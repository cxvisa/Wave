/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPINTERFACERECEIVEROBJECTMANAGER_H
#define HTTPINTERFACERECEIVEROBJECTMANAGER_H

#include <Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h>

namespace WaveNs
{

class ServerStreamingSocket;
class BootCompleteForThisLocationEvent;
class WaveAsynchronousContextForBootPhases;
class HttpInterfaceMethodWorker;

class HttpInterfaceReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                      HttpInterfaceReceiverObjectManager      ();
                void  construct                               ();

        virtual void  initialize                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void  boot                                    (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void  listenForEvents                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void  bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);

    protected :
                     HttpInterfaceReceiverObjectManager (const string &serviceName);

        virtual bool getIsTranportSecurityEnabled () const;
        virtual SI32 getInterfaceReceiverPort     () const;

    public :
        virtual                                    ~HttpInterfaceReceiverObjectManager ();

        static  string                              getServiceName                     ();
        static  HttpInterfaceReceiverObjectManager *getInstance                        ();
        static  WaveServiceId                      getWaveServiceId                  ();

        static  bool                                isAKnownHttpInterfaceMethod        (const WaveHttpInterfaceMethod &waveHttpInterfaceMethod);
        static  void                                addHttpInterfaceMethodWorker       (const WaveHttpInterfaceMethod &waveHttpInterfaceMethod, HttpInterfaceMethodWorker *pHttpInterfaceMethodWorker);
        static  HttpInterfaceMethodWorker          *getHttpInterfaceMethodWorker       (const WaveHttpInterfaceMethod &waveHttpInterfaceMethod);

    // Now the data members

    private :
               ServerStreamingSocket                                     *m_pServerSocketForHttpInterfaceClients;

        static map<WaveHttpInterfaceMethod, HttpInterfaceMethodWorker *>  m_httpInterfaceMethodWorkers;

    protected :
    public :
};

}

#endif // HTTPINTERFACERECEIVEROBJECTMANAGER_H
