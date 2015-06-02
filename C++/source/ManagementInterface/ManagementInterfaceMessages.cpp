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

RequestToManagementInterfaceMessage::RequestToManagementInterfaceMessage (PrismServiceId serviceId, UI32 operationId, AttributesMap *pAttributesMap)
    : PrismMessage (ManagementInterfaceObjectManager::getPrismServiceId (), MANAGEMENTINTERFACE_REQUEST),
      m_pInputAttributesMap (pAttributesMap)
{
}

}
