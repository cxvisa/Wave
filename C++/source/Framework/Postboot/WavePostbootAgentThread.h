/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTAGENTTHREAD_H
#define WAVEPOSTBOOTAGENTTHREAD_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Postboot/WavePostbootAgentThreadContext.h"
#include "Framework/MultiThreading/WavePosixThread.h"

namespace WaveNs
{

class WavePostbootAgentContext;
class WavePostbootAgentThread : protected WaveWorker, public WavePosixThread
{
    private :
    protected :
    public :
							WavePostbootAgentThread		  (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, const ResourceId &recoveryType, WavePostbootAgentThreadContext *pWavePostbootAgentThreadContext);
        virtual            ~WavePostbootAgentThread            ();

        WaveThreadStatus    start               ();

    // Now the data members

    private :
                UI32        m_eventId;
                UI32        m_parameter;
                ResourceId  m_recoveryType;
				WavePostbootAgentThreadContext *m_pWavePostbootAgentThreadContext;
        static  UI32        m_parallelPostBootAgentThreads;
        static  WaveMutex  m_parallelPostBootAgentThreadsMutex;
    protected :
    public :
};

}

#endif // WAVEPOSTBOOTAGENTTHREAD_H
