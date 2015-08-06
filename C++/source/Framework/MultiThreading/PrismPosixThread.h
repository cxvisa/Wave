/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/
#ifndef PRISMPOSIXTHREAD_H
#define PRISMPOSIXTHREAD_H

#include <iostream>
#include <pthread.h>
#include "Framework/MultiThreading/WaveThreadStatus.h"
#include "Framework/MultiThreading/PrismPosixThreadContext.h"
#include "WaveResourceIdEnums.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class PrismPosixThread;

typedef PrismPosixThread *(*PrismPosixThreadStartMethodType) (PrismPosixThread *);
typedef void *(*PosixThreadStartMethodType) (void *);
typedef pthread_t WaveThreadId;

class PrismPosixThread
{
    public :
                                         PrismPosixThread  (const UI32 &stackSize = 0);
                                         PrismPosixThread  (const PrismPosixThread &prismPosixThread);
        virtual                         ~PrismPosixThread  ();
                PrismPosixThread        &operator =        (const PrismPosixThread &prismPosixThread);
        virtual WaveThreadStatus        run               ();
                WaveThreadStatus        joinCallingThread ();
        const   PrismPosixThreadContext *getThreadContext  ();
                WaveThreadId            getId             () const;

    protected :
        virtual WaveThreadStatus        start               ();
        virtual PrismPosixThreadContext *createThreadContext ();
        virtual void                     stopCallingThread   ();

    private :
        static PrismPosixThread *pthreadStartMethod (PrismPosixThread *pPrismPoixThread);

    private:
        pthread_t                m_pThreadId;
        PrismPosixThreadContext *m_pThreadContext;
        UI32                     m_stackSize;
};

}

#endif
