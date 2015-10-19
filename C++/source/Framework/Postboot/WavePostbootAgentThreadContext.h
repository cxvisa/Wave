/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Jitendra Singh                                                   *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTAGENTTHREADCONTEXT_H
#define WAVEPOSTBOOTAGENTTHREADCONTEXT_H

#include "Framework/Postboot/WavePostPersistentBootMessages.h"

using namespace std;

namespace WaveNs
{
class WaveMutex;
class WaveCondition;
class WavePostbootAgentThreadContext 
{
    public :
        		                        WavePostbootAgentThreadContext ();
        virtual                        ~WavePostbootAgentThreadContext ();
    	void 							setPostbootMessagePointer (WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage);
		WavePostPersistenceBootMessage *getPostbootMessagePointer ();
                void                    setPostbootMutex                        (WaveMutex *pPostbootMutex);
                WaveMutex             *getPostbootMutex                        () const;
                void                    setPostbootSynchronizingCondition       (WaveCondition *pPostbootSynchronizingCondition);
                WaveCondition         *getPostbootSynchronizingCondition       () const;


    // Now the data members

    private :
		WavePostPersistenceBootMessage *m_pWavePostPersistenceBootMessage;
        WaveMutex                      *m_pPostbootMutex;
        WaveCondition                  *m_pPostbootSynchronizingCondition;

};

}

#endif // WAVEPOSTBOOTAGENTTHREADCONTEXT_H
