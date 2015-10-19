/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkObjectManagerServiceControlWorker.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

WaveFrameworkObjectManagerServiceControlWorker::WaveFrameworkObjectManagerServiceControlWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_SERVICE_CONTROL_LIST_MESSAGE,     reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManagerServiceControlWorker::serviceControlListMessageHandler));
    addOperationMap (FRAMEWORK_OBJECT_MANAGER_SERVICE_SET_CPU_AFFINITY_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkObjectManagerServiceControlWorker::serviceSetCpuAffinityMessageHandler));
}

WaveFrameworkObjectManagerServiceControlWorker::~WaveFrameworkObjectManagerServiceControlWorker ()
{
}

WaveMessage *WaveFrameworkObjectManagerServiceControlWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case FRAMEWORK_OBJECT_MANAGER_SERVICE_CONTROL_LIST_MESSAGE :
            pWaveMessage = new FrameworkObjectManagerServiceControlListMessage;
            break;

        case FRAMEWORK_OBJECT_MANAGER_SERVICE_SET_CPU_AFFINITY_MESSAGE :
            pWaveMessage = new FrameworkObjectManagerServiceSetCpuAffinityMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void WaveFrameworkObjectManagerServiceControlWorker::serviceControlListMessageHandler (FrameworkObjectManagerServiceControlListMessage *pFrameworkObjectManagerServiceControlListMessage)
{
    vector<WaveServiceId> waveServiceIds;
    UI32                   numberOfWaveServices;
    UI32                   i;
    WaveServiceId         serviceId              = 0;
    string                 serviceName;
    bool                   isEnabled              = false;
    bool                   isLocal                = false;
    vector<UI32>           cpuAffinityVector;
    string                 cpuAffinity;
    UI32                   numberOfCpus           = 0;
    UI32                   j                      = 0;

    WaveThread::getListOfServiceIds (waveServiceIds);
    numberOfWaveServices = waveServiceIds.size ();

    for (i = 0; i < numberOfWaveServices; i++)
    {
        serviceId         = waveServiceIds[i];
        serviceName       = FrameworkToolKit::getServiceNameById (serviceId);
        isEnabled         = WaveObjectManager::isServiceEnabled (serviceId);
        isLocal           = FrameworkToolKit::isALocalService (serviceId);
        cpuAffinityVector = WaveThread::getCpuAffinityVectorForServiceId (serviceId);

        cpuAffinity  = "";
        numberOfCpus = cpuAffinityVector.size ();

        for (j = 0; j < numberOfCpus; j++)
        {
            cpuAffinity = cpuAffinity + cpuAffinityVector[j] + string (":");
        }

        pFrameworkObjectManagerServiceControlListMessage->addAService (serviceId, serviceName, isEnabled, isLocal, cpuAffinity);
    }

    pFrameworkObjectManagerServiceControlListMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pFrameworkObjectManagerServiceControlListMessage);
}

void WaveFrameworkObjectManagerServiceControlWorker::serviceSetCpuAffinityMessageHandler (FrameworkObjectManagerServiceSetCpuAffinityMessage *pFrameworkObjectManagerServiceSetCpuAffinityMessage)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkObjectManagerServiceControlWorker::serviceSetCpuAffinityMessageHandler : Entering ...");

          WaveServiceId                           waveServiceId                          = pFrameworkObjectManagerServiceSetCpuAffinityMessage->getWaveServiceId ();
          vector<UI32>                             cpuAffinityVector                       = pFrameworkObjectManagerServiceSetCpuAffinityMessage->getCpuAffinityVector ();
          WaveSetCpuAffinityObjectManagerMessage  prismSetCpuAffinityObjectManagerMessage   (waveServiceId);
          ResourceId                               status                                  = WAVE_MESSAGE_SUCCESS;
    const WaveServiceId                           thisServiceId                           = getServiceId ();

    if (thisServiceId != waveServiceId)
    {
        prismSetCpuAffinityObjectManagerMessage.setCpuAffinityVector (cpuAffinityVector);

        status = sendSynchronously (&prismSetCpuAffinityObjectManagerMessage);

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            status = prismSetCpuAffinityObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManagerServiceControlWorker::serviceSetCpuAffinityMessageHandler : Failed to set Cpu Affinity for service \'" + FrameworkToolKit::getServiceNameById (waveServiceId) + "\'.  Status : " + FrameworkToolKit::localize (status));
            }
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "WaveFrameworkObjectManagerServiceControlWorker::serviceSetCpuAffinityMessageHandler : Failed to send message.  Status : " + FrameworkToolKit::localize (status));
        }
    }
    else
    {
        setCpuAffinity (cpuAffinityVector);
    }

    pFrameworkObjectManagerServiceSetCpuAffinityMessage->setCompletionStatus (status);
    reply (pFrameworkObjectManagerServiceSetCpuAffinityMessage);
}

}
