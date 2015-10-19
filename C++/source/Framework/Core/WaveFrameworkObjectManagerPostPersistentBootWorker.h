/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKOBJECTMANAGERPOSTPERSISTENTBOOTWORKER_H
#define WAVEFRAMEWORKOBJECTMANAGERPOSTPERSISTENTBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Postboot/WavePostPersistentBootMessages.h"

namespace WaveNs
{

class WavePostPersistenceBootMessage;
class WavePostBootHardwareSyncMessage;
class WavePostPersistentBootWorkerClusterContext;

class WaveFrameworkObjectManagerPostPersistentBootWorker : public WaveWorker
{
    private :
                void          postPersistentBootMessageHandler                      (WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage);
                void          postPersistentBootServiceAndWaveSlotsMessageHandler   (WavePostPersistenceBootServiceAndWaveSlotsMessage *pWavePostPersistenceBootServiceAndWaveSlotsMessage);
                ResourceId    copyRunningToStart                                    ();
                string        createReplayString                                    (const string &path, const string &params, const string &file);
                void          triggerPostBootPassTable                              (const UI32 &eventId, const UI32 &parameter, WavePostPersistenceBootMessage *pWavePostPersistenceBootMessage);
                ResourceId    triggerStartupFileReplay                              ();
                ResourceId    triggerLastConfigReplay                               ();
                void          resetXPathStringsTimestampsInPersistenceObjectManager ();
                ResourceId    setupStartupAfterConfigReplay                             ();

    protected :
    public :
                 WaveFrameworkObjectManagerPostPersistentBootWorker                (WaveObjectManager *pWaveObjectManager);
        virtual ~WaveFrameworkObjectManagerPostPersistentBootWorker                ();
                ResourceId    triggerPostBootPassTableForAll                        (WavePostPersistentBootWorkerClusterContext *pPostPersistentBootWorkerClusterContext);  
                ResourceId    triggerPostBootPassTableForEvent                      (const WavePostPersistentBootWorkerClusterContext *pPostPersistentBootWorkerClusterContext);

    // Now the Data Members
    private :
    protected :
    public :
};

}

#endif // WAVEFRAMEWORKOBJECTMANAGERPOSTPERSISTENTBOOTWORKER_H
