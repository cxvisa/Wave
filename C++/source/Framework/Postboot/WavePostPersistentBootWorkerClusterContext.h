/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Anil C                                                         *
 ***************************************************************************/

#ifndef WAVEPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H
#define WAVEPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H

#include "Framework/Postboot/WavePostPersistentBootMessages.h"

using namespace std;

namespace WaveNs
{
class WaveMutex;
class WaveCondition;
class WavePostPersistentBootWorkerClusterContext 
{
    public :
                                        WavePostPersistentBootWorkerClusterContext ();
                                        WavePostPersistentBootWorkerClusterContext ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, WavePostPersistenceBootMessage *WavePostPersistenceBootMessage = NULL, WaveMutex *pPostbootMutex = NULL, WaveCondition *pPostbootSynchronizingCondition = NULL);
                                        
                void                    initializeContext                           ( const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType, WavePostPersistenceBootMessage *WavePostPersistenceBootMessage = NULL, WaveMutex *pPostbootMutex = NULL, WaveCondition *pPostbootSynchronizingCondition = NULL);
        virtual                        ~WavePostPersistentBootWorkerClusterContext ();

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
                void                    setPostbootMessagePointer               (WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage);
                WavePostPersistenceBootMessage *getPostbootMessagePointer      () const;

    // Now the data members

    private :
                UI32                    m_eventId;
                UI32                    m_parameter;
                ResourceId              m_recoveryType;
                WaveMutex             *m_pPostbootMutex;
                WaveCondition         *m_pPostbootSynchronizingCondition;
                WavePostPersistenceBootMessage *m_pWavePostPersistenceBootMessage;
};

}

#endif // WAVEPOSTPERSISTENTBOOTWORKERCLUSTERCONTEXT_H
