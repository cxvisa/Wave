/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Hypervisor/KvmHypervisorManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"

namespace IsleNs
{

KvmHypervisorManagedObject::KvmHypervisorManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement             (pNetworkModelObjectManager),
      WavePersistableObject   (KvmHypervisorManagedObject::getClassName (), HypervisorManagedObject::getClassName ()),
      WaveManagedObject       (pNetworkModelObjectManager),
      IsleManagedObject       (pNetworkModelObjectManager),
      HypervisorManagedObject (pNetworkModelObjectManager)
{
}

KvmHypervisorManagedObject::~KvmHypervisorManagedObject ()
{
}

string KvmHypervisorManagedObject::getClassName ()
{
    return ("KvmHypervisorManagedObject");
}

void KvmHypervisorManagedObject::setupAttributesForCreate ()
{
}

void KvmHypervisorManagedObject::setupAttributesForPersistence ()
{
    HypervisorManagedObject::setupAttributesForPersistence ();
}

}
