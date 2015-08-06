/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENTRECEIVEROBJECTMANAGER_H
#define WAVECLIENTRECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class ServerStreamingSocket;
class WaveClientReceiverThread;
class WaveAsynchronousContextForBootPhases;
class WaveClientTransportObjectManager;

class WaveClientReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                       WaveClientReceiverObjectManager ();

        virtual void   initialize                                          (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void   boot                                                (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        static  bool   addWaveClientReceiverThreadToCache                  (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort, WaveClientReceiverThread *&pWaveClientReceiverThread, const string& remoteLocationMessageVersion);
        static  void   removeWaveClientReceiverThreadFromCache             (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static  void   terminateAndRemoveWaveClientReceiverThreadFromCache (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static  string getRemoteLocationUniqueIdentifier                   (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    protected :
    public :
        virtual                                 ~WaveClientReceiverObjectManager ();

        static  WaveClientReceiverObjectManager *getInstance                     ();
        static  WaveServiceId                   getWaveServiceId               ();

        static  bool                             isACurrentlyConnectedLocation   (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

        static  void                             debugPrint                      (UI32 argc, vector<string> argv);
        static  void                             registerDebugShellEntries       ();

        static  void                             setAutoScanForAvailablePort     (const bool &autoScanForAvailablePort);

        static string                            getMessageVersionForWaveClient  (const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);
        static UI8                               getSerializationTypeForWaveClient(const string &remoteLocationIpAddress, const SI32 &remoteLocationPort);

    // Now the Data Members

    private :
        static map<string, WaveClientReceiverThread *>  s_waveClientReceiverThreadCache;
        static WaveMutex                               s_waveClientReceiverThreadCacheMutex;

               ServerStreamingSocket                   *m_pServerSocketForWaveManagementInterfaceServers;

        static bool                                     m_autoScanForAvailablePort;
        static UI32                                     m_autoScanLimit;

    protected :
    public :

    friend class WaveClientReceiverThread;
    friend class WaveClientTransportObjectManager;
};

}

#endif // WAVECLIENTRECEIVEROBJECTMANAGER_H
