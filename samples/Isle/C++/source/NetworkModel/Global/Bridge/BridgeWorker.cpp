/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Bridge/BridgeWorker.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "NetworkModel/Global/Bridge/BridgeManagedObject.h"
#include "NetworkModel/Global/Bridge/OvsBridgeManagedObject.h"

namespace IsleNs
{

BridgeWorker::BridgeWorker (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveWorker (pNetworkModelObjectManager)
{
    BridgeManagedObject    bridgeManagedObject    (pNetworkModelObjectManager);
    OvsBridgeManagedObject ovsBridgeManagedObject (pNetworkModelObjectManager);

    addManagedClass (BridgeManagedObject::getClassName    (), this);
    addManagedClass (OvsBridgeManagedObject::getClassName (), this);

    bridgeManagedObject.setupOrm    ();
    ovsBridgeManagedObject.setupOrm ();
}

BridgeWorker::~BridgeWorker ()
{
}

WaveManagedObject *BridgeWorker::createManagedObjectInstance (const string &managedObjectClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    NetworkModelObjectManager *pNetworkModelObjectManager = NULL;
    WaveObjectManager         *pWaveObjectManager         = getPWaveObjectManager ();

    waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    pNetworkModelObjectManager = dynamic_cast<NetworkModelObjectManager *> (pWaveObjectManager);

    waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

    if ((BridgeManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new BridgeManagedObject (pNetworkModelObjectManager);
    }
    else if ((OvsBridgeManagedObject::getClassName ()) == managedObjectClassName)
    {
        pWaveManagedObject = new OvsBridgeManagedObject (pNetworkModelObjectManager);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("BridgeWorker::createManagedObjectInstance : Unknown Managed Object Class Name : ") + managedObjectClassName);

        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}
}
