/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Interface/InterfaceWorker.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "NetworkModel/Global/Interface/InterfaceManagedObject.h"
#include "NetworkModel/Global/Interface/VirtualInterfaceManagedObject.h"
#include "NetworkModel/Global/Interface/TapInterfaceManagedObject.h"

namespace IsleNs
{

InterfaceWorker::InterfaceWorker (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveWorker (pNetworkModelObjectManager)
{
    InterfaceManagedObject        interfaceManagedObject        (pNetworkModelObjectManager);
    VirtualInterfaceManagedObject virtualInterfaceManagedObject (pNetworkModelObjectManager);
    TapInterfaceManagedObject     tapInterfaceManagedObject     (pNetworkModelObjectManager);

    addManagedClass (InterfaceManagedObject::getClassName        (), this);
    addManagedClass (VirtualInterfaceManagedObject::getClassName (), this);
    addManagedClass (TapInterfaceManagedObject::getClassName     (), this);

    interfaceManagedObject.setupOrm        ();
    virtualInterfaceManagedObject.setupOrm ();
    tapInterfaceManagedObject.setupOrm     ();
}

InterfaceWorker::~InterfaceWorker ()
{
}

WaveManagedObject *InterfaceWorker::createManagedObjectInstance (const string &managedObjectClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    NetworkModelObjectManager *pNetworkModelObjectManager = NULL;
    WaveObjectManager         *pWaveObjectManager         = getPWaveObjectManager ();

    waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    pNetworkModelObjectManager = dynamic_cast<NetworkModelObjectManager *> (pWaveObjectManager);

    waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    if ((InterfaceManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new InterfaceManagedObject (pNetworkModelObjectManager);
    }
    else if ((VirtualInterfaceManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new VirtualInterfaceManagedObject (pNetworkModelObjectManager);
    }
    else if ((TapInterfaceManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new TapInterfaceManagedObject (pNetworkModelObjectManager);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("InterfaceWorker::createManagedObjectInstance : Unknown Managed Object Class Name : ") + managedObjectClassName);

        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

}
