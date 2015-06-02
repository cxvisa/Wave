/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Anil C                                                         *
 ***************************************************************************/

#ifndef PRISMPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H
#define PRISMPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H

#include "Framework/Postboot/PrismPostPersistentBootMessages.h"

using namespace std;

namespace WaveNs
{
class PrismMutex;
class PrismCondition;
class PrismPostPersistentBootWorkerClusterContext 
{
    public :
                                        PrismPostPersistentBootWorkerClusterContext ();
                                        PrismPostPersistentBootWorkerClusterContext ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, PrismPostPersistenceBootMessage *PrismPostPersistenceBootMessage = NULL, PrismMutex *pPostbootMutex = NULL, PrismCondition *pPostbootSynchronizingCondition = NULL);
                                        
                void                    initializeContext                           ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, PrismPostPersistenceBootMessage *PrismPostPersistenceBootMessage = NULL, PrismMutex *pPostbootMutex = NULL, PrismCondition *pPostbootSynchronizingCondition = NULL);
        virtual                        ~PrismPostPersistentBootWorkerClusterContext ();

                void                    setEventId                              (const UI32 &eventId);
                UI32                    getEventId                              () const;
                void                    setParameter                            (const UI32 &parameter);
                UI32                    getParameter                            () const;
                void                    setRecoveryType                         (const ResourceId &recoveryType);
                ResourceId              getRecoveryType                         () const;
                void                    setPostbootMutex                        (PrismMutex *pPostbootMutex);
                PrismMutex             *getPostbootMutex                        () const;
                void                    setPostbootSynchronizingCondition       (PrismCondition *pPostbootSynchronizingCondition);            
                PrismCondition         *getPostbootSynchronizingCondition       () const;
                void                    setPostbootMessagePointer               (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage);
                PrismPostPersistenceBootMessage *getPostbootMessagePointer      () const;

    // Now the data members

    private :
                UI32                    m_eventId;
                UI32                    m_parameter;
                ResourceId              m_recoveryType;
                PrismMutex             *m_pPostbootMutex;
                PrismCondition         *m_pPostbootSynchronizingCondition;
                PrismPostPersistenceBootMessage *m_pPrismPostPersistenceBootMessage;
};

}

#endif // PRISMPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H
