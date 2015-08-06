/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef INTERLOCATIONMESSAGERECEIVEROBJECTMANAGER_H
#define INTERLOCATIONMESSAGERECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class InterLocationMessageReceiverThread;
class WaveAsynchronousContextForBootPhases;

class InterLocationMessageReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                      InterLocationMessageReceiverObjectManager                                          ();
               void   boot                                                                               (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        static bool   addInterLocationMessageReceiverThreadToCache                                       (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort, InterLocationMessageReceiverThread *&pInterLocationMessageReceiverThread);
        static void   removeInterLocationMessageReceiverThreadFromCache                                  (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static void   closePeerServerStreamingSocketAndRemoveInterLocationMessageReceiverThreadFromCache (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static void   terminateAndRemoveInterLocationMessageReceiverThreadFromCache                      (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static string getRemoteLocationUniqueIdentifier                                                  (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    protected :
    public :
        virtual                                          ~InterLocationMessageReceiverObjectManager ();
        static InterLocationMessageReceiverObjectManager *getInstance                               ();
        static WaveServiceId                             getWaveServiceId                         ();
        static bool                                       isACurrentlyConnectedLocation             (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

        static void                                       debugPrint                                (UI32 argc, vector<string> argv);
        static void                                       registerDebugShellEntries                 ();

        static string                                     getMessageVersionForRemoteLocation        (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static UI8                                        getSerializationTypeForRemoteLocation     (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);  

    // Now the data members

    private :
    protected :
    public :

    friend class InterLocationMessageReceiverThread;
    friend class PrismFrameworkObjectManager;
};

}

#endif // INTERLOCATIONMESSAGERECEIVEROBJECTMANAGER_H
