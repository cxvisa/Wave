/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                       *
 ***************************************************************************/

#ifndef HAPEERMESSAGERECEIVEROBJECTMANAGER_H
#define HAPEERMESSAGERECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class HaPeerMessageReceiverThread;
class WaveAsynchronousContextForBootPhases;

class HaPeerMessageReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                      HaPeerMessageReceiverObjectManager                                          ();
               void   boot                                                                               (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        static bool   addHaPeerMessageReceiverThreadToCache                                       (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort, HaPeerMessageReceiverThread *&pHaPeerMessageReceiverThread);
        static void   removeHaPeerMessageReceiverThreadFromCache                                  (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static void   closePeerServerStreamingSocketAndRemoveHaPeerMessageReceiverThreadFromCache (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static void   terminateAndRemoveHaPeerMessageReceiverThreadFromCache                      (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static string getRemoteLocationUniqueIdentifier                                                  (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    protected :
    public :
        virtual                                          ~HaPeerMessageReceiverObjectManager ();
        static HaPeerMessageReceiverObjectManager *getInstance                               ();
        static WaveServiceId                             getWaveServiceId                         ();
        static bool                                       isACurrentlyConnectedLocation             (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

        static void                                       debugPrint                                (UI32 argc, vector<string> argv);
        static void                                       registerDebugShellEntries                 ();

        static string                                     getMessageVersionForHaPeer                        (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static UI8                                        getSerializationTypeForHaPeer                     (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    // Now the data members

    private :
    protected :
    public :

    friend class HaPeerMessageReceiverThread;
    friend class WaveFrameworkObjectManager;
    friend class WaveFrameworkObjectManagerHaSyncWorker;
};

}

#endif // HAPEERMESSAGERECEIVEROBJECTMANAGER_H
