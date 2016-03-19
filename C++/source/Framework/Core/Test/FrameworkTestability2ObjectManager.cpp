/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/FrameworkTestability2ObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Messaging/Local/Test/FrameworkTestabilityEvents.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestTypes.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager.h"
#include "Framework/Core/WaveNewNodesAddedEvent.h"
#include "Framework/Core/WaveNodesAdditionToClusterCompletedEvent.h"
#include "Framework/Core/WaveNodeLocalNodeDeletedEvent.h"
#include "Framework/Core/PrimaryChangedEvent.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Persistence/StartupSchemaChangeEvent.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

FrameworkTestability2ObjectManager::FrameworkTestability2ObjectManager ()
    : WaveLocalObjectManager ("Framework Testability2")
{
}

FrameworkTestability2ObjectManager *FrameworkTestability2ObjectManager::getInstance ()
{
    static FrameworkTestability2ObjectManager *pFrameworkTestability2ObjectManager = NULL;

    if (NULL == pFrameworkTestability2ObjectManager)
    {
        pFrameworkTestability2ObjectManager = new FrameworkTestability2ObjectManager ();
        WaveNs::waveAssert (NULL != pFrameworkTestability2ObjectManager, __FILE__, __LINE__);
    }

    return (pFrameworkTestability2ObjectManager);
}

FrameworkTestability2ObjectManager::~FrameworkTestability2ObjectManager ()
{
}

WaveServiceId FrameworkTestability2ObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void FrameworkTestability2ObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (FrameworkLocalMessagingTestObjectManager::getWaveServiceId (), FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT1, reinterpret_cast<WaveEventHandler> (&FrameworkTestability2ObjectManager::frameworkTestabilityEvent1EventHandler));
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_ADDITION_OF_NEW_NODES_EVENT, reinterpret_cast<WaveEventHandler> (&FrameworkTestability2ObjectManager::WaveNewNodesAddedEventHandler));
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_NODES_ADDITION_TO_CLUSTER_COMPLETED_EVENT, reinterpret_cast<WaveEventHandler> (&FrameworkTestability2ObjectManager::WaveNodesAdditionToClusterCompletedEventHandler));
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_LOCAL_NODE_DELETED_EVENT, reinterpret_cast<WaveEventHandler> (&FrameworkTestability2ObjectManager::WaveNodeLocalNodeDeletedEventHandler));
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_EVENT, reinterpret_cast<WaveEventHandler> (&FrameworkTestability2ObjectManager::PrimaryChangedEventHandler));
    listenForEvent (PersistenceLocalObjectManager::getWaveServiceId (), STARTUP_SCHEMA_CHANGE_EVENT, reinterpret_cast<WaveEventHandler> (&FrameworkTestability2ObjectManager::StartupSchemaChangeEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void FrameworkTestability2ObjectManager::frameworkTestabilityEvent1EventHandler (const FrameworkTestabilityEvent1 *&pEvent)
{
    static UI32 numberOfEventsRceivedSoFar = 0;

    numberOfEventsRceivedSoFar++;

    if (0 == (numberOfEventsRceivedSoFar % 10000))
    {
        trace (TRACE_LEVEL_INFO, string ("FrameworkTestability2ObjectManager::frameworkTestabilityEvent1EventHandler : Received Events ... ") + numberOfEventsRceivedSoFar);
        trace (TRACE_LEVEL_DEBUG, string ("m_eventUI32   = ") + pEvent->getEventUI32 ());
        trace (TRACE_LEVEL_DEBUG, string ("m_eventString = ") + pEvent->getEventString ());
    }

     reply (reinterpret_cast<const WaveEvent *&> (pEvent));
}

/// Name
/// WaveNewNodesAddedEventHandler
/// Description
/// Test Handler for handling broadcast event thrown during add node
/// or cluster creation
/// Input
/// const WaveNewNodesAddedEvent* & : Actual event object
/// Output
/// none
/// Return
/// none
void FrameworkTestability2ObjectManager::WaveNewNodesAddedEventHandler(const WaveNewNodesAddedEvent* & pEvent)
{
  trace(TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::WaveNewNodesAddedEventHandler..Entering");
  UI32 number_of_nodes = pEvent->getNumberOfNewLocations();

  for(UI32 i=0; i<number_of_nodes; ++i)
  {
      tracePrintf(TRACE_LEVEL_INFO,"IpAddress: %s: Port: %d: LocationId: %d",pEvent->getIpAddressAtIndex(i).c_str(), pEvent->getPortAtIndex(i), pEvent->getLocationIdAtIndex(i));
  }

   reply (reinterpret_cast<const WaveEvent *&> (pEvent));

   trace(TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::WaveNewNodesAddedEventHandler..Exiting");
  return;

}

/// Name
/// WaveNodesAdditionToClusterCompletedEventHandler
/// Description
/// Test Handler for handling broadcast event thrown after the completion of cluster formation
/// Input
/// const WaveNodesAdditionToClusterCompletedEvent* & : Actual event object
/// Output
/// none
/// Return
/// none
void FrameworkTestability2ObjectManager::WaveNodesAdditionToClusterCompletedEventHandler(const WaveNodesAdditionToClusterCompletedEvent* & pEvent)
{
  trace(TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::WaveNodesAdditionToClusterCompletedEventHandler..Entering");
  UI32 number_of_nodes = pEvent->getNumberOfNewLocations();

  for(UI32 i=0; i<number_of_nodes; ++i)
  {
      tracePrintf(TRACE_LEVEL_INFO,"IpAddress: %s: Port: %d: LocationId: %d",pEvent->getIpAddressAtIndex(i).c_str(), pEvent->getPortAtIndex(i), pEvent->getLocationIdAtIndex(i));
  }

   reply (reinterpret_cast<const WaveEvent *&> (pEvent));

   trace(TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::WaveNodesAdditionToClusterCompletedEventHandler..Exiting");
  return;

}


/// Name
/// WaveNodeLocalNodeDeletedEventHandler
/// Description
/// Test Handler for handling broadcast event thrown during delete
/// node on the secondary
/// Input
/// const WaveNewNodesAddedEvent* & : Actual event object
/// Output
/// none
/// Return
/// none
void FrameworkTestability2ObjectManager::WaveNodeLocalNodeDeletedEventHandler(const WaveNodeLocalNodeDeletedEvent* & pEvent)
{
  trace(TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::WaveNodeLocalNodeDeletedEventHandler..Entering");

  reply (reinterpret_cast<const WaveEvent *&> (pEvent));

  return;
}

// Name : PrimaryChangedEventHandler
// Description : The handler for an event PrimaryChangedEvent which is broadcasted by New Primary and all secondaries in a
//               cluster on Old Primary failover.
// Input       : const PrimaryChangedEvent* & : actual event object
// Output      : None.

void FrameworkTestability2ObjectManager::PrimaryChangedEventHandler (const PrimaryChangedEvent* &pEvent)
{
    trace (TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::PrimaryChangedEventHandler : Entering...");
    const LocationId newPrimaryLocation = pEvent->getNewPrimaryLocationId ();

    trace (TRACE_LEVEL_INFO, string("New Primary locationId : ") + newPrimaryLocation);

    reply (reinterpret_cast<const WaveEvent *&> (pEvent));

    trace (TRACE_LEVEL_INFO, "FrameworkTestability2ObjectManager::PrimaryChangedEventHandler : Exiting...");
    return;
}

void FrameworkTestability2ObjectManager::StartupSchemaChangeEventHandler (const StartupSchemaChangeEvent* & pEvent)
{
    trace (TRACE_LEVEL_DEBUG, "FrameworkTestability2ObjectManager::StartupSchemaChangeEventHandler : Entering...");

    const bool          operationStatus = pEvent->getOperationStatus ();
    const SchemaType    fromSchema      = pEvent->getFromSchema ();
    const string        schemaFile      = pEvent->getFromFileSchemaPath ();
    const SchemaType    toSchema        = pEvent->getToSchema ();
    const string        toSchemaFile    = pEvent->getToFileSchemaPath ();

    trace (TRACE_LEVEL_DEBUG, string ("Operation status : ") + operationStatus);

    string originSchema = pEvent->getSchemaName (fromSchema);
    string targetSchema = pEvent->getSchemaName (toSchema);

    trace (TRACE_LEVEL_DEBUG, string ("operation is : COPY ") + originSchema + string (" ") + targetSchema);

    trace (TRACE_LEVEL_DEBUG, string ("fromFilePath : ") + schemaFile);
    trace (TRACE_LEVEL_DEBUG, string ("toFilePath : ") + toSchemaFile);

    reply (reinterpret_cast<const WaveEvent *&> (pEvent));
}

}
