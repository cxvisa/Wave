/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/
#include "Framework/MultiThreading/WavePosixThread.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include <signal.h>
#include <errno.h>

using namespace std;

namespace WaveNs
{

#ifdef __ZVM__
static UI32 s_prismPosixThreadStackSize = PTHREAD_STACK_MIN * 4 * 32;
#else
static UI32 s_prismPosixThreadStackSize = PTHREAD_STACK_MIN * 16;
#endif

WavePosixThread::WavePosixThread (const UI32 &stackSize)
{
    m_pThreadId      = (pthread_t)0;
    m_pThreadContext = NULL;

    m_stackSize = stackSize;

    // Reset the stackSize accordingly

    if (0 == m_stackSize)
    {
        m_stackSize = s_prismPosixThreadStackSize; // The default Stack Size.
    }
}

WavePosixThread::WavePosixThread (const WavePosixThread &prismPosixThread)
{
    WaveNs::trace (TRACE_LEVEL_FATAL, "WavePosixThread::WavePosixThread : Copy constructing a WavePosixThread does not make sense and hence not allowed.");
    WaveNs::waveAssert (false, __FILE__, __LINE__);
}

WavePosixThread::~WavePosixThread ()
{
    WaveFrameworkObjectManager::removeWaveThreadId (m_pThreadId);
}

WavePosixThread &WavePosixThread::operator = (const WavePosixThread &prismPosixThread)
{
    WaveNs::trace (TRACE_LEVEL_FATAL, "WavePosixThread::operator = : Assigning to a WavePosixThread does not make sense and hence not allowed.");
    WaveNs::waveAssert (false, __FILE__, __LINE__);

    return (*this);
}

WaveThreadStatus WavePosixThread::run ()
{
    static int signalMaskIndicator = 0;
           int status              = 0;

    // The following code massks the SIGALRM and SIGPIPE signals for the entire process.
    // This happens jut before the first ptheread gets created in the system and it only happens
    // once.  We make sure that this by using the signalMaskIndicator statuc variable.
    // On linux the oly way to make the sigwait to reliably work is to block the corresponding
    // sgnals for the entire process before any thread is crated in the system and them make a
    // particular thread wait for the signal using the sigwait call.  Refer to the "Threads and Signal handling"
    // section of the GNU libc manual located at the following URL:
    // http://www.gnu.org/software/libc/manual/html_mono/libc.html#Threads%20and%20Signal%20Handling
    // This works on GNU/Linux as well as Net BSD systems.

    prismInstallSigIntHandler ();

    if (0 == signalMaskIndicator)
    {
        prismBlockSignals ();

        signalMaskIndicator = 1;

    }

    // Create the thread in a detached state so that we do not encounter the atrificial limit on the number of threads created during entire life of the process.

    pthread_attr_t pthreadAttribute;

    status = pthread_attr_init (&pthreadAttribute);

    if (0 != status)
    {
        cerr << "Pthread attributes could not be initialized : Status : " << status << endl;
        return (WAVE_THREAD_COULD_NOT_CREATE);
    }

    status = pthread_attr_setdetachstate (&pthreadAttribute, PTHREAD_CREATE_DETACHED);

    if (0 != status)
    {
        cerr << "Pthread attribute for detach state could not be set : Status : " << status << endl;
        return (WAVE_THREAD_COULD_NOT_CREATE);
    }

    status = pthread_attr_setstacksize (&pthreadAttribute, m_stackSize);

    if (0 != status)
    {
        cerr << "Pthread attribute for set stack size could not be set : Status : " << status << endl;
        return (WAVE_THREAD_COULD_NOT_CREATE);
    }

    status = pthread_create (&m_pThreadId, &pthreadAttribute, reinterpret_cast<PosixThreadStartMethodType> (WavePosixThread::pthreadStartMethod), reinterpret_cast<void **> (this));

    if (0 != status)
    {
        cerr << "pthread could not be created : errno : " << errno << ", Status : " << status << endl;
        return (WAVE_THREAD_COULD_NOT_CREATE);
    }
    else
    {
        WaveFrameworkObjectManager::addWaveThreadId (m_pThreadId);
        return (WAVE_THREAD_SUCCESS);
    }
}

WaveThreadStatus WavePosixThread::joinCallingThread ()
{
    void *pContext = NULL;

    int status = pthread_join (m_pThreadId, &pContext);

    if (0 != status)
    {
        return (WAVE_THREAD_ERROR);
    }
    else
    {
        return (WAVE_THREAD_SUCCESS);
    }
}

WavePosixThreadContext *WavePosixThread::createThreadContext ()
{
    return (new WavePosixThreadContext ());
}

const WavePosixThreadContext *WavePosixThread::getThreadContext()
{
    return (m_pThreadContext);
}

WaveThreadId WavePosixThread::getId () const
{
    return (m_pThreadId);
}

WavePosixThread *WavePosixThread::pthreadStartMethod (WavePosixThread *pWavePoixThread)
{
    pWavePoixThread->start ();
    // We will see the following output only if user has ovewritten the start and did not make calls to pthread_exit in the new definition of start.
    //cout << "Finished Executing the User defined behavior (user did not call pthread_exit)." << endl;
    return (pWavePoixThread);
}

WaveThreadStatus WavePosixThread::start ()
{
    cout << "Thread Started." << endl;
    cout << "We are not doing anything useful here." << endl;
    cout << "Ending the thread now." << endl;
    stopCallingThread ();
    // We should never see the following statement in the output as the above line ends the execution of the thread.
    cout << "Thread Ended." << endl;
    return (WAVE_THREAD_SUCCESS);
}

void WavePosixThread::stopCallingThread ()
{
    pthread_exit (reinterpret_cast<void *> (this));
}

}
