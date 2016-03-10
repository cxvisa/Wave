/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/ServiceInstanceToolKit.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"

#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveObjectManagerToolKit.h"
#include "ServiceManagement/Local/ExternalNonNativeServiceInstanceManagedObject.h"
#include "Sharding/NetworkDeviceRead/NetworkDeviceReadShardDataManagedObject.h"
#include "Sharding/NetworkDeviceWrite/NetworkDeviceWriteShardDataManagedObject.h"

namespace WaveNs
{

ServiceInstanceToolKit::ServiceInstanceToolKit ()
{
}

ServiceInstanceToolKit::~ServiceInstanceToolKit ()
{
}

ExternalNonNativeServiceInstanceManagedObject *ServiceInstanceToolKit::getServiceInstanceByName (const string &name)
{
    const string className = ExternalNonNativeServiceInstanceManagedObject::getClassName ();

    vector<WaveManagedObject *> *pQueryResults = WaveObjectManagerToolKit::querySynchronouslyByName (className, name);

    WaveNs::waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    const UI32 numberOfQueryResults = pQueryResults->size ();

    if (0 == numberOfQueryResults)
    {
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

        return (NULL);
    }
    else if (1 == numberOfQueryResults)
    {
        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[0];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        ExternalNonNativeServiceInstanceManagedObject *pExternalNonNativeServiceInstanceManagedObject = dynamic_cast<ExternalNonNativeServiceInstanceManagedObject *> (pWaveManagedObject);

        WaveNs::waveAssert (NULL != pExternalNonNativeServiceInstanceManagedObject, __FILE__, __LINE__);

        pQueryResults->clear ();

        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pQueryResults);

        return (pExternalNonNativeServiceInstanceManagedObject);
    }
    else
    {
        WaveNs::waveAssert (false, __FILE__, __LINE__);
    }

    return (NULL);
}

}
