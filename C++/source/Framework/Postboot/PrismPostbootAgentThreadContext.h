/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Jitendra Singh                                                   *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTAGENTTHREADCONTEXT_H
#define PRISMPOSTBOOTAGENTTHREADCONTEXT_H

#include "Framework/Postboot/PrismPostPersistentBootMessages.h"

using namespace std;

namespace WaveNs
{
class WaveMutex;
class WaveCondition;
class PrismPostbootAgentThreadContext 
{
    public :
        		                        PrismPostbootAgentThreadContext ();
        virtual                        ~PrismPostbootAgentThreadContext ();
    	void 							setPostbootMessagePointer (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage);
		PrismPostPersistenceBootMessage *getPostbootMessagePointer ();
                void                    setPostbootMutex                        (WaveMutex *pPostbootMutex);
                WaveMutex             *getPostbootMutex                        () const;
                void                    setPostbootSynchronizingCondition       (WaveCondition *pPostbootSynchronizingCondition);
                WaveCondition         *getPostbootSynchronizingCondition       () const;


    // Now the data members

    private :
		PrismPostPersistenceBootMessage *m_pPrismPostPersistenceBootMessage;
        WaveMutex                      *m_pPostbootMutex;
        WaveCondition                  *m_pPostbootSynchronizingCondition;

};

}

#endif // PRISMPOSTBOOTAGENTTHREADCONTEXT_H
