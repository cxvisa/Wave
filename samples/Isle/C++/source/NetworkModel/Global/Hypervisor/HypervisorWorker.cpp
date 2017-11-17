/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Hypervisor/KvmHypervisorManagedObject.h"
#include "NetworkModel/Global/Hypervisor/HypervisorWorker.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "NetworkModel/Global/Hypervisor/HypervisorManagedObject.h"

namespace IsleNs
{

HypervisorWorker::HypervisorWorker (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveWorker (pNetworkModelObjectManager)
{
    HypervisorManagedObject    hypervisorManagedObject    (pNetworkModelObjectManager);
    KvmHypervisorManagedObject kvmHypervisorManagedObject (pNetworkModelObjectManager);

    addManagedClass (HypervisorManagedObject::getClassName (),    this);
    addManagedClass (KvmHypervisorManagedObject::getClassName (), this);

    hypervisorManagedObject.setupOrm    ();
    kvmHypervisorManagedObject.setupOrm ();
}

HypervisorWorker::~HypervisorWorker ()
{
}

WaveManagedObject *HypervisorWorker::createManagedObjectInstance (const string &managedObjectClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    NetworkModelObjectManager *pNetworkModelObjectManager = NULL;
    WaveObjectManager         *pWaveObjectManager         = getPWaveObjectManager ();

    waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    pNetworkModelObjectManager = dynamic_cast<NetworkModelObjectManager *> (pWaveObjectManager);

    waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    if ((HypervisorManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new HypervisorManagedObject (pNetworkModelObjectManager);
    }
    else if ((KvmHypervisorManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new KvmHypervisorManagedObject (pNetworkModelObjectManager);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("HypervisorWorker::createManagedObjectInstance : Unknown Managed Object Class Name : ") + managedObjectClassName);

        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

}
