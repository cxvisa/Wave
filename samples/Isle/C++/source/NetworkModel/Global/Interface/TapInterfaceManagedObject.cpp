/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Interface/TapInterfaceManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "NetworkModel/Global/Bridge/BridgeManagedObject.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectModel/WaveObjectManagerToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"

namespace IsleNs
{

TapInterfaceManagedObject::TapInterfaceManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager)
    : WaveElement                   (pNetworkModelObjectManager),
      WavePersistableObject         (TapInterfaceManagedObject::getClassName (), VirtualInterfaceManagedObject::getClassName ()),
      WaveManagedObject             (pNetworkModelObjectManager),
      IsleManagedObject             (pNetworkModelObjectManager),
      InterfaceManagedObject        (pNetworkModelObjectManager),
      VirtualInterfaceManagedObject (pNetworkModelObjectManager)
{
}

TapInterfaceManagedObject::~TapInterfaceManagedObject ()
{
}

string TapInterfaceManagedObject::getClassName ()
{
    return ("TapInterfaceManagedObject");
}

void TapInterfaceManagedObject::setupAttributesForCreate ()
{
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_bridge, "bridge", BridgeManagedObject::getClassName (), true));
    addPersistableAttributeForCreate (new AttributeUI32                (&m_id,     "id"));
}

void TapInterfaceManagedObject::setupAttributesForPersistence ()
{
    VirtualInterfaceManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeObjectIdAssociation (&m_bridge, "bridge", BridgeManagedObject::getClassName (), true));
    addPersistableAttribute (new AttributeUI32                (&m_id,     "id"));
}

string TapInterfaceManagedObject::getUserDefinedKeyCombinationValueForJson () const
{
    WaveManagedObject         *pWaveManagedObject         = WaveObjectManagerToolKit::queryManagedObject (getObjectId ());
    TapInterfaceManagedObject *pTapInterfaceManagedObject = NULL;
    ObjectId                   bridge;
    UI32                       id                         = 0;

    if (NULL != pWaveManagedObject)
    {
        pTapInterfaceManagedObject = dynamic_cast<TapInterfaceManagedObject *> (pWaveManagedObject);

        if (NULL != pTapInterfaceManagedObject)
        {
            bridge = pTapInterfaceManagedObject->getBridge ();
            id     = pTapInterfaceManagedObject->getId     ();

            delete pTapInterfaceManagedObject;
        }
    }

    pWaveManagedObject = NULL;

    if (ObjectId::NullObjectId != bridge)
    {
        pWaveManagedObject = WaveObjectManagerToolKit::queryManagedObject (bridge);
    }

    BridgeManagedObject *pBridgeManagedObject = NULL;
    string               jsonString;

    if (NULL != pWaveManagedObject)
    {
        pBridgeManagedObject = dynamic_cast<BridgeManagedObject *> (pWaveManagedObject);
    }

    if (NULL != pBridgeManagedObject)
    {
        jsonString = pBridgeManagedObject->getId () + "/";

        delete pBridgeManagedObject;
    }

    jsonString = jsonString + id;

    return (jsonString);
}

const ObjectId &TapInterfaceManagedObject::getBridge () const
{
    return (m_bridge);
}

void TapInterfaceManagedObject::setBridge (const ObjectId &bridge)
{
    m_bridge = bridge;
}

const UI32 &TapInterfaceManagedObject::getId () const
{
    return (m_id);
}

void TapInterfaceManagedObject::setId (const UI32 &id)
{
    m_id = id;
}

TapInterfaceManagedObject *TapInterfaceManagedObject::getByBridgeAndId (const ObjectId &bridge, const UI32 &id)
{
    WaveManagedObjectSynchronousQueryContext queryContextForTapInterface (TapInterfaceManagedObject::getClassName ());

    queryContextForTapInterface.addAndAttribute (new AttributeObjectIdAssociation (bridge, "bridge", BridgeManagedObject::getClassName ()), WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
    queryContextForTapInterface.addAndAttribute (new AttributeUI32                (id,     "id"),                                           WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);

    vector<WaveManagedObject *> *pResultsVector = WaveObjectManagerToolKit::querySynchronously (&queryContextForTapInterface);

    WaveNs::waveAssert (NULL != pResultsVector, __FILE__, __LINE__);

    if (NULL == pResultsVector)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "TapInterfaceManagedObject::getByBridgeAndId : Query for Tap Interface Failed.");

        return (NULL);
    }

    const UI32 resultCount = pResultsVector->size ();

    if (1 < resultCount)
    {
        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "TapInterfaceManagedObject::getByBridgeAndId : Tap Interface query resulted in more than one entry.  Count : %d", resultCount);

        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResultsVector);

        return (NULL);

    }
    else if (1 == resultCount)
    {
        WaveManagedObject *pWaveManagedObject = (*(pResultsVector))[0];

        WaveNs::waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        TapInterfaceManagedObject *pTapInterfaceManagedObject = dynamic_cast<TapInterfaceManagedObject *> (pWaveManagedObject);

        WaveNs::waveAssert (NULL != pTapInterfaceManagedObject, __FILE__, __LINE__);

        pResultsVector->clear ();

        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResultsVector);

        return (pTapInterfaceManagedObject);
    }

    return (NULL);
}

const string TapInterfaceManagedObject::getBridgeId () const
{
    if (ObjectId::NullObjectId == m_bridge)
    {
        return ("");
    }

    WaveManagedObject *pWaveManagedObject = WaveObjectManagerToolKit::queryManagedObject (m_bridge);

    if (NULL == pWaveManagedObject)
    {
        return ("");
    }

    BridgeManagedObject *pBridgeManagedObject = dynamic_cast<BridgeManagedObject *> (pWaveManagedObject);

    if (NULL == pBridgeManagedObject)
    {
        return ("");
    }

    const string bridgeId = pBridgeManagedObject->getId ();

    delete pBridgeManagedObject;

    return (bridgeId);
}

}
