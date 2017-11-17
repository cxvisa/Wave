/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Bridge/BridgeManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "NetworkModel/Global/Interface/TapInterfaceManagedObject.h"
#include "NetworkModel/Global/Hypervisor/HypervisorManagedObject.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveObjectManagerToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"

namespace IsleNs
{

BridgeManagedObject::BridgeManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement           (pNetworkModelObjectManager),
      WavePersistableObject (BridgeManagedObject::getClassName (), IsleManagedObject::getClassName ()),
      WaveManagedObject     (pNetworkModelObjectManager),
      IsleManagedObject     (pNetworkModelObjectManager)
{
}

BridgeManagedObject::~BridgeManagedObject ()
{
}

string BridgeManagedObject::getClassName ()
{
    return ("BridgeManagedObject");
}

void BridgeManagedObject::setupAttributesForCreate ()
{
    IsleManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeString                    (&m_id,            "id"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAggregation (&m_tapInterfaces, "tapInterfaces", getClassName (), getObjectId (), TapInterfaceManagedObject::getClassName ()));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation       (&m_hypervisor,    "hypervisor",    HypervisorManagedObject::getClassName (), true));
}

void BridgeManagedObject::setupAttributesForPersistence ()
{
    IsleManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeString                    (&m_id,            "id"));
    addPersistableAttribute (new AttributeObjectIdVectorAggregation (&m_tapInterfaces, "tapInterfaces", getClassName (), getObjectId (), TapInterfaceManagedObject::getClassName ()));
    addPersistableAttribute (new AttributeObjectIdAssociation       (&m_hypervisor,    "hypervisor",    HypervisorManagedObject::getClassName (), true));
}

const string &BridgeManagedObject::getId () const
{
    return (m_id);
}

void BridgeManagedObject::setId (const string &id)
{
    m_id = id;
}

vector<ObjectId> &BridgeManagedObject::getTapInterfaces ()
{
    return (m_tapInterfaces);
}

const ObjectId &BridgeManagedObject::getHypervisor () const
{
    return (m_hypervisor);
}

void BridgeManagedObject::setHypervisor (const ObjectId &hypervisor)
{
    m_hypervisor = hypervisor;
}

ObjectId BridgeManagedObject::getObjectIdById (const string &id)
{
    WaveManagedObjectSynchronousQueryContext queryContextForBridge (BridgeManagedObject::getClassName ());

    queryContextForBridge.addAndAttribute (new AttributeString (id, "id"), WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);

    queryContextForBridge.addSelectField ("objectId");

    vector<WaveManagedObject *> *pResultsVector = WaveObjectManagerToolKit::querySynchronously (&queryContextForBridge);

    WaveNs::waveAssert (NULL != pResultsVector, __FILE__, __LINE__);

    if (NULL == pResultsVector)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "BridgeManagedObject::getObjectIdById : Query for Bridge by Id Failed.");

        return (ObjectId::NullObjectId);
    }

    const UI32 resultCount = pResultsVector->size ();

    if (1 < resultCount)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "BridgeManagedObject::getObjectIdById : Bridge by id query resulted in more than one entry.  Count : %d", resultCount);

        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResultsVector);

        return (ObjectId::NullObjectId);

    }
    else if (1 == resultCount)
    {
        WaveManagedObject *pWaveManagedObject = (*(pResultsVector))[0];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        BridgeManagedObject *pBridgeManagedObject = dynamic_cast<BridgeManagedObject *> (pWaveManagedObject);

        WaveNs::waveAssert (NULL != pBridgeManagedObject, __FILE__, __LINE__);

        ObjectId bridgeObjectId = pBridgeManagedObject->getObjectId ();

        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResultsVector);

        return (bridgeObjectId);
    }

    return (ObjectId::NullObjectId);
}

}
