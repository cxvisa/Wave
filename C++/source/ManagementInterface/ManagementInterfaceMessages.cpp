/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ManagementInterface/ManagementInterfaceMessages.h"
#include "ManagementInterface/ManagementInterfaceTypes.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"

namespace WaveNs
{

RequestToManagementInterfaceMessage::RequestToManagementInterfaceMessage (WaveServiceId serviceId, UI32 operationId, AttributesMap *pAttributesMap)
    : PrismMessage (ManagementInterfaceObjectManager::getWaveServiceId (), MANAGEMENTINTERFACE_REQUEST),
      m_pInputAttributesMap (pAttributesMap)
{
}

}
