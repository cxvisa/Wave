/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessageFactory/WaveMessageFactory.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"

namespace WaveNs
{

WaveMessage *WaveMessageFactory::getMessageInstance (const WaveServiceId &serviceId, const UI32 &opcode)
{
    WaveObjectManager *pWaveObjectManager = getWaveObjectManagerForMessage (serviceId, opcode);
    WaveMessage       *pWaveMessage       = NULL;

    if (NULL != pWaveObjectManager)
    {
        pWaveMessage = pWaveObjectManager->createMessageInstanceWrapper (opcode);
    }

    if (NULL == pWaveMessage)
    {
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Could not create message instance for  Service : " + FrameworkToolKit::getServiceNameById (serviceId) + ", Opcode = " + opcode + ".");
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Have you implemented the createMessageInstance on the object manager yet???.");
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Also, Please make sure that the opcode has been registered using addOperationMap on the corresponding Object Manager.");
        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveMessage);
}

WaveObjectManager *WaveMessageFactory::getWaveObjectManagerForMessage (const WaveServiceId &serviceId, const UI32 &opcode)
{
    WaveThread        *pWaveThread        = NULL;
    WaveObjectManager *pWaveObjectManager = NULL;

    pWaveThread = WaveThread::getWaveThreadForServiceId (serviceId);

    if (NULL != pWaveThread)
    {
        pWaveObjectManager = pWaveThread->getWaveObjectManagerForOperationCode (opcode);
    }

    return (pWaveObjectManager);
}

WaveObjectManager *WaveMessageFactory::getWaveObjectManagerForEvent (const WaveServiceId &serviceId, const UI32 &eventOpcode)
{
    WaveThread        *pWaveThread        = NULL;
    WaveObjectManager *pWaveObjectManager = NULL;

    pWaveThread = WaveThread::getWaveThreadForServiceId (serviceId);

    if (NULL != pWaveThread)
    {
        pWaveObjectManager = pWaveThread->getWaveObjectManagerForEventOperationCode (eventOpcode);
    }

    return (pWaveObjectManager);
}

WaveObjectManager *WaveMessageFactory::getWaveObjectManagerForEventListener (const LocationId &locationId, const WaveServiceId &serviceId, const UI32 &eventOpcode)
{
    WaveThread        *pWaveThread        = NULL;
    WaveObjectManager *pWaveObjectManager = NULL;

    pWaveThread = WaveThread::getWaveThreadForServiceId (serviceId);

    if (NULL != pWaveThread)
    {
        pWaveObjectManager = pWaveThread->getWaveObjectManagerForEventOperationCodeForListening (locationId, serviceId, eventOpcode);
    }

    return (pWaveObjectManager);
}

WaveMessage *WaveMessageFactory::getManagementInterfaceMessageInstance (const string &waveClientName, const WaveServiceId &serviceId, const UI32 &opcode)
{
    if (WAVE_MGMT_INTF_ROLE_CLIENT == (FrameworkToolKit::getManagementInterfaceRole ()))
    {
        return (getMessageInstance (serviceId, opcode));
    }

    ManagementInterfaceMessageInstantiatorForClient  managementInterfaceMessageInstantiatorForClient = WaveUserInterfaceObjectManager::getManagementInterfaceMessageInstantiatorForClient (waveClientName);
    WaveMessage                                    *pWaveMessage                                   = NULL;

    if (NULL != managementInterfaceMessageInstantiatorForClient)
    {
        pWaveMessage = (*managementInterfaceMessageInstantiatorForClient) (opcode);

        if (NULL == pWaveMessage)
        {
            trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getManagementInterfaceMessageInstance : Management Interface Message Instantiator for client \'" + waveClientName + "\' Returned NULL.");
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            ManagementInterfaceMessage *pManagementInterfaceMessage = dynamic_cast<ManagementInterfaceMessage *> (pWaveMessage);

            if (NULL == pManagementInterfaceMessage)
            {
                trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getManagementInterfaceMessageInstance : Only Management Interface Derivations can be used in messaging with Wave Clients.");
                waveAssert (false, __FILE__, __LINE__);
            }
        }
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getManagementInterfaceMessageInstance : Management Interface Message Instantiator has not bee set for client \'" + waveClientName + "\'.");
        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveMessage);
}

WaveObjectManager *WaveMessageFactory::getWaveObjectManagerForLightPulse (const string &lightPulseName)
{
    return (WaveObjectManager::getWaveObjectManagerForLightPulseType (lightPulseName));
}

}
