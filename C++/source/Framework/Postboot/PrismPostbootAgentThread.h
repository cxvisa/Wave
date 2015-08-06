/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTAGENTTHREAD_H
#define PRISMPOSTBOOTAGENTTHREAD_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Postboot/PrismPostbootAgentThreadContext.h"
#include "Framework/MultiThreading/PrismPosixThread.h"

namespace WaveNs
{

class PrismPostbootAgentContext;
class PrismPostbootAgentThread : protected WaveWorker, public PrismPosixThread
{
    private :
    protected :
    public :
							PrismPostbootAgentThread		  (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, const ResourceId &recoveryType, PrismPostbootAgentThreadContext *pPrismPostbootAgentThreadContext);
        virtual            ~PrismPostbootAgentThread            ();

        WaveThreadStatus    start               ();

    // Now the data members

    private :
                UI32        m_eventId;
                UI32        m_parameter;
                ResourceId  m_recoveryType;
				PrismPostbootAgentThreadContext *m_pPrismPostbootAgentThreadContext;
        static  UI32        m_parallelPostBootAgentThreads;
        static  WaveMutex  m_parallelPostBootAgentThreadsMutex;
    protected :
    public :
};

}

#endif // PRISMPOSTBOOTAGENTTHREAD_H
