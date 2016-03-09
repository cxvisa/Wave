/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardWorker.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardingCategoryManagedObject.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

NetworkDeviceReadShardWorker::NetworkDeviceReadShardWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    NetworkDeviceReadShardingCategoryManagedObject networkDeviceReadShardingCategoryManagedObject (pWaveObjectManager);
    NetworkDeviceReadShardDataManagedObject networkDeviceReadShardDataManagedObject (pWaveObjectManager);

    networkDeviceReadShardingCategoryManagedObject.setupOrm ();
    networkDeviceReadShardDataManagedObject.setupOrm ();

    addManagedClass (NetworkDeviceReadShardingCategoryManagedObject::getClassName(), this);
    addManagedClass (NetworkDeviceReadShardDataManagedObject::getClassName(), this);
}

NetworkDeviceReadShardWorker::~NetworkDeviceReadShardWorker ()
{
}

void NetworkDeviceReadShardWorker::install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "NetworkDeviceReadShardWorker::install : Entering ...");

    trace (TRACE_LEVEL_INFO, "NetworkDeviceReadShardWorker::install : Installing Network Device Read Shard Category.");

    startTransaction ();

    NetworkDeviceReadShardingCategoryManagedObject *pNetworkDeviceReadShardingCategoryManagedObject = new NetworkDeviceReadShardingCategoryManagedObject (getPWaveObjectManager ());

    pNetworkDeviceReadShardingCategoryManagedObject->setName (FrameworkToolKit::localize (WAVE_EXTERNAL_SERVICE_SHARD_CATEGORY_TOKEN_NETWORK_DEVICE_READ));

    ResourceId commitStatus = commitTransaction ();

    delete pNetworkDeviceReadShardingCategoryManagedObject;

    if (FRAMEWORK_SUCCESS != commitStatus)
    {
        tracePrintf (TRACE_LEVEL_ERROR, "NetworkDeviceReadShardWorker::install : Failed to install the Network Device Read Shard Category.  Details : %s", FrameworkToolKit::localize (commitStatus));

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
