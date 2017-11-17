/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Hypervisor/HypervisorManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "NetworkModel/Global/Bridge/BridgeManagedObject.h"
#include "Framework/Attributes/AttributeIpVxAddress.h"

namespace IsleNs
{

HypervisorManagedObject::HypervisorManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement           (pNetworkModelObjectManager),
      WavePersistableObject (HypervisorManagedObject::getClassName (), IsleManagedObject::getClassName ()),
      WaveManagedObject     (pNetworkModelObjectManager),
      IsleManagedObject     (pNetworkModelObjectManager)
{
}

HypervisorManagedObject::~HypervisorManagedObject ()
{
}

string HypervisorManagedObject::getClassName ()
{
    return ("HypervisorManagedObject");
}

void HypervisorManagedObject::setupAttributesForCreate ()
{
    IsleManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeIpVxAddress               (&m_ipAddress, "ipAddress"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAggregation (&m_bridges,   "bridges",  getClassName (), getObjectId (), BridgeManagedObject::getClassName  ()));
}

void HypervisorManagedObject::setupAttributesForPersistence ()
{
    IsleManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeIpVxAddress               (&m_ipAddress, "ipAddress"));
    addPersistableAttribute (new AttributeObjectIdVectorAggregation (&m_bridges,   "bridges", getClassName  (), getObjectId (), BridgeManagedObject::getClassName  ()));
}

void HypervisorManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("ipAddress");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

const IpVxAddress &HypervisorManagedObject::getIpAddress () const
{
    return (m_ipAddress);
}

void HypervisorManagedObject::setIpAddress (const IpVxAddress &ipAddress)
{
    m_ipAddress = ipAddress;
}

vector<ObjectId> &HypervisorManagedObject::getBridges ()
{
    return (m_bridges);
}

}
