/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/ServiceManagementLocalObjectManager.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"

namespace WaveNs
{

ServiceManagementLocalObjectManager::ServiceManagementLocalObjectManager ()
    : WaveObjectManager (getServiceName ())
{
    ExternalNonNativeServiceInstanceManagedObject externalNonNativeServiceInstanceManagedObject (this);

    externalNonNativeServiceInstanceManagedObject.setupOrm ();

    addManagedClass (ExternalNonNativeServiceInstanceManagedObject::getClassName());
}

ServiceManagementLocalObjectManager::~ServiceManagementLocalObjectManager ()
{
}

ServiceManagementLocalObjectManager *ServiceManagementLocalObjectManager:: getInstance ()
{
    static ServiceManagementLocalObjectManager *pServiceManagementObjectManagerObjectManager = new ServiceManagementLocalObjectManager ();

    WaveNs::waveAssert (NULL != pServiceManagementObjectManagerObjectManager, __FILE__, __LINE__);

    return (pServiceManagementObjectManagerObjectManager);
}

WaveServiceId ServiceManagementLocalObjectManager:: getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string ServiceManagementLocalObjectManager::getServiceName ()
{
    return ("Service Management Local");
}

}
