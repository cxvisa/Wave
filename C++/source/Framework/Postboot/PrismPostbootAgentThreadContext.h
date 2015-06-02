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
class PrismMutex;
class PrismCondition;
class PrismPostbootAgentThreadContext 
{
    public :
        		                        PrismPostbootAgentThreadContext ();
        virtual                        ~PrismPostbootAgentThreadContext ();
    	void 							setPostbootMessagePointer (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage);
		PrismPostPersistenceBootMessage *getPostbootMessagePointer ();
                void                    setPostbootMutex                        (PrismMutex *pPostbootMutex);
                PrismMutex             *getPostbootMutex                        () const;
                void                    setPostbootSynchronizingCondition       (PrismCondition *pPostbootSynchronizingCondition);
                PrismCondition         *getPostbootSynchronizingCondition       () const;


    // Now the data members

    private :
		PrismPostPersistenceBootMessage *m_pPrismPostPersistenceBootMessage;
        PrismMutex                      *m_pPostbootMutex;
        PrismCondition                  *m_pPostbootSynchronizingCondition;

};

}

#endif // PRISMPOSTBOOTAGENTTHREADCONTEXT_H
