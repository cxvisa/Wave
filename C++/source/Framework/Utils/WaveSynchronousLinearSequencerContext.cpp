/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

#include <pthread.h>

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

namespace WaveNs
{

WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
{
    m_pWaveMessage                 = pWaveMessage;
    m_pWaveAsynchronousContext     = NULL;
    m_pWaveElement                 = pWaveElement;
    m_pSteps                        = NULL;
    m_numberOfSteps                 = numberOfSteps;
    m_currentStep                   = 0;
    m_isTransactionStartedByMe      = false;
    m_isADelayedCommitTransaction   = false;
    m_completionStatus              = WAVE_MESSAGE_ERROR;

    m_clockId                   = 0;

    if (3 > m_numberOfSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext : There should be atleast three steps to run a Wave Linear Sequencer. " << numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pSteps = new WaveSynchronousLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = pSteps[i];
    }

    return;
}

WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
{
    m_pWaveMessage                 = NULL;
    m_pWaveAsynchronousContext     = pWaveAsynchronousContext;
    m_pWaveElement                 = pWaveElement;
    m_pSteps                        = NULL;
    m_numberOfSteps                 = numberOfSteps;
    m_currentStep                   = 0;
    m_isTransactionStartedByMe      = false;
    m_isADelayedCommitTransaction   = false;
    m_completionStatus              = WAVE_MESSAGE_ERROR;

    m_clockId                       = 0;

    if (3 > m_numberOfSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext : There should be atleast three steps to run a Wave Linear Sequencer. " << numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pSteps = new WaveSynchronousLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = pSteps[i];
    }

    return;
}

WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext (const WaveSynchronousLinearSequencerContext &prismSynchronousLinearSequencerContext)
{
    m_pWaveMessage                 = prismSynchronousLinearSequencerContext.m_pWaveMessage;
    m_pWaveAsynchronousContext     = prismSynchronousLinearSequencerContext.m_pWaveAsynchronousContext;
    m_pWaveElement                 = prismSynchronousLinearSequencerContext.m_pWaveElement;
    m_pSteps                        = prismSynchronousLinearSequencerContext.m_pSteps;
    m_numberOfSteps                 = prismSynchronousLinearSequencerContext.m_numberOfSteps;
    m_currentStep                   = prismSynchronousLinearSequencerContext.m_currentStep;
    m_isTransactionStartedByMe      = prismSynchronousLinearSequencerContext.m_isTransactionStartedByMe;
    m_isADelayedCommitTransaction   = prismSynchronousLinearSequencerContext.m_isADelayedCommitTransaction;
    m_completionStatus              = WAVE_MESSAGE_ERROR;

    m_clockId                       = 0;

    if (3 > m_numberOfSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext : There should be atleast three steps to run a Wave Linear Sequencer. " << m_numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pSteps = new WaveSynchronousLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::WaveSynchronousLinearSequencerContext : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = prismSynchronousLinearSequencerContext.m_pSteps[i];
    }

    return;
}

WaveSynchronousLinearSequencerContext::~WaveSynchronousLinearSequencerContext ()
{
    if (NULL != m_pSteps)
    {
        delete[] m_pSteps;
    }

    garbageCollect ();
}

WaveSynchronousLinearSequencerContext &WaveSynchronousLinearSequencerContext::operator = (const WaveSynchronousLinearSequencerContext &prismSynchronousLinearSequencerContext)
{
    m_pWaveMessage                 = prismSynchronousLinearSequencerContext.m_pWaveMessage;
    m_pWaveAsynchronousContext     = prismSynchronousLinearSequencerContext.m_pWaveAsynchronousContext;
    m_pWaveElement                 = prismSynchronousLinearSequencerContext.m_pWaveElement;
    m_pSteps                        = prismSynchronousLinearSequencerContext.m_pSteps;
    m_numberOfSteps                 = prismSynchronousLinearSequencerContext.m_numberOfSteps;
    m_currentStep                   = prismSynchronousLinearSequencerContext.m_currentStep;
    m_isTransactionStartedByMe      = prismSynchronousLinearSequencerContext.m_isTransactionStartedByMe;
    m_isADelayedCommitTransaction   = prismSynchronousLinearSequencerContext.m_isADelayedCommitTransaction;
    m_completionStatus              = prismSynchronousLinearSequencerContext.m_completionStatus;

    m_clockId                       = 0;

    if (3 > m_numberOfSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::operator = : There should be atleast three steps to run a Wave Linear Sequencer. " << m_numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return (*this);
    }

    m_pSteps = new WaveSynchronousLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveSynchronousLinearSequencerContext::operator = : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return (*this);
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = prismSynchronousLinearSequencerContext.m_pSteps[i];
    }

    return (*this);
}

void WaveSynchronousLinearSequencerContext::advanceCurrentStep ()
{
    m_currentStep++;
}

ResourceId WaveSynchronousLinearSequencerContext::executeCurrentStep ()
{
    struct timespec ts1                 = {0};
    struct timespec ts2                 = {0};
    struct timespec tsr1                = {0};
    struct timespec tsr2                = {0};
            SI32    returnValue         = -1;
            SI32    returnValueR        = -1;
            UI32    operationCode       = 0;
            UI32    numberOfSeconds     = 0;
            SI32    numberOfNanoSeconds = 0;
            UI32    currentStep         = m_currentStep;
            UI32    numberOfSteps       = m_numberOfSteps;

    if (currentStep < (numberOfSteps - 2))
    {
        if ((0 != m_clockId) && (NULL != m_pWaveMessage) && (NULL != m_pWaveElement))
        {
            operationCode = m_pWaveMessage->getOperationCode ();

            returnValue   = clock_gettime (m_clockId,      &ts1);
            returnValueR  = clock_gettime (CLOCK_REALTIME, &tsr1);
        }
    }


    ResourceId status = (m_pWaveElement->*(m_pSteps[currentStep])) (this);

    if (currentStep < (numberOfSteps - 2))
    {
        if (0 == returnValue)
        {
            returnValue = clock_gettime (m_clockId, &ts2);

            if (0 == returnValue)
            {
                numberOfSeconds     = ts2.tv_sec  - ts1.tv_sec;
                numberOfNanoSeconds = ts2.tv_nsec - ts1.tv_nsec;

                m_pWaveElement->updateTimeConsumedInThisThread (operationCode, currentStep, numberOfSeconds, numberOfNanoSeconds);
            }
        }

        if (0 == returnValueR)
        {
            returnValueR = clock_gettime (CLOCK_REALTIME, &tsr2);

            if (0 == returnValueR)
            {
                numberOfSeconds     = tsr2.tv_sec  - tsr1.tv_sec;
                numberOfNanoSeconds = tsr2.tv_nsec - tsr1.tv_nsec;

                m_pWaveElement->updateRealTimeConsumedInThisThread (operationCode, currentStep, numberOfSeconds, numberOfNanoSeconds);
            }
        }
    }

    return (status);
}

ResourceId WaveSynchronousLinearSequencerContext::getCompletionStatus ()
{
    return (m_completionStatus);
}

ResourceId WaveSynchronousLinearSequencerContext::execute ()
{
    UI32 i;
    UI32 effectiveNumberOfSteps = m_numberOfSteps - 2;
    SI32 returnValue            = 0;

    m_completionStatus = WAVE_MESSAGE_ERROR;

    returnValue = pthread_getcpuclockid (pthread_self (), &m_clockId);

    if (0 != returnValue)
    {
        m_clockId = 0;

        cerr << "Could not get Clock ID for this thread." << endl;
    }

    for (i = 0; i < effectiveNumberOfSteps; i++)
    {
        m_completionStatus = executeCurrentStep ();

        if (WAVE_MESSAGE_SUCCESS != m_completionStatus)
        {
            if (WAVE_SEQUENCER_SKIP_TO_SUCCESS_STEP == m_completionStatus)
            {
                // Move step pointer to the success step
                m_currentStep = effectiveNumberOfSteps;
                m_completionStatus = WAVE_MESSAGE_SUCCESS;
            }

            break;
        }
        else
        {
            advanceCurrentStep ();
        }
    }

    if (WAVE_MESSAGE_SUCCESS != m_completionStatus)
    {
        m_currentStep = m_numberOfSteps - 1;
    }

    return (executeCurrentStep ());
}

WaveMessage *WaveSynchronousLinearSequencerContext::getPWaveMessage ()
{
    return (m_pWaveMessage);
}

void WaveSynchronousLinearSequencerContext::setPWaveMessage (WaveMessage *pWaveMessage)
{
    m_pWaveMessage = pWaveMessage;
}

WaveAsynchronousContext *WaveSynchronousLinearSequencerContext::getPWaveAsynchronousContext ()
{
    return (m_pWaveAsynchronousContext);
}

bool WaveSynchronousLinearSequencerContext::getIsTransactionStartedByMe () const
{
    return (m_isTransactionStartedByMe);
}

void WaveSynchronousLinearSequencerContext::setIsTransactionStartedByMe (const bool &isTransactionStartedByMe)
{
    m_isTransactionStartedByMe = isTransactionStartedByMe;
}

void WaveSynchronousLinearSequencerContext::addManagedObjectsForGarbageCollection (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection)
{
    m_managedObjectsForGarbageCollection.insert (m_managedObjectsForGarbageCollection.end (), managedObjectsForGarbageCollection.begin (), managedObjectsForGarbageCollection.end ());
}

void WaveSynchronousLinearSequencerContext::addManagedObjectForGarbageCollection (WaveManagedObject *pWaveManagedObjectForGarbageCollection)
{
    waveAssert (NULL != pWaveManagedObjectForGarbageCollection, __FILE__, __LINE__);

    m_managedObjectsForGarbageCollection.push_back (pWaveManagedObjectForGarbageCollection);
}

void WaveSynchronousLinearSequencerContext::garbageCollect ()
{
    UI32 numberOfManagedObjectsForGarbageCollection = m_managedObjectsForGarbageCollection.size ();
    UI32 i                                          = 0;

    for (i = 0; i < numberOfManagedObjectsForGarbageCollection; i++)
    {
        waveAssert (NULL != m_managedObjectsForGarbageCollection[i], __FILE__, __LINE__);

        delete (m_managedObjectsForGarbageCollection[i]);
    }
}

bool WaveSynchronousLinearSequencerContext::getIsADelayedCommitTransaction () const
{
    return (m_isADelayedCommitTransaction);
}
 
void WaveSynchronousLinearSequencerContext::setIsADelayedCommitTransaction (const bool &isADelayedCommitTransaction)
{
    m_isADelayedCommitTransaction = isADelayedCommitTransaction;
}

}
