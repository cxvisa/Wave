/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef GRPCGATEWAYLOCALOBJECTMANAGER_H
#define GRPCGATEWAYLOCALOBJECTMANAGER_H

#include <grpc++/impl/codegen/completion_queue.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <memory>

#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;

namespace WaveNs
{

class GrpcGatewayLocalObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                      GrpcGatewayLocalObjectManager           ();

        virtual void  initialize                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void  boot                                    (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void  listenForEvents                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void  bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);

    protected :
    public :
        virtual                              ~GrpcGatewayLocalObjectManager ();

        static string                         getServiceName                ();
        static GrpcGatewayLocalObjectManager *getInstance                   ();
        static WaveServiceId                  getWaveServiceId              ();

        // Now the data members

    private :
        ServerBuilder                     m_grpcServerBuilder;
        unique_ptr<ServerCompletionQueue> m_grpcServerCompletionQueue;
        unique_ptr<Server>                m_grpcServer;

    protected :
    public :
};

}

#endif // GRPCGATEWAYLOCALOBJECTMANAGER_H
