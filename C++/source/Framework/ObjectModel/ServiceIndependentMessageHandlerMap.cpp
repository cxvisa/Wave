/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author :  Anand Subramanian, Brian Adaniya                            *
 ***************************************************************************/

#include "Framework/ObjectModel/ServiceIndependentMessageHandlerMap.h"
#include "Framework/Messaging/Local/WaveServiceIndependentMessage.h"
#include "ManagementInterface/ManagementInterfaceServiceIndependentMessage.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>                   ServiceIndependentMessageHandlerMap::s_waveServiceIndependentMessageHandlerMap;
map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>    ServiceIndependentMessageHandlerMap::s_managementInterfaceServiceIndependentMessageHandlerMap;
WaveMutex                                                                      ServiceIndependentMessageHandlerMap::s_serviceIndependentMessageHandlerMapMutex;

void ServiceIndependentMessageHandlerMap::addOperationMap (UI32 serviceId, UI32 operationCode, WaveServiceIndependentMessageHandler pMessageHandler)
{
    s_serviceIndependentMessageHandlerMapMutex.lock ();

    map <UI32, WaveServiceIndependentMessageHandler> *opcodeHandlerMap;
    
    map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>::iterator element = s_waveServiceIndependentMessageHandlerMap.find (serviceId);
    map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>::iterator end     = s_waveServiceIndependentMessageHandlerMap.end ();

    if (end != element)
    {
        opcodeHandlerMap = (element->second);

        map<UI32, WaveServiceIndependentMessageHandler>::iterator opcodeHandlerMapElement = opcodeHandlerMap->find (operationCode);
        map<UI32, WaveServiceIndependentMessageHandler>::iterator opcodeHandlerMapEnd     = opcodeHandlerMap->end ();

        if (opcodeHandlerMapEnd != opcodeHandlerMapElement)
        {
            trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::addOperationMap : OperationMap already found for serviceId : ") + serviceId + string (" and operation code : ") + operationCode);
            waveAssert (false, __FILE__, __LINE__);

            return;
        }
        
        (*opcodeHandlerMap)[operationCode] = pMessageHandler;
    }
    else
    {
        opcodeHandlerMap = new map <UI32, WaveServiceIndependentMessageHandler>;
        (*opcodeHandlerMap)[operationCode] = pMessageHandler;
        s_waveServiceIndependentMessageHandlerMap[serviceId] = opcodeHandlerMap;
    }

    s_serviceIndependentMessageHandlerMapMutex.unlock ();
}

void ServiceIndependentMessageHandlerMap::addOperationMap (UI32 serviceId, UI32 operationCode, ManagementInterfaceServiceIndependentMessageHandler pMessageHandler)
{
    s_serviceIndependentMessageHandlerMapMutex.lock ();

    map <UI32, ManagementInterfaceServiceIndependentMessageHandler> *opcodeHandlerMap;

    map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>::iterator element = s_managementInterfaceServiceIndependentMessageHandlerMap.find (serviceId);
    map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>::iterator end     = s_managementInterfaceServiceIndependentMessageHandlerMap.end ();

    if (end != element)
    {
        opcodeHandlerMap = (element->second);

        map<UI32, ManagementInterfaceServiceIndependentMessageHandler>::iterator opcodeHandlerMapElement = opcodeHandlerMap->find (operationCode);
        map<UI32, ManagementInterfaceServiceIndependentMessageHandler>::iterator opcodeHandlerMapEnd     = opcodeHandlerMap->end ();

        if (opcodeHandlerMapEnd != opcodeHandlerMapElement)
        {
            trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::addOperationMap : OperationMap already found for serviceId : ") + serviceId + string (" and operation code : ") + operationCode);
            waveAssert (false, __FILE__, __LINE__);

            return;
        }

        (*opcodeHandlerMap)[operationCode] = pMessageHandler;
    }
    else
    {
        opcodeHandlerMap = new map <UI32, ManagementInterfaceServiceIndependentMessageHandler>;
        (*opcodeHandlerMap)[operationCode] = pMessageHandler;
        s_managementInterfaceServiceIndependentMessageHandlerMap[serviceId] = opcodeHandlerMap;
    }

    s_serviceIndependentMessageHandlerMapMutex.unlock ();
}

void ServiceIndependentMessageHandlerMap::execute (WaveServiceIndependentMessage *pWaveServiceIndependentMessage)
{
    s_serviceIndependentMessageHandlerMapMutex.lock ();

    UI32 serviceId          = pWaveServiceIndependentMessage->getServiceCode ();
    UI32 operationCode      = pWaveServiceIndependentMessage->getOperationCode ();

    map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>::iterator element = s_waveServiceIndependentMessageHandlerMap.find (serviceId);
    map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>::iterator end     = s_waveServiceIndependentMessageHandlerMap.end ();

    if (end == element)
    {
        trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::execute: OperationMap entry not found for this ServiceId : ") + serviceId + string (" opcode : ") + operationCode);
        waveAssert (false, __FILE__, __LINE__);

        return;
    }    

    map <UI32, WaveServiceIndependentMessageHandler> opcodeHandlerMap = *(element->second);

    map<UI32, WaveServiceIndependentMessageHandler>::iterator opcodeHandlerMapElement = opcodeHandlerMap.find (operationCode);
    map<UI32, WaveServiceIndependentMessageHandler>::iterator opcodeHandlerMapEnd     = opcodeHandlerMap.end ();

    if (opcodeHandlerMapEnd == opcodeHandlerMapElement)
    {
        trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::execute: OperationMap entry not found for this serviceId : ") + serviceId + string (" opcode : ") + operationCode);
        waveAssert (false, __FILE__, __LINE__);

        return;
    }

    (*(opcodeHandlerMapElement->second)) (pWaveServiceIndependentMessage);

    s_serviceIndependentMessageHandlerMapMutex.unlock ();
}

void ServiceIndependentMessageHandlerMap::execute (ManagementInterfaceServiceIndependentMessage *pManagementInterfaceServiceIndependentMessage)
{
    s_serviceIndependentMessageHandlerMapMutex.lock ();

    UI32 serviceId          = pManagementInterfaceServiceIndependentMessage->getServiceCode ();
    UI32 operationCode      = pManagementInterfaceServiceIndependentMessage->getOperationCode ();

    map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>::iterator element = s_managementInterfaceServiceIndependentMessageHandlerMap.find (serviceId);
    map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>::iterator end     = s_managementInterfaceServiceIndependentMessageHandlerMap.end ();

    if (end == element)
    {
        trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::execute: OperationMap entry not found for this ServiceId : ") + serviceId + string (" opcode : ") + operationCode);
        waveAssert (false, __FILE__, __LINE__);

        return;
    }

    map <UI32, ManagementInterfaceServiceIndependentMessageHandler> opcodeHandlerMap = *(element->second);

    map<UI32, ManagementInterfaceServiceIndependentMessageHandler>::iterator opcodeHandlerMapElement = opcodeHandlerMap.find (operationCode);
    map<UI32, ManagementInterfaceServiceIndependentMessageHandler>::iterator opcodeHandlerMapEnd     = opcodeHandlerMap.end ();

    if (opcodeHandlerMapEnd == opcodeHandlerMapElement)
    {
        trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::execute: OperationMap entry not found for this serviceId : ") + serviceId + string (" opcode : ") + operationCode);
        waveAssert (false, __FILE__, __LINE__);

        return;
    }

    (*(opcodeHandlerMapElement->second)) (pManagementInterfaceServiceIndependentMessage);

    s_serviceIndependentMessageHandlerMapMutex.unlock ();
}

void ServiceIndependentMessageHandlerMap::removeOperationMap (UI32 serviceId, UI32 operationCode)
{
    bool isRemovedFromWaveServiceIndependentMessageHandlerMap                   = false;
    bool isRemovedFromManagementInterfaceServiceIndependentMessageHandlerMap    = false;

    s_serviceIndependentMessageHandlerMapMutex.lock ();

    // Attempt to remove the operation map from both the WaveServiceIndependentMessageHandlerMap and the ManagementInterfaceServiceIndependentMessageHandlerMap.
    // First try to remove from the WaveServiceIndependentMessageHanderMap
    
    map <UI32, WaveServiceIndependentMessageHandler> opcodeHandlerMap;

    map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>::iterator element = s_waveServiceIndependentMessageHandlerMap.find (serviceId);
    map <UI32, map<UI32, WaveServiceIndependentMessageHandler> *>::iterator end     = s_waveServiceIndependentMessageHandlerMap.end ();

    if (end != element)
    {
        opcodeHandlerMap = *(element->second);

        map<UI32, WaveServiceIndependentMessageHandler>::iterator opcodeHandlerMapElement = opcodeHandlerMap.find (operationCode);
        map<UI32, WaveServiceIndependentMessageHandler>::iterator opcodeHandlerMapEnd     = opcodeHandlerMap.end ();

        if (opcodeHandlerMapEnd == opcodeHandlerMapElement)
        {
            isRemovedFromWaveServiceIndependentMessageHandlerMap = false;
        }
        else
        {
            opcodeHandlerMap.erase (opcodeHandlerMapElement);
            isRemovedFromWaveServiceIndependentMessageHandlerMap = true;
        }
    }
    else
    {
        isRemovedFromWaveServiceIndependentMessageHandlerMap = false;
    }

    // Next try to remove from the ManagementInterfaceServiceIndependentMessageHanderMap

    map <UI32, ManagementInterfaceServiceIndependentMessageHandler> opcodeHandlerMap2;

    map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>::iterator element2 = s_managementInterfaceServiceIndependentMessageHandlerMap.find (serviceId);
    map <UI32, map<UI32, ManagementInterfaceServiceIndependentMessageHandler> *>::iterator end2     = s_managementInterfaceServiceIndependentMessageHandlerMap.end ();

    if (end2 != element2)
    {
        opcodeHandlerMap2 = *(element2->second);

        map<UI32, ManagementInterfaceServiceIndependentMessageHandler>::iterator opcodeHandlerMapElement2 = opcodeHandlerMap2.find (operationCode);
        map<UI32, ManagementInterfaceServiceIndependentMessageHandler>::iterator opcodeHandlerMapEnd2     = opcodeHandlerMap2.end ();

        if (opcodeHandlerMapEnd2 == opcodeHandlerMapElement2)
        {
            isRemovedFromManagementInterfaceServiceIndependentMessageHandlerMap = false;
        }
        else
        {
            opcodeHandlerMap2.erase (opcodeHandlerMapElement2);
            isRemovedFromManagementInterfaceServiceIndependentMessageHandlerMap = true;
        }
    }
    else
    {
        isRemovedFromManagementInterfaceServiceIndependentMessageHandlerMap = false;
    }

    // Verify remove from either map was done

    if ((false == isRemovedFromWaveServiceIndependentMessageHandlerMap) && (false == isRemovedFromManagementInterfaceServiceIndependentMessageHandlerMap))
    {
        trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::removeOperationMap : OperationMap NOT found either WaveServiceIndependentMessageHanderMap nor ManagementInterfaceServiceIndependentMessageHandlerMap for ServiceId : ") + serviceId + string (" and operation code : ") + operationCode);
        waveAssert (false, __FILE__, __LINE__);
    }
    else if ((true == isRemovedFromWaveServiceIndependentMessageHandlerMap) && (true == isRemovedFromManagementInterfaceServiceIndependentMessageHandlerMap))
    {
        trace (TRACE_LEVEL_FATAL, string ("ServiceIndependentMessageHandlerMap::removeOperationMap : OperationMap found in BOTH WaveServiceIndependentMessageHanderMap and ManagementInterfaceServiceIndependentMessageHandlerMap for ServiceId : ") + serviceId + string (" and operation code : ") + operationCode + ".  This should never happen.");
        waveAssert (false, __FILE__, __LINE__);
    }

    s_serviceIndependentMessageHandlerMapMutex.unlock ();
}

}    
