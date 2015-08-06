/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author :  Anand Subramanian, Brian Adaniya                            *
 ***************************************************************************/

#ifndef SERVICEINDEPENDENTMESSAGEHANDLERMAP_H
#define SERVICEINDEPENDENTMESSAGEHANDLERMAP_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/PrismMutex.h"
#include <map>

namespace WaveNs
{

class WaveServiceIndependentMessage;
class ManagementInterfaceServiceIndependentMessage;

class ServiceIndependentMessageHandlerMap
{
    private :

    protected :
    public :
            static void         addOperationMap         (UI32 serviceId, UI32 operationCode, WaveServiceIndependentMessageHandler pMessageHandler);
            static void         addOperationMap         (UI32 serviceId, UI32 operationCode, ManagementInterfaceServiceIndependentMessageHandler pMessageHandler);
            static void         execute                 (WaveServiceIndependentMessage *pWaveServiceIndependentMessage);
            static void         execute                 (ManagementInterfaceServiceIndependentMessage *pManagementInterfaceServiceIndependentMessage);
            static void         removeOperationMap      (UI32 serviceId, UI32 operationCode);


    // Now the data members

    private :
            static map <UI32, map <UI32, WaveServiceIndependentMessageHandler> *>                   s_waveServiceIndependentMessageHandlerMap;
            static map <UI32, map <UI32, ManagementInterfaceServiceIndependentMessageHandler> *>    s_managementInterfaceServiceIndependentMessageHandlerMap;
            static PrismMutex                                                                       s_serviceIndependentMessageHandlerMapMutex;

    protected :
    public :
};

}

#endif // SERVICEINDEPENDENTMESSAGEHANDLERMAP_H
