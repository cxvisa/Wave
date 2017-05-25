/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "gRPC/GrpcGatewayLocalObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <grpc++/grpc++.h>
#include <grpc/support/log.h>

using namespace grpc;

namespace WaveNs
{

GrpcGatewayLocalObjectManager::GrpcGatewayLocalObjectManager ()
    : WaveLocalObjectManagerForUserSpecificTasks (getServiceName ())
{
    setAllowAutomaticallyUnlistenForEvents (false);

    restrictMessageHistoryLogging (false, false, false);
}

GrpcGatewayLocalObjectManager::~GrpcGatewayLocalObjectManager ()
{
}

string GrpcGatewayLocalObjectManager::getServiceName ()
{
    return ("gRPC Gateway");
}

WaveServiceId GrpcGatewayLocalObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

GrpcGatewayLocalObjectManager *GrpcGatewayLocalObjectManager::getInstance ()
{
    static GrpcGatewayLocalObjectManager *pGrpcGatewayLocalObjectManager = new GrpcGatewayLocalObjectManager ();

    WaveNs::waveAssert (nullptr != pGrpcGatewayLocalObjectManager, __FILE__, __LINE__);

    return (pGrpcGatewayLocalObjectManager);
}

void GrpcGatewayLocalObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    const string grpcServerAddress = string ("0.0.0.0:") + FrameworkToolKit::getGrpcServerPort ();

    m_grpcServerBuilder.AddListeningPort (grpcServerAddress, InsecureServerCredentials ());

    m_grpcServerCompletionQueue = m_grpcServerBuilder.AddCompletionQueue ();

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void GrpcGatewayLocalObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void GrpcGatewayLocalObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION, reinterpret_cast<WaveEventHandler> (&GrpcGatewayLocalObjectManager::bootCompleteForThisLocationEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void GrpcGatewayLocalObjectManager::bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent)
{
    // Since we told framework not to unlistenEvents, we must explicitly unlisten for events since we are going to go into an infinite while loop.

    unlistenEvents ();

    reply (reinterpret_cast<const WaveEvent *&> (pBootCompleteForThisLocationEvent));

    trace (TRACE_LEVEL_INFO, "GrpcGatewayLocalObjectManager::bootCompleteForThisLocationEventHandler : Now accepting connections from gRPC Clients");

    m_grpcServer = m_grpcServerBuilder.BuildAndStart ();

}

}
