/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/
#ifndef WAVEPOSIXTHREAD_H
#define WAVEPOSIXTHREAD_H

#include <iostream>
#include <pthread.h>
#include "Framework/MultiThreading/WaveThreadStatus.h"
#include "Framework/MultiThreading/WavePosixThreadContext.h"
#include "WaveResourceIdEnums.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class WavePosixThread;

typedef WavePosixThread *(*WavePosixThreadStartMethodType) (WavePosixThread *);
typedef void *(*PosixThreadStartMethodType) (void *);
typedef pthread_t WaveThreadId;

class WavePosixThread
{
    public :
                                         WavePosixThread  (const UI32 &stackSize = 0);
                                         WavePosixThread  (const WavePosixThread &wavePosixThread);
        virtual                         ~WavePosixThread  ();
                WavePosixThread        &operator =        (const WavePosixThread &wavePosixThread);
        virtual WaveThreadStatus        run               ();
                WaveThreadStatus        joinCallingThread ();
        const   WavePosixThreadContext *getThreadContext  ();
                WaveThreadId            getId             () const;

    protected :
        virtual WaveThreadStatus        start               ();
        virtual WavePosixThreadContext *createThreadContext ();
        virtual void                     stopCallingThread   ();

    private :
        static WavePosixThread *pthreadStartMethod (WavePosixThread *pWavePoixThread);

    private:
        pthread_t                m_pThreadId;
        WavePosixThreadContext *m_pThreadContext;
        UI32                     m_stackSize;
};

}

#endif
