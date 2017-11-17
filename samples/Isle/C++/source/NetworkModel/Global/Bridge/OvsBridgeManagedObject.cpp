/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Bridge/OvsBridgeManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"

namespace IsleNs
{

OvsBridgeManagedObject::OvsBridgeManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement           (pNetworkModelObjectManager),
      WavePersistableObject (OvsBridgeManagedObject::getClassName (), BridgeManagedObject::getClassName ()),
      WaveManagedObject     (pNetworkModelObjectManager),
      IsleManagedObject     (pNetworkModelObjectManager),
      BridgeManagedObject   (pNetworkModelObjectManager)
{
}

OvsBridgeManagedObject::~OvsBridgeManagedObject ()
{
}

string OvsBridgeManagedObject::getClassName ()
{
    return ("OvsBridgeManagedObject");
}

void OvsBridgeManagedObject::setupAttributesForCreate ()
{
}

void OvsBridgeManagedObject::setupAttributesForPersistence ()
{
    BridgeManagedObject::setupAttributesForPersistence ();
}

}
