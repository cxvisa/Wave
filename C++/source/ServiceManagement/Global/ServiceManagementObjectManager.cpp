/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/ServiceManagementObjectManager.h"
#include "ServiceManagement/Global/ExternalNonNativeServiceManagedObject.h"
#include "ServiceManagement/Global/ShardableResourceCategory.h"
#include "ServiceManagement/Global/ShardData.h"
#include "ServiceManagement/Global/AddExternalNonNativeServiceWorker.h"
#include "Sharding/ShardingCapabilitiesToolKit.h"

namespace WaveNs
{

ServiceManagementObjectManager::ServiceManagementObjectManager ()
    : WaveObjectManager (getServiceName ())
{

    ShardingCapabilitiesToolKit::initialize ();

    ShardableResourceCategory shardableResourceCategory (this);
    ShardData shardData (this);

    shardableResourceCategory.setupOrm ();
    shardData.setupOrm ();

    addManagedClass (ShardableResourceCategory::getClassName ());
    addManagedClass (ShardData::getClassName ());

    m_pAddExternalNonNativeServiceWorker = new AddExternalNonNativeServiceWorker (this);

    waveAssert (NULL != m_pAddExternalNonNativeServiceWorker, __FILE__, __LINE__);
}

ServiceManagementObjectManager::~ServiceManagementObjectManager ()
{
    if (NULL != m_pAddExternalNonNativeServiceWorker)
    {
        delete m_pAddExternalNonNativeServiceWorker;
        m_pAddExternalNonNativeServiceWorker = NULL;
    }
}

ServiceManagementObjectManager *ServiceManagementObjectManager:: getInstance ()
{
    static ServiceManagementObjectManager *pServiceManagementObjectManagerObjectManager = new ServiceManagementObjectManager ();

    WaveNs::waveAssert (NULL != pServiceManagementObjectManagerObjectManager, __FILE__, __LINE__);

    return (pServiceManagementObjectManagerObjectManager);
}

WaveServiceId ServiceManagementObjectManager:: getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string ServiceManagementObjectManager::getServiceName ()
{
    return ("Service Management");
}

}
