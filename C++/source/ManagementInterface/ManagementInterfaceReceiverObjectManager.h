/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACERECEIVEROBJECTMANAGER_H
#define MANAGEMENTINTERFACERECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class ServerStreamingSocket;
class ManagementInterfaceReceiverThread;
class BootCompleteForThisLocationEvent;
class WaveAsynchronousContextForBootPhases;

class ManagementInterfaceReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                       ManagementInterfaceReceiverObjectManager                    ();

        virtual void   initialize                                                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void   boot                                                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void   listenForEvents                                             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void   bootCompleteForThisLocationEventHandler                     (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);


        static  bool   addManagementInterfaceReceiverThreadToCache                 (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort, ManagementInterfaceReceiverThread *&pManagementInterfaceReceiverThread);
        static  void   removeManagemntInterfaceReceiverThreadFromCache             (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static  string getRemoteLocationUniqueIdentifier                           (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    protected :
    public :
        virtual                                          ~ManagementInterfaceReceiverObjectManager ();
        static  ManagementInterfaceReceiverObjectManager *getInstance                              ();
        static  WaveServiceId                            getWaveServiceId                        ();

        static  bool                                      isACurrentlyConnectedLocation            (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

        static  void                                      debugPrint                               (UI32 argc, vector<string> argv);
        static  void                                      registerDebugShellEntries                ();
        static  void   terminateAndRemoveManagemntInterfaceReceiverThreadFromCache (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

        static string                                     getMessageVersionForManagemntInterface    (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort); 
        static UI8                                        getSerializationTypeForManagemntInterface (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerSocketForManagementInterfaceClients;

    protected :
    public :

    friend class ManagementInterfaceReceiverThread;
};

}

#endif // MANAGEMENTINTERFACERECEIVEROBJECTMANAGER_H
