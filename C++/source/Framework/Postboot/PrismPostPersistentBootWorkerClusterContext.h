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
class WaveMutex;
class WaveCondition;
class PrismPostPersistentBootWorkerClusterContext 
{
    public :
                                        PrismPostPersistentBootWorkerClusterContext ();
                                        PrismPostPersistentBootWorkerClusterContext ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, PrismPostPersistenceBootMessage *PrismPostPersistenceBootMessage = NULL, WaveMutex *pPostbootMutex = NULL, WaveCondition *pPostbootSynchronizingCondition = NULL);
                                        
                void                    initializeContext                           ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, PrismPostPersistenceBootMessage *PrismPostPersistenceBootMessage = NULL, WaveMutex *pPostbootMutex = NULL, WaveCondition *pPostbootSynchronizingCondition = NULL);
        virtual                        ~PrismPostPersistentBootWorkerClusterContext ();

                void                    setEventId                              (const UI32 &eventId);
                UI32                    getEventId                              () const;
                void                    setParameter                            (const UI32 &parameter);
                UI32                    getParameter                            () const;
                void                    setRecoveryType                         (const ResourceId &recoveryType);
                ResourceId              getRecoveryType                         () const;
                void                    setPostbootMutex                        (WaveMutex *pPostbootMutex);
                WaveMutex             *getPostbootMutex                        () const;
                void                    setPostbootSynchronizingCondition       (WaveCondition *pPostbootSynchronizingCondition);            
                WaveCondition         *getPostbootSynchronizingCondition       () const;
                void                    setPostbootMessagePointer               (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage);
                PrismPostPersistenceBootMessage *getPostbootMessagePointer      () const;

    // Now the data members

    private :
                UI32                    m_eventId;
                UI32                    m_parameter;
                ResourceId              m_recoveryType;
                WaveMutex             *m_pPostbootMutex;
                WaveCondition         *m_pPostbootSynchronizingCondition;
                PrismPostPersistenceBootMessage *m_pPrismPostPersistenceBootMessage;
};

}

#endif // PRISMPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H
