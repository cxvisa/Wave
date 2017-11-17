/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Interface/InterfaceManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"

namespace IsleNs
{

InterfaceManagedObject::InterfaceManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement           (pNetworkModelObjectManager),
      WavePersistableObject (InterfaceManagedObject::getClassName (), IsleManagedObject::getClassName ()),
      WaveManagedObject     (pNetworkModelObjectManager),
      IsleManagedObject     (pNetworkModelObjectManager)
{
}

InterfaceManagedObject::~InterfaceManagedObject ()
{
}

string InterfaceManagedObject::getClassName ()
{
    return ("InterfaceManagedObject");
}

void InterfaceManagedObject::setupAttributesForCreate ()
{
    IsleManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeMacAddress (&m_macAddress, "macAddress"));
}

void InterfaceManagedObject::setupAttributesForPersistence ()
{
    IsleManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeMacAddress (&m_macAddress, "macAddress"));
}

const MacAddress &InterfaceManagedObject::getMacAddress () const
{
    return (m_macAddress);
}

void InterfaceManagedObject::setMacAddress (const MacAddress &macAddress)
{
    m_macAddress = macAddress;
}

}
