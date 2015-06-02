/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveObjectManagerToolKit.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/MultiThreading/PrismThread.h"
#include "Framework/Utils/AssertUtils.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

WaveMessageStatus WaveObjectManagerToolKit::sendOneWay (PrismMessage *pPrismMessage, const LocationId &locationId)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->sendOneWay (pPrismMessage, locationId));
}

WaveMessageStatus WaveObjectManagerToolKit::sendOneWayToFront (PrismMessage *pPrismMessage, const LocationId &locationId)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->sendOneWayToFront (pPrismMessage, locationId));
}

WaveMessageStatus WaveObjectManagerToolKit::sendSynchronously (PrismMessage *pPrismMessage, const LocationId &locationId)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->sendSynchronously (pPrismMessage, locationId));
}

ResourceId WaveObjectManagerToolKit::sendSynchronouslyToWaveClient (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, const SI32 &Instance)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->sendSynchronouslyToWaveClient (waveClientName, pManagementInterfaceMessage, Instance));
}

WaveMessageStatus WaveObjectManagerToolKit::sendToWaveServer (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, PrismMessageResponseHandler messageCallback, PrismElement *pPrismMessageSender, void *pInputContext, UI32 timeOutInMilliSeconds)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->sendToWaveServer (waveServerId, pManagementInterfaceMessage, messageCallback, pPrismMessageSender, pInputContext, timeOutInMilliSeconds));
}

ResourceId WaveObjectManagerToolKit::sendOneWayToAllWaveClients (ManagementInterfaceMessage *pManagementInterfaceMessage)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->sendOneWayToAllWaveClients (pManagementInterfaceMessage));
}

vector<WaveManagedObject *> *WaveObjectManagerToolKit::querySynchronously (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronously (pWaveManagedObjectSynchronousQueryContext));
}

vector<WaveManagedObject *> *WaveObjectManagerToolKit::querySynchronously (const string &managedClassName, const string &schema)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronously (managedClassName, schema));
}

vector<WaveManagedObject *> *WaveObjectManagerToolKit::querySynchronously (const string &managedClassName, vector<ObjectId> &objectIds, const string &schema)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronously (managedClassName, objectIds, schema));
}

vector<WaveManagedObject *> *WaveObjectManagerToolKit::querySynchronouslyByName (const string &managedClassName, const string &managedObjectName, const string &schema)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronouslyByName (managedClassName, managedObjectName, schema));
}

vector<WaveManagedObject *> *WaveObjectManagerToolKit:: querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronouslyLocalManagedObjectsForLocationId (locationId, className));
}

WaveManagedObject *WaveObjectManagerToolKit::queryManagedObject (const ObjectId &managedObjectId, const string &schema)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->queryManagedObject (managedObjectId, schema));
}

ResourceId WaveObjectManagerToolKit::querySynchronouslyForCount (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext, UI32 &count)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronouslyForCount (pWaveManagedObjectSynchronousQueryContext, count));
}

ResourceId WaveObjectManagerToolKit::querySynchronouslyForCount (const string &managedClassName, UI32 &count, const string &schema)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronouslyForCount (managedClassName, count, schema));
}

ResourceId WaveObjectManagerToolKit::querySynchronouslyForCount (const string &managedClassName, const string &fieldName, const string &range, UI32 &count, const string &schema)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    return (pWaveObjectManagerForCurrentThread->querySynchronouslyForCount (managedClassName, fieldName, range, count, schema));
}

void WaveObjectManagerToolKit::getWaveConfigEntry (string &configName, Attribute *attribute, bool &configFound)
{
    WaveObjectManager *pWaveObjectManagerForCurrentThread = PrismThread::getWaveObjectManagerForCurrentThread ();

    prismAssert (NULL != pWaveObjectManagerForCurrentThread, __FILE__, __LINE__);

    pWaveObjectManagerForCurrentThread->getWaveConfigEntry (configName, attribute, configFound);

	return;
}
}
