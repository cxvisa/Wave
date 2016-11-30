/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardWorker.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardingCategoryManagedObject.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

NetworkDeviceWriteShardWorker::NetworkDeviceWriteShardWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    NetworkDeviceWriteShardingCategoryManagedObject networkDeviceWriteShardingCategoryManagedObject (pWaveObjectManager);
    NetworkDeviceWriteShardDataManagedObject networkDeviceWriteShardDataManagedObject (pWaveObjectManager);

    networkDeviceWriteShardingCategoryManagedObject.setupOrm ();
    networkDeviceWriteShardDataManagedObject.setupOrm ();

    addManagedClass (NetworkDeviceWriteShardingCategoryManagedObject::getClassName(), this);
    addManagedClass (NetworkDeviceWriteShardDataManagedObject::getClassName(), this);
}

NetworkDeviceWriteShardWorker::~NetworkDeviceWriteShardWorker ()
{
}

void NetworkDeviceWriteShardWorker::install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "NetworkDeviceWriteShardWorker::install : Entering ...");

    trace (TRACE_LEVEL_INFO, "NetworkDeviceWriteShardWorker::install : Installing Network Device Write Shard Category.");

    startTransaction ();

    NetworkDeviceWriteShardingCategoryManagedObject *pNetworkDeviceWriteShardingCategoryManagedObject = new NetworkDeviceWriteShardingCategoryManagedObject (getPWaveObjectManager ());

    pNetworkDeviceWriteShardingCategoryManagedObject->setName (FrameworkToolKit::localize (WAVE_EXTERNAL_SERVICE_SHARD_CATEGORY_TOKEN_NETWORK_DEVICE_WRITE));

    ResourceId commitStatus = commitTransaction ();

    delete pNetworkDeviceWriteShardingCategoryManagedObject;

    if (FRAMEWORK_SUCCESS != commitStatus)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "NetworkDeviceWriteShardWorker::install : Failed to install the Network Device Write Shard Category.  Details : %s", (FrameworkToolKit::localize (commitStatus)).c_str ());

        pWaveAsynchronousContextForBootPhases->setCompletionStatus (commitStatus);
        pWaveAsynchronousContextForBootPhases->callback ();
        return;
    }
    else
    {
        pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        pWaveAsynchronousContextForBootPhases->callback ();
        return;
    }
}

}
