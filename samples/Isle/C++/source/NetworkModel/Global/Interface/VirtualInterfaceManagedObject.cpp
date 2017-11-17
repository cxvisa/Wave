/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Interface/VirtualInterfaceManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"

namespace IsleNs
{

VirtualInterfaceManagedObject::VirtualInterfaceManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement             (pNetworkModelObjectManager),
      WavePersistableObject   (VirtualInterfaceManagedObject::getClassName (), InterfaceManagedObject::getClassName ()),
      WaveManagedObject       (pNetworkModelObjectManager),
      IsleManagedObject       (pNetworkModelObjectManager),
      InterfaceManagedObject (pNetworkModelObjectManager)
{
}

VirtualInterfaceManagedObject::~VirtualInterfaceManagedObject ()
{
}

string VirtualInterfaceManagedObject::getClassName ()
{
    return ("VirtualInterfaceManagedObject");
}

void VirtualInterfaceManagedObject::setupAttributesForCreate ()
{
}

void VirtualInterfaceManagedObject::setupAttributesForPersistence ()
{
    InterfaceManagedObject::setupAttributesForPersistence ();
}

}
