/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKOBJECTMANAGERPOSTPERSISTENTBOOTWORKER_H
#define PRISMFRAMEWORKOBJECTMANAGERPOSTPERSISTENTBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Postboot/PrismPostPersistentBootMessages.h"

namespace WaveNs
{

class PrismPostPersistenceBootMessage;
class PrismPostBootHardwareSyncMessage;
class PrismPostPersistentBootWorkerClusterContext;

class PrismFrameworkObjectManagerPostPersistentBootWorker : public WaveWorker
{
    private :
                void          postPersistentBootMessageHandler                      (PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage);
                void          postPersistentBootServiceAndWaveSlotsMessageHandler   (PrismPostPersistenceBootServiceAndWaveSlotsMessage *pPrismPostPersistenceBootServiceAndWaveSlotsMessage);
                ResourceId    copyRunningToStart                                    ();
                string        createReplayString                                    (const string &path, const string &params, const string &file);
                void          triggerPostBootPassTable                              (const UI32 &eventId, const UI32 &parameter, PrismPostPersistenceBootMessage *pPrismPostPersistenceBootMessage);
                ResourceId    triggerStartupFileReplay                              ();
                ResourceId    triggerLastConfigReplay                               ();
                void          resetXPathStringsTimestampsInPersistenceObjectManager ();
                ResourceId    setupStartupAfterConfigReplay                             ();

    protected :
    public :
                 PrismFrameworkObjectManagerPostPersistentBootWorker                (WaveObjectManager *pWaveObjectManager);
        virtual ~PrismFrameworkObjectManagerPostPersistentBootWorker                ();
                ResourceId    triggerPostBootPassTableForAll                        (PrismPostPersistentBootWorkerClusterContext *pPostPersistentBootWorkerClusterContext);  
                ResourceId    triggerPostBootPassTableForEvent                      (const PrismPostPersistentBootWorkerClusterContext *pPostPersistentBootWorkerClusterContext);

    // Now the Data Members
    private :
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKOBJECTMANAGERPOSTPERSISTENTBOOTWORKER_H
