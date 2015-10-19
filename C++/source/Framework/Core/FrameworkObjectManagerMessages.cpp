/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "Framework/Attributes/AttributeSerializableObject.cpp"

namespace WaveNs
{

WaveCreateClusterWithNodesMessage::WaveCreateClusterWithNodesMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode),
      m_currentValidtionResultsBufferTag (0),
      m_isAddNodeForSpecialCase (false)
{
}

WaveCreateClusterWithNodesMessage::WaveCreateClusterWithNodesMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CREATE_CLUSTER_WITH_NODES),
      m_currentValidtionResultsBufferTag (0),
      m_isAddNodeForSpecialCase (false)
{
}

WaveCreateClusterWithNodesMessage::~WaveCreateClusterWithNodesMessage ()
{
}

bool WaveCreateClusterWithNodesMessage::isNewNodeIpAddressExists (const string &newNodeIpAddress, const SI32 &newNodePort)
{
    bool exists              = false;
    UI32 numberOfIpAddresses = m_newNodesIpAddresses.size ();
    UI32 i                   = 0;

    for (i = 0; i < numberOfIpAddresses; i++)
    {
        if ((newNodeIpAddress == m_newNodesIpAddresses[i]) && (newNodePort == m_newNodesPorts[i]))
        {
            exists = true;
            break;
        }
    }

    return (exists);
}

void WaveCreateClusterWithNodesMessage::addNewNodeIpAddressAndPort (const string &newNodeIpAddress, const SI32 &newNodePort)
{
    if (false == (isNewNodeIpAddressExists (newNodeIpAddress, newNodePort)))
    {
        m_newNodesIpAddresses.push_back (newNodeIpAddress);
        m_newNodesPorts.push_back (newNodePort);
    }
    else
    {
        // Adding duplicate ip addresses.

        trace (TRACE_LEVEL_FATAL, "WaveCreateClusterWithNodesMessage::addNewNodeIpAddressAndPort : Adding duplicate IP Address and Port.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

UI32 WaveCreateClusterWithNodesMessage::getNumberOfNewNodes ()
{
    return (m_newNodesIpAddresses.size ());
}

string WaveCreateClusterWithNodesMessage::getNodeAt (UI32 i)
{
    if (i < (m_newNodesIpAddresses.size ()))
    {
        return (m_newNodesIpAddresses[i]);
    }
    else
    {
        // index out of range.

        trace (TRACE_LEVEL_FATAL, string ("WaveCreateClusterWithNodesMessage::getNodeAt : Index out of range, i = ") + i + string (" , Max Allowed = ") + m_newNodesIpAddresses.size ());
        waveAssert (false, __FILE__, __LINE__);

        return (string (""));
    }
}

SI32 WaveCreateClusterWithNodesMessage::getNodePortAt (UI32 i)
{
    if (i < (m_newNodesPorts.size ()))
    {
        return (m_newNodesPorts[i]);
    }
    else
    {
        // index out of range.

        trace (TRACE_LEVEL_FATAL, string ("WaveCreateClusterWithNodesMessage::getNodePortAt : Index out of range, i = ") + i + string (" , Max Allowed = ") + m_newNodesPorts.size ());
        waveAssert (false, __FILE__, __LINE__);

        return (0);
    }
}

void WaveCreateClusterWithNodesMessage::setNewNodeStatus (const string &newNodeIpAddress, const SI32 &newNodePort, ResourceId status)
{
    string                            uniqueTag = newNodeIpAddress + "#" + newNodePort;
    map<string, ResourceId>::iterator element   = m_newNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_newNodesStatus.end ();

    if (end == element)
    {
        m_newNodesStatus[uniqueTag] = status;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveCreateClusterWithNodesMessage::setNewNodeStatus : This node (") + newNodeIpAddress + ":" + newNodePort + ") status is already set.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

void WaveCreateClusterWithNodesMessage::updateNewNodeStatus (const string &newNodeIpAddress, const SI32 &newNodePort, ResourceId status)
{
    string                            uniqueTag = newNodeIpAddress + "#" + newNodePort;
    map<string, ResourceId>::iterator element   = m_newNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_newNodesStatus.end ();

    if (end != element)
    {
        m_newNodesStatus[uniqueTag] = status;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveCreateClusterWithNodesMessage::updateNewNodeStatus : This node (") + newNodeIpAddress + ":" + newNodePort + ") status is not previously set.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

ResourceId WaveCreateClusterWithNodesMessage::getNewNodeStatus (const string &newNodeIpAddress, const SI32 &newNodePort)
{
    string                            uniqueTag = newNodeIpAddress + "#" + newNodePort;
    map<string, ResourceId>::iterator element   = m_newNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_newNodesStatus.end ();

    if (end != element)
    {
        return (m_newNodesStatus[uniqueTag]);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveCreateClusterWithNodesMessage::getNewNodeStatus : This node (") + newNodeIpAddress + ":" + newNodePort + ") status is not set.");
        waveAssert (false, __FILE__, __LINE__);
        return (WAVE_MESSAGE_ERROR);
    }
}

bool WaveCreateClusterWithNodesMessage::isNewNodeStatusSet (const string &newNodeIpAddress, const SI32 &newNodePort)
{
    string                            uniqueTag = newNodeIpAddress + "#" + newNodePort;
    map<string, ResourceId>::iterator element   = m_newNodesStatus.find (uniqueTag);
    map<string, ResourceId>::iterator end       = m_newNodesStatus.end ();

    if (end != element)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void WaveCreateClusterWithNodesMessage::setValidationDetails (const UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToMessage)
{
    addBuffer (VALIDATION_DETAILS_BUFFER_TAG, bufferSize, pBuffer, transferBufferOwnershipToMessage);
}

void WaveCreateClusterWithNodesMessage::getValidationDetails (UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToUser)
{
    if (true == transferBufferOwnershipToUser)
    {
        pBuffer = transferBufferToUser (VALIDATION_DETAILS_BUFFER_TAG, bufferSize);
    }
    else
    {
        pBuffer = findBuffer (VALIDATION_DETAILS_BUFFER_TAG, bufferSize);
    }
}

void WaveCreateClusterWithNodesMessage::setValidationResults (const string &newNodeIpAddress, const SI32 &newNodePort, const UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToMessage)
{
    UI32   bufferTag = VALIDATION_RESULTS_BUFFER_TAG + m_currentValidtionResultsBufferTag;
    string uniqueTag = newNodeIpAddress + "#" + newNodePort;

    addBuffer (bufferTag, bufferSize, pBuffer, transferBufferOwnershipToMessage);
    m_newNodeValidationResults[uniqueTag] = bufferTag;

    // Increment it so that the next time we add it will be at the next tag.

    m_currentValidtionResultsBufferTag++;
}

void WaveCreateClusterWithNodesMessage::getValidationResults (const string &newNodeIpAddress, const SI32 &newNodePort, UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToUser)
{
    string                      uniqueTag = newNodeIpAddress + "#" + newNodePort;
    map<string, UI32>::iterator element   = m_newNodeValidationResults.find (uniqueTag);
    map<string, UI32>::iterator end       = m_newNodeValidationResults.end ();

    UI32 bufferTag;

    if (element != end)
    {
        bufferTag = element->second;
    }
    else
    {
        bufferSize = 0;
        pBuffer    = NULL;

        return;
    }

    if (true == transferBufferOwnershipToUser)
    {
        pBuffer = transferBufferToUser (bufferTag, bufferSize);
    }
    else
    {
        pBuffer = findBuffer (bufferTag, bufferSize);
    }
}

void WaveCreateClusterWithNodesMessage::setIsAddNodeForSpecialCaseFlag (const bool &isAddNodeForSpecialCase)
{
    m_isAddNodeForSpecialCase = isAddNodeForSpecialCase;
}

bool WaveCreateClusterWithNodesMessage::getIsAddNodeForSpecialCaseFlag () const
{
    return (m_isAddNodeForSpecialCase);
}

void WaveCreateClusterWithNodesMessage::setFilenamesToSync ( const vector<string> &filenamesToSync )
{   
    m_filenamesToSync = filenamesToSync;
}

void WaveCreateClusterWithNodesMessage::getFilenamesToSync ( vector<string> &filenamesToSync )
{   
    filenamesToSync = m_filenamesToSync;
}

WaveConfigureClusterSecondaryMessage::WaveConfigureClusterSecondaryMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY),
      m_clusterPrimaryPort (0),
      m_clusterPrimaryLocationId (0),
      m_port (0),
      m_locationId (0),
      m_isAddNodeForSpecialCase (false)
{
}

WaveConfigureClusterSecondaryMessage::WaveConfigureClusterSecondaryMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode),
      m_clusterPrimaryPort (0),
      m_clusterPrimaryLocationId (0),
      m_port (0),
      m_locationId (0),
      m_isAddNodeForSpecialCase (false)
{
}

WaveConfigureClusterSecondaryMessage::WaveConfigureClusterSecondaryMessage (WaveServiceId serviceCode, UI32 operationCode, const string &clusterPrimaryWaveVersion, const string &clusterPrimaryIpAddress, const SI32 &clusterPrimaryPort, const LocationId &clusterPrimaryLocationId, const string &ipAddress, const SI32 &port, const LocationId &locationId)
    : WaveMessage (serviceCode, operationCode),
      m_clusterPrimaryWaveVersion (clusterPrimaryWaveVersion),
      m_clusterPrimaryIpAddress (clusterPrimaryIpAddress),
      m_clusterPrimaryPort (clusterPrimaryPort),
      m_clusterPrimaryLocationId (clusterPrimaryLocationId),
      m_ipAddress (ipAddress),
      m_port (port),
      m_locationId (locationId),
      m_isAddNodeForSpecialCase (false)
{
}

WaveConfigureClusterSecondaryMessage::WaveConfigureClusterSecondaryMessage (const string &clusterPrimaryWaveVersion, const string &clusterPrimaryIpAddress, const SI32 &clusterPrimaryPort, const LocationId &clusterPrimaryLocationId, const string &ipAddress, const SI32 &port, const LocationId &locationId)
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY),
      m_clusterPrimaryWaveVersion (clusterPrimaryWaveVersion),
      m_clusterPrimaryIpAddress (clusterPrimaryIpAddress),
      m_clusterPrimaryPort (clusterPrimaryPort),
      m_clusterPrimaryLocationId (clusterPrimaryLocationId),
      m_ipAddress (ipAddress),
      m_port (port),
      m_locationId (locationId),
      m_isAddNodeForSpecialCase (false)
{
}

WaveConfigureClusterSecondaryMessage::~WaveConfigureClusterSecondaryMessage ()
{
}

string WaveConfigureClusterSecondaryMessage::getClusterPrimaryWaveVersion ()
{
    return (m_clusterPrimaryWaveVersion);
}

string WaveConfigureClusterSecondaryMessage::getClusterPrimaryIpAddress ()
{
    return (m_clusterPrimaryIpAddress);
}

SI32 WaveConfigureClusterSecondaryMessage::getClusterPrimaryPort ()
{
    return (m_clusterPrimaryPort);
}

LocationId WaveConfigureClusterSecondaryMessage::getClusterPrimaryLocationId ()
{
    return (m_clusterPrimaryLocationId);
}

string WaveConfigureClusterSecondaryMessage::getIpAddress ()
{
    return (m_ipAddress);
}

SI32 WaveConfigureClusterSecondaryMessage::getPort ()
{
    return (m_port);
}

LocationId WaveConfigureClusterSecondaryMessage::getLocationId ()
{
    return (m_locationId);
}

void WaveConfigureClusterSecondaryMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString     (&m_clusterPrimaryWaveVersion,          "clusterPrimaryWaveVersion"));
     addSerializableAttribute (new AttributeString     (&m_clusterPrimaryIpAddress,             "clusterPrimaryIpAddress"));
     addSerializableAttribute (new AttributeSI32       (&m_clusterPrimaryPort,                  "clusterPrimaryPort"));
     addSerializableAttribute (new AttributeLocationId (&m_clusterPrimaryLocationId,            "clusterPrimaryLocationId"));
     addSerializableAttribute (new AttributeString     (&m_ipAddress,                           "ipAddress"));
     addSerializableAttribute (new AttributeSI32       (&m_port,                                "port"));
     addSerializableAttribute (new AttributeLocationId (&m_locationId,                          "locationId"));
     addSerializableAttribute (new AttributeBool       (&m_isAddNodeForSpecialCase,             "isAddNodeForSpecialCase"));

     addSerializableAttribute (new AttributeStringVector (&m_managedObjectNamesForSchemaChange, "managedObjectNamesForSchemaChange"));
     addSerializableAttribute (new AttributeStringVector (&m_fieldNamesStringsForSchemaChange,  "fieldNamesStringsForSchemaChange"));
     addSerializableAttribute (new AttributeStringVector (&m_fieldNamesTypesForSchemaChange,    "fieldNamesTypesForSchemaChange"));
     addSerializableAttribute (new AttributeUI32Vector   (&m_classIds,                          "classIds"));
     addSerializableAttribute (new AttributeUI32Vector   (&m_parentTableIds,                    "parentTableIds"));

}

void  WaveConfigureClusterSecondaryMessage::getSchemaChangeVectors (vector<string>   & managedObjectNamesForSchemaChange,vector<string>   & fieldNamesStringsForSchemaChange,vector<string> & fieldNamesTypesForSchemaChange,vector<UI32>   & classIds,vector<UI32> & parentTableIds)
{
     managedObjectNamesForSchemaChange = m_managedObjectNamesForSchemaChange;
     fieldNamesStringsForSchemaChange = m_fieldNamesStringsForSchemaChange;
     fieldNamesTypesForSchemaChange = m_fieldNamesTypesForSchemaChange;
     classIds = m_classIds;
     parentTableIds = m_parentTableIds;
}


void  WaveConfigureClusterSecondaryMessage::setSchemaChangeVectors ()
{
     vector<string>  managedObjectNamesForSchemaChange;
     vector<string>  fieldNamesStringsForSchemaChange;
     vector<string>  fieldNamesTypesForSchemaChange;
     vector<UI32>    classIds;
     vector<UI32>    parentTableIds;

     OrmRepository  *pOrmRepository = OrmRepository::getInstance();
     pOrmRepository->getSchemaChangeVectors (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange, classIds, parentTableIds);

     m_managedObjectNamesForSchemaChange = managedObjectNamesForSchemaChange;
     m_fieldNamesStringsForSchemaChange = fieldNamesStringsForSchemaChange;
     m_fieldNamesTypesForSchemaChange = fieldNamesTypesForSchemaChange;
     m_classIds = classIds;
     m_parentTableIds = parentTableIds;
}

void WaveConfigureClusterSecondaryMessage::setValidationDetails (const UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToMessage)
{
    addBuffer (VALIDATION_DETAILS_BUFFER_TAG, bufferSize, pBuffer, transferBufferOwnershipToMessage);
}

void WaveConfigureClusterSecondaryMessage::getValidationDetails (UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToUser)
{
    if (true == transferBufferOwnershipToUser)
    {
        pBuffer = transferBufferToUser (VALIDATION_DETAILS_BUFFER_TAG, bufferSize);
    }
    else
    {
        pBuffer = findBuffer (VALIDATION_DETAILS_BUFFER_TAG, bufferSize);
    }
}

void WaveConfigureClusterSecondaryMessage::setValidationResults (const UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToMessage)
{
    addBuffer (VALIDATION_RESULTS_BUFFER_TAG, bufferSize, pBuffer, transferBufferOwnershipToMessage);
}

void WaveConfigureClusterSecondaryMessage::getValidationResults (UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToUser)
{
    if (true == transferBufferOwnershipToUser)
    {
        pBuffer = transferBufferToUser (VALIDATION_RESULTS_BUFFER_TAG, bufferSize);
    }
    else
    {
        pBuffer = findBuffer (VALIDATION_RESULTS_BUFFER_TAG, bufferSize);
    }
}

void WaveConfigureClusterSecondaryMessage::setIsAddNodeForSpecialCaseFlag (const bool &isAddNodeForSpecialCase)
{
    m_isAddNodeForSpecialCase = isAddNodeForSpecialCase;
}

bool WaveConfigureClusterSecondaryMessage::getIsAddNodeForSpecialCaseFlag () const
{
    return (m_isAddNodeForSpecialCase);
}

WaveConfigureClusterSecondaryHaPeerMessage::WaveConfigureClusterSecondaryHaPeerMessage ()
    : WaveConfigureClusterSecondaryMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER)
{
}

WaveConfigureClusterSecondaryHaPeerMessage::~WaveConfigureClusterSecondaryHaPeerMessage ()
{
}

void WaveConfigureClusterSecondaryHaPeerMessage::setupAttributesForSerialization ()
{
    WaveConfigureClusterSecondaryMessage::setupAttributesForSerialization ();
}

WaveConfigureClusterSecondaryPhase1Message::WaveConfigureClusterSecondaryPhase1Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_1)
{
}

WaveConfigureClusterSecondaryPhase1Message::WaveConfigureClusterSecondaryPhase1Message (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode)
{
}

WaveConfigureClusterSecondaryPhase1Message::~WaveConfigureClusterSecondaryPhase1Message ()
{
}

void WaveConfigureClusterSecondaryPhase1Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
     addSerializableAttribute (new AttributeString (&m_filenameToSync, "filenameToSync"));
}

UI32 WaveConfigureClusterSecondaryPhase1Message::getDatabaseBackupBufferTag ()
{
    return (UINT_MAX);
}

void WaveConfigureClusterSecondaryPhase1Message::setFilenameToSync ( const string &filenameToSync )
{   
    m_filenameToSync = filenameToSync;
}

void WaveConfigureClusterSecondaryPhase1Message::getFilenameToSync ( string &filenameToSync )
{   
    filenameToSync = m_filenameToSync;
}

WaveConfigureClusterSecondaryHaPeerPhase1Message::WaveConfigureClusterSecondaryHaPeerPhase1Message ()
    : WaveConfigureClusterSecondaryPhase1Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER_PHASE_1)
{
}

WaveConfigureClusterSecondaryHaPeerPhase1Message::~WaveConfigureClusterSecondaryHaPeerPhase1Message ()
{
}

void WaveConfigureClusterSecondaryHaPeerPhase1Message::setupAttributesForSerialization ()
{
    WaveConfigureClusterSecondaryPhase1Message::setupAttributesForSerialization ();
}

WaveConfigureClusterSecondaryPhase2Message::WaveConfigureClusterSecondaryPhase2Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_2)
{
}

WaveConfigureClusterSecondaryPhase2Message::~WaveConfigureClusterSecondaryPhase2Message ()
{
}

void WaveConfigureClusterSecondaryPhase2Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

WaveConfigureClusterSecondaryPhase3Message::WaveConfigureClusterSecondaryPhase3Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_PHASE_3)
{
}

WaveConfigureClusterSecondaryPhase3Message::WaveConfigureClusterSecondaryPhase3Message (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode)
{
}

WaveConfigureClusterSecondaryPhase3Message::~WaveConfigureClusterSecondaryPhase3Message ()
{
}

void WaveConfigureClusterSecondaryPhase3Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

WaveConfigureClusterSecondaryHaPeerPhase3Message::WaveConfigureClusterSecondaryHaPeerPhase3Message ()
    : WaveConfigureClusterSecondaryPhase3Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_CONFIGURE_CLUSTER_SECONDARY_HA_PEER_PHASE_3)
{
}

WaveConfigureClusterSecondaryHaPeerPhase3Message::~WaveConfigureClusterSecondaryHaPeerPhase3Message ()
{
}

void WaveConfigureClusterSecondaryHaPeerPhase3Message::setupAttributesForSerialization ()
{
    WaveConfigureClusterSecondaryPhase3Message::setupAttributesForSerialization ();
}

WaveRejoinClusterSecondaryPhase1Message::WaveRejoinClusterSecondaryPhase1Message ()
    : WaveConfigureClusterSecondaryPhase1Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_1)
{
}

WaveRejoinClusterSecondaryPhase1Message::WaveRejoinClusterSecondaryPhase1Message (WaveServiceId serviceCode, UI32 operationCode)
    : WaveConfigureClusterSecondaryPhase1Message (serviceCode, operationCode)
{
}

WaveRejoinClusterSecondaryPhase1Message::~WaveRejoinClusterSecondaryPhase1Message ()
{
}

void WaveRejoinClusterSecondaryPhase1Message::setupAttributesForSerialization ()
{
    WaveConfigureClusterSecondaryPhase1Message::setupAttributesForSerialization ();
}

WaveRejoinClusterSecondaryHaPeerPhase1Message::WaveRejoinClusterSecondaryHaPeerPhase1Message ()
    : WaveRejoinClusterSecondaryPhase1Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER_PHASE_1)
{
}

WaveRejoinClusterSecondaryHaPeerPhase1Message::~WaveRejoinClusterSecondaryHaPeerPhase1Message ()
{
}

void WaveRejoinClusterSecondaryHaPeerPhase1Message::setupAttributesForSerialization ()
{
    WaveRejoinClusterSecondaryPhase1Message::setupAttributesForSerialization ();
}

/// Name
/// WaveRejoinClusterSecondaryPhase2Message
/// Description
/// Constructor
/// Input
/// none
/// Output
/// none
/// Return
/// none
WaveRejoinClusterSecondaryPhase2Message::WaveRejoinClusterSecondaryPhase2Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_2),
      m_isReplaceRejoin (false),
      m_replacedNodeLocationId (0)
{
}

/// Name
/// ~WaveRejoinClusterSecondaryPhase2Message
/// Description
/// Destructor
/// Input
/// none
/// Output
/// none
/// Return
/// none
WaveRejoinClusterSecondaryPhase2Message::~WaveRejoinClusterSecondaryPhase2Message ()
{
}
/// Name
/// setupAttributesForSerialization
/// Description
/// Calls the base class function to
/// adds serializable attribute  to add
/// to the attributeMap in the WaveMessage
/// Input
/// none
/// Output
/// none
/// Return
/// none

void WaveRejoinClusterSecondaryPhase2Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
     addSerializableAttribute (new AttributeBool (&m_isReplaceRejoin, "isReplaceRejoin"));
}

bool WaveRejoinClusterSecondaryPhase2Message::getIsReplaceRejoin ()
{
    return (m_isReplaceRejoin);
}

void WaveRejoinClusterSecondaryPhase2Message::setIsReplaceRejoin (const bool &isReplaceRejoin)
{
    m_isReplaceRejoin = isReplaceRejoin;
}

/// Name
/// WaveRejoinClusterSecondaryPhase3Message
/// Description
/// Constructor
/// Input
/// none
/// Output
/// none
/// Return
/// none
WaveRejoinClusterSecondaryPhase3Message::WaveRejoinClusterSecondaryPhase3Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_PHASE_3)
{
}

WaveRejoinClusterSecondaryPhase3Message::WaveRejoinClusterSecondaryPhase3Message (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode)
{
}

/// Name
/// ~WaveRejoinClusterSecondaryPhase3Message
/// Description
/// Destructor
/// Input
/// none
/// Output
/// none
/// Return
/// none
WaveRejoinClusterSecondaryPhase3Message::~WaveRejoinClusterSecondaryPhase3Message ()
{
}
/// Name
/// setupAttributesForSerialization
/// Description
/// Calls the base class function to
/// adds serializable attribute  to add
/// to the attributeMap in the WaveMessage
/// Input
/// none
/// Output
/// none
/// Return
/// none

void WaveRejoinClusterSecondaryPhase3Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

WaveRejoinClusterSecondaryHaPeerPhase3Message::WaveRejoinClusterSecondaryHaPeerPhase3Message ()
    : WaveRejoinClusterSecondaryPhase3Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER_PHASE_3)
{
}

WaveRejoinClusterSecondaryHaPeerPhase3Message::~WaveRejoinClusterSecondaryHaPeerPhase3Message ()
{
}

void WaveRejoinClusterSecondaryHaPeerPhase3Message::setupAttributesForSerialization ()
{
    WaveRejoinClusterSecondaryPhase3Message::setupAttributesForSerialization ();
}

FrameworkObjectManagerUpdateListOfSecondariesMessage::FrameworkObjectManagerUpdateListOfSecondariesMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_UPDATE_LIST_OF_CLUSTER_SECONDARIES),
      m_isDeletion(false),
      m_lastUsedLocationId (0)
{
}

FrameworkObjectManagerUpdateListOfSecondariesMessage::~FrameworkObjectManagerUpdateListOfSecondariesMessage ()
{
}

void FrameworkObjectManagerUpdateListOfSecondariesMessage::addSecondaryNodeDetails (const LocationId &locationId, const string &ipAddress, const UI32 &port, bool isNewNode)
{
    m_locationIdsForSecondaryNodes.push_back (locationId);
    m_IpAddressesForSecondaryNodes.push_back (ipAddress);
    m_portsForSecondaryNodes.push_back       (port);
    m_isNodeNewVector.push_back (isNewNode);
}

UI32 FrameworkObjectManagerUpdateListOfSecondariesMessage::getNumberOfSecondaryLocations () const
{
    UI32 numberOfSecondaryLocations1 = m_locationIdsForSecondaryNodes.size ();
    UI32 numberOfSecondaryLocations2 = m_IpAddressesForSecondaryNodes.size ();
    UI32 numberOfSecondaryLocations3 = m_portsForSecondaryNodes.size ();
    UI32 numberOfSecondaryLocations4 = m_isNodeNewVector.size();

    waveAssert (numberOfSecondaryLocations1 == numberOfSecondaryLocations2, __FILE__, __LINE__);
    waveAssert (numberOfSecondaryLocations2 == numberOfSecondaryLocations3, __FILE__, __LINE__);
    waveAssert (numberOfSecondaryLocations3 == numberOfSecondaryLocations4, __FILE__, __LINE__);
    return (numberOfSecondaryLocations1);
}

LocationId FrameworkObjectManagerUpdateListOfSecondariesMessage::getLocationIdAtIndex (const UI32 &index) const
{
    UI32 numberOfSecondaryLocations = getNumberOfSecondaryLocations ();

    waveAssert (index < numberOfSecondaryLocations, __FILE__, __LINE__);

    return (m_locationIdsForSecondaryNodes[index]);
}

string FrameworkObjectManagerUpdateListOfSecondariesMessage::getIpAddressAtIndex (const UI32 &index) const
{
    UI32 numberOfSecondaryLocations = getNumberOfSecondaryLocations ();

    waveAssert (index < numberOfSecondaryLocations, __FILE__, __LINE__);

    return (m_IpAddressesForSecondaryNodes[index]);
}

UI32 FrameworkObjectManagerUpdateListOfSecondariesMessage::getPortAtIndex (const UI32 &index) const
{
    UI32 numberOfSecondaryLocations = getNumberOfSecondaryLocations ();

    waveAssert (index < numberOfSecondaryLocations, __FILE__, __LINE__);

    return (m_portsForSecondaryNodes[index]);
}

bool FrameworkObjectManagerUpdateListOfSecondariesMessage::isNodeNewAtIndex(const UI32 &index) const
{
    UI32 numberOfSecondaryLocations = getNumberOfSecondaryLocations ();
    waveAssert(index < numberOfSecondaryLocations, __FILE__, __LINE__);
    return (m_isNodeNewVector[index]);
}

bool FrameworkObjectManagerUpdateListOfSecondariesMessage::isDeletion() const
{
    return m_isDeletion;
}

void  FrameworkObjectManagerUpdateListOfSecondariesMessage::setIsDeletion (bool deletion)
{
    m_isDeletion = deletion;
}

LocationId FrameworkObjectManagerUpdateListOfSecondariesMessage::getLastUsedLocationId () const
{
    return (m_lastUsedLocationId);
}

void FrameworkObjectManagerUpdateListOfSecondariesMessage::setLastUsedLocationId (const LocationId &locationId)
{
    m_lastUsedLocationId = locationId;
}

void FrameworkObjectManagerUpdateListOfSecondariesMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeLocationIdVector (&m_locationIdsForSecondaryNodes,  "locationIdsForSecondaryNodes"));
     addSerializableAttribute (new AttributeStringVector     (&m_IpAddressesForSecondaryNodes,  "IpAddressesForSecondaryNodes"));
     addSerializableAttribute (new AttributeUI32Vector       (&m_portsForSecondaryNodes,        "portsForSecondaryNodes"));
     addSerializableAttribute (new AttributeBoolVector       (&m_isNodeNewVector,               "isNodeNewVector"));
     addSerializableAttribute (new AttributeBool             (&m_isDeletion,                    "isDeletion"));
     addSerializableAttribute (new AttributeLocationId       (&m_lastUsedLocationId,            "lastUsedLocationId"));
     addSerializableAttribute (new AttributeLocationIdVector (&m_connectedLocationIds,          "connectedLocationIds"));
}

void FrameworkObjectManagerUpdateListOfSecondariesMessage::getConnectedLocationIds (vector<LocationId> &locationIds)
{
    locationIds = m_connectedLocationIds;
}

void FrameworkObjectManagerUpdateListOfSecondariesMessage::setConnectedLocationIds (vector<LocationId> &locationIds)
{
    m_connectedLocationIds = locationIds;
}

FrameworkObjectManagerAddNodesToClusterMessage::FrameworkObjectManagerAddNodesToClusterMessage ()
    : WaveCreateClusterWithNodesMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_ADD_NODES_TO_CLUSTER)
{
}

FrameworkObjectManagerAddNodesToClusterMessage::~FrameworkObjectManagerAddNodesToClusterMessage ()
{
}

FrameworkObjectManagerDeleteNodesFromClusterMessage::FrameworkObjectManagerDeleteNodesFromClusterMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveCreateClusterWithNodesMessage (serviceCode, operationCode),
      m_isDisconnected(false)
{
}

FrameworkObjectManagerDeleteNodesFromClusterMessage::FrameworkObjectManagerDeleteNodesFromClusterMessage ()
    : WaveCreateClusterWithNodesMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_DELETE_NODES_FROM_CLUSTER),
      m_isDisconnected(false)
{
}

FrameworkObjectManagerDeleteNodesFromClusterMessage::~FrameworkObjectManagerDeleteNodesFromClusterMessage ()
{
}

void FrameworkObjectManagerDeleteNodesFromClusterMessage::addNodeIpAddressAndPort (const string &nodeIpAddress, const SI32 &nodePort)
{
    addNewNodeIpAddressAndPort (nodeIpAddress, nodePort);
}

UI32 FrameworkObjectManagerDeleteNodesFromClusterMessage::getNumberOfNodes ()
{
    return (getNumberOfNewNodes ());
}

string FrameworkObjectManagerDeleteNodesFromClusterMessage::getNodeAt (UI32 i)
{
    return (WaveCreateClusterWithNodesMessage::getNodeAt (i));
}

SI32 FrameworkObjectManagerDeleteNodesFromClusterMessage::getNodePortAt (UI32 i)
{
    return (WaveCreateClusterWithNodesMessage::getNodePortAt (i));
}

void FrameworkObjectManagerDeleteNodesFromClusterMessage::setNodeStatus (const string &nodeIpAddress, const SI32 &nodePort, ResourceId status)
{
    setNewNodeStatus (nodeIpAddress, nodePort, status);
}

ResourceId FrameworkObjectManagerDeleteNodesFromClusterMessage::getNodeStatus (const string &nodeIpAddress, const SI32 &nodePort)
{
    return (getNewNodeStatus (nodeIpAddress, nodePort));
}

bool FrameworkObjectManagerDeleteNodesFromClusterMessage::isNodeStatusSet (const string &nodeIpAddress, const SI32 &nodePort)
{
    return (isNewNodeStatusSet (nodeIpAddress, nodePort));
}

void FrameworkObjectManagerDeleteNodesFromClusterMessage::setIsDisconnected(bool isDisconnected)
{
    m_isDisconnected = isDisconnected;
}

bool FrameworkObjectManagerDeleteNodesFromClusterMessage::getIsDisconnected ()
{
    return m_isDisconnected;
}

FrameworkObjectManagerDestroyClusterMessage::FrameworkObjectManagerDestroyClusterMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_DESTORY_CLUSTER),
      m_reasonForDestroyingCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED),
      m_originalRequester(0),
      m_isRebootRequired (true)
{
}

FrameworkObjectManagerDestroyClusterMessage::~FrameworkObjectManagerDestroyClusterMessage ()
{
}

FrameworkObjectManagerFailoverReason FrameworkObjectManagerDestroyClusterMessage::getReasonForDestroyingCluster () const
{
    return (m_reasonForDestroyingCluster);
}

WaveServiceId FrameworkObjectManagerDestroyClusterMessage::getOriginalRequester () const
{
    return (m_originalRequester);
}

void FrameworkObjectManagerDestroyClusterMessage::setOriginalRequester (const WaveServiceId &originalRequester)
{
    m_originalRequester = originalRequester;
}

void FrameworkObjectManagerDestroyClusterMessage::setReasonForDestroyingCluster (const FrameworkObjectManagerFailoverReason &reasonForDestroyingCluster)
{
    m_reasonForDestroyingCluster = reasonForDestroyingCluster;
}

void FrameworkObjectManagerDestroyClusterMessage::setIsRebootRequired (const bool &isRebootRequired)
{
    m_isRebootRequired = isRebootRequired;
}

bool FrameworkObjectManagerDestroyClusterMessage::getIsRebootRequired () const
{
    return (m_isRebootRequired);
}

FrameworkObjectManagerUnconfigureClusterSecondaryMessage::FrameworkObjectManagerUnconfigureClusterSecondaryMessage (const string &clusterSecondaryIpAddress, const SI32 &clusterSecondaryPort)
    : WaveMessage                (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_UNCONFIGURE_CLUSTER_SECONDARY),
      m_clusterSecondaryIpAddress (clusterSecondaryIpAddress),
      m_clusterSecondaryPort      (clusterSecondaryPort),
      m_isPerformWarmRecovery     (false)
{
}

FrameworkObjectManagerUnconfigureClusterSecondaryMessage::FrameworkObjectManagerUnconfigureClusterSecondaryMessage ()
    : WaveMessage                  (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_UNCONFIGURE_CLUSTER_SECONDARY),
      m_clusterSecondaryIpAddress (""),
      m_clusterSecondaryPort (0),
      m_isPerformWarmRecovery (false)
{
}

FrameworkObjectManagerUnconfigureClusterSecondaryMessage::~FrameworkObjectManagerUnconfigureClusterSecondaryMessage ()
{
}

string FrameworkObjectManagerUnconfigureClusterSecondaryMessage::getClusterSecondaryIpAddress ()
{
    return (m_clusterSecondaryIpAddress);
}

SI32 FrameworkObjectManagerUnconfigureClusterSecondaryMessage::getClusterSecondaryPort ()
{
    return (m_clusterSecondaryPort);
}

void FrameworkObjectManagerUnconfigureClusterSecondaryMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_clusterSecondaryIpAddress,   "clusterSecondaryIpAddress"));
     addSerializableAttribute (new AttributeSI32 (&m_clusterSecondaryPort,          "clusterSecondaryPort"));
     addSerializableAttribute (new AttributeBool (&m_isPerformWarmRecovery,         "isPerformWarmRecovery"));
}

bool FrameworkObjectManagerUnconfigureClusterSecondaryMessage::getIsPerformWarmRecovery ()
{
    return (m_isPerformWarmRecovery);
}

void FrameworkObjectManagerUnconfigureClusterSecondaryMessage::setIsPerformWarmRecovery (const bool &isPerformWarmRecovery)
{
    m_isPerformWarmRecovery = isPerformWarmRecovery;
}

FrameworkObjectManagerRejoinNodesToClusterMessage::FrameworkObjectManagerRejoinNodesToClusterMessage ()
    : FrameworkObjectManagerDeleteNodesFromClusterMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_NODES_TO_CLUSTER),
    m_isReplaceRejoin (false)
{
}

FrameworkObjectManagerRejoinNodesToClusterMessage::~FrameworkObjectManagerRejoinNodesToClusterMessage ()
{
}

bool FrameworkObjectManagerRejoinNodesToClusterMessage::getIsReplaceRejoin ()
{
    return (m_isReplaceRejoin);
}

void FrameworkObjectManagerRejoinNodesToClusterMessage::setIsReplaceRejoin (const bool &isReplaceRejoin)
{
    m_isReplaceRejoin = isReplaceRejoin;
}

void FrameworkObjectManagerRejoinNodesToClusterMessage::setupAttributesForSerialization ()
{
    FrameworkObjectManagerDeleteNodesFromClusterMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_isReplaceRejoin,           "isReplaceRejoin"));
     addSerializableAttribute (new AttributeLocationIdVector (&m_locationIds,   "locationIds"));
}

void FrameworkObjectManagerRejoinNodesToClusterMessage::setNodeLocationId (const LocationId & locationId)
{
    m_locationIds.push_back(locationId);
    return;
}

LocationId FrameworkObjectManagerRejoinNodesToClusterMessage::getNodeLocationId (const UI32 index) const
{
    return (m_locationIds[index]);
}

FrameworkObjectManagerRejoinClusterSecondaryMessage::FrameworkObjectManagerRejoinClusterSecondaryMessage ()
    : WaveConfigureClusterSecondaryMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY),
      m_isReplaceRejoin (false)
{
}

FrameworkObjectManagerRejoinClusterSecondaryMessage::FrameworkObjectManagerRejoinClusterSecondaryMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveConfigureClusterSecondaryMessage (serviceCode, operationCode),
      m_isReplaceRejoin (false)
{
}

FrameworkObjectManagerRejoinClusterSecondaryMessage::FrameworkObjectManagerRejoinClusterSecondaryMessage (const string &clusterPrimaryWaveVersion, const string &clusterPrimaryIpAddress, const SI32 &clusterPrimaryPort, const LocationId &clusterPrimaryLocationId, const string &ipAddress, const SI32 &port, const LocationId &locationId)
    : WaveConfigureClusterSecondaryMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY, clusterPrimaryWaveVersion, clusterPrimaryIpAddress, clusterPrimaryPort, clusterPrimaryLocationId, ipAddress, port, locationId),
    m_isReplaceRejoin (false)
{
}

FrameworkObjectManagerRejoinClusterSecondaryMessage::~FrameworkObjectManagerRejoinClusterSecondaryMessage ()
{
}

bool FrameworkObjectManagerRejoinClusterSecondaryMessage::getIsReplaceRejoin ()
{
    return (m_isReplaceRejoin);
}

void FrameworkObjectManagerRejoinClusterSecondaryMessage::setIsReplaceRejoin (const bool &isReplaceRejoin)
{
    m_isReplaceRejoin = isReplaceRejoin;
}

void FrameworkObjectManagerRejoinClusterSecondaryMessage::setupAttributesForSerialization ()
{
    WaveConfigureClusterSecondaryMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool         (&m_isReplaceRejoin,       "isReplaceRejoin"));
     addSerializableAttribute (new AttributeUI64Vector   (&m_configurationNumber,   "configurationNumber"));
}

void FrameworkObjectManagerRejoinClusterSecondaryMessage::setConfigurationNumber (const vector<UI64> configurationNumber)
{
    m_configurationNumber = configurationNumber;
}

vector<UI64> FrameworkObjectManagerRejoinClusterSecondaryMessage::getConfigurationNumber ()
{
    return (m_configurationNumber);
}

FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage::FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage ()
    : FrameworkObjectManagerRejoinClusterSecondaryMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REJOIN_CLUSTER_SECONDARY_HA_PEER)
{
}

FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage::~FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage ()
{
}

void FrameworkObjectManagerRejoinClusterSecondaryHaPeerMessage::setupAttributesForSerialization ()
{
    FrameworkObjectManagerRejoinClusterSecondaryMessage::setupAttributesForSerialization ();
}

FrameworkObjectManagerDetachFromClusterMessage::FrameworkObjectManagerDetachFromClusterMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_DETACH_FROM_CLUSTER),
      m_reasonForDetachingFromCluster (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED)
{
}

FrameworkObjectManagerDetachFromClusterMessage::~FrameworkObjectManagerDetachFromClusterMessage ()
{
}

FrameworkObjectManagerFailoverReason FrameworkObjectManagerDetachFromClusterMessage::getReasonForDetachingFromCluster () const
{
    return (m_reasonForDetachingFromCluster);
}

void FrameworkObjectManagerDetachFromClusterMessage::setReasonForDetachingFromCluster (const FrameworkObjectManagerFailoverReason &reasonForDetachingFromCluster)
{
    m_reasonForDetachingFromCluster = reasonForDetachingFromCluster;
}

FrameworkObjectManagerLostHeartBeatMessage::FrameworkObjectManagerLostHeartBeatMessage ()
    : FrameworkObjectManagerDeleteNodesFromClusterMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_LOST_HEART_BEAT_MESSAGE)
{
}

FrameworkObjectManagerLostHeartBeatMessage::~FrameworkObjectManagerLostHeartBeatMessage ()
{
}

FrameworkObjectManagerPrimaryChangedMessage::FrameworkObjectManagerPrimaryChangedMessage ()
    : WaveMessage           (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE),
      m_newPrimaryLocationId (0),
      m_newPrimaryIpAddress  (""),
      m_newPrimaryPort       (0),
      m_isPrimaryChangeDueToControlledFailover(false),
      m_anyConfiguraitonChangeTrackingNumber (0)
{
}

FrameworkObjectManagerPrimaryChangedMessage::FrameworkObjectManagerPrimaryChangedMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage           (serviceCode, operationCode),
      m_newPrimaryLocationId (0),
      m_newPrimaryIpAddress  (""),
      m_newPrimaryPort       (0),
      m_isPrimaryChangeDueToControlledFailover(false),
      m_anyConfiguraitonChangeTrackingNumber (0)
{
}
    
FrameworkObjectManagerPrimaryChangedMessage::FrameworkObjectManagerPrimaryChangedMessage (const LocationId &newPrimaryLocationId, const string &newPrimaryIpAddress, const UI32 &newPrimaryPort)
    : WaveMessage                            (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE),
      m_newPrimaryLocationId                  (newPrimaryLocationId),
      m_newPrimaryIpAddress                   (newPrimaryIpAddress),
      m_newPrimaryPort                        (newPrimaryPort),
      m_isPrimaryChangeDueToControlledFailover(false),
      m_anyConfiguraitonChangeTrackingNumber  (0)
{
}

FrameworkObjectManagerPrimaryChangedMessage::~FrameworkObjectManagerPrimaryChangedMessage ()
{
}

void FrameworkObjectManagerPrimaryChangedMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeLocationId (&m_newPrimaryLocationId,                    "newPrimaryLocationId"));
     addSerializableAttribute (new AttributeString     (&m_newPrimaryIpAddress,                     "newPrimaryIpAddress"));
     addSerializableAttribute (new AttributeUI32       (&m_newPrimaryPort,                          "newPrimaryPort"));
     addSerializableAttribute (new AttributeBool       (&m_isPrimaryChangeDueToControlledFailover,  "isPrimaryChangeDueToControlledFailover"));

     addSerializableAttribute (new AttributeStringVector (&m_managedObjectNamesForSchemaChange,     "managedObjectNamesForSchemaChange"));
     addSerializableAttribute (new AttributeStringVector (&m_fieldNamesStringsForSchemaChange,      "fieldNamesStringsForSchemaChange"));
     addSerializableAttribute (new AttributeStringVector (&m_fieldNamesTypesForSchemaChange,        "fieldNamesTypesForSchemaChange"));
     addSerializableAttribute (new AttributeUI32Vector   (&m_classIds,                              "classIds"));
     addSerializableAttribute (new AttributeUI32Vector   (&m_parentTableIds,                        "parentTableIds"));
    addSerializableAttribute (new AttributeUI64         (&m_anyConfiguraitonChangeTrackingNumber,   "anyConfiguraitonChangeTrackingNumber"));
}

LocationId FrameworkObjectManagerPrimaryChangedMessage::getNewPrimaryLocationId () const
{
    return (m_newPrimaryLocationId);
}

string FrameworkObjectManagerPrimaryChangedMessage::getNewPrimaryIpAddress () const
{
    return (m_newPrimaryIpAddress);
}

UI32 FrameworkObjectManagerPrimaryChangedMessage::getNewPrimaryPort () const
{
    return (m_newPrimaryPort);
}

void   FrameworkObjectManagerPrimaryChangedMessage::setPrimaryChangeDueToControlledFailover     ()
{
     m_isPrimaryChangeDueToControlledFailover = true;
}

bool FrameworkObjectManagerPrimaryChangedMessage::isPrimaryChangeDueToControlledFailover () const
{
    return m_isPrimaryChangeDueToControlledFailover;

}

void  FrameworkObjectManagerPrimaryChangedMessage::getSchemaChangeVectors (vector<string>   & managedObjectNamesForSchemaChange,vector<string>   & fieldNamesStringsForSchemaChange,vector<string> & fieldNamesTypesForSchemaChange,vector<UI32>   & classIds,vector<UI32> & parentTableIds)
{
     managedObjectNamesForSchemaChange = m_managedObjectNamesForSchemaChange;
     fieldNamesStringsForSchemaChange = m_fieldNamesStringsForSchemaChange;
     fieldNamesTypesForSchemaChange = m_fieldNamesTypesForSchemaChange;
     classIds = m_classIds;
     parentTableIds = m_parentTableIds;
}

void  FrameworkObjectManagerPrimaryChangedMessage::setSchemaChangeVectors ()
{
     vector<string>  managedObjectNamesForSchemaChange;
     vector<string>  fieldNamesStringsForSchemaChange;
     vector<string>  fieldNamesTypesForSchemaChange;
     vector<UI32>    classIds;
     vector<UI32>    parentTableIds;

     (OrmRepository::getInstance())->getSchemaChangeVectors (managedObjectNamesForSchemaChange,fieldNamesStringsForSchemaChange,fieldNamesTypesForSchemaChange, classIds, parentTableIds);

     m_managedObjectNamesForSchemaChange = managedObjectNamesForSchemaChange;
     m_fieldNamesStringsForSchemaChange = fieldNamesStringsForSchemaChange;
     m_fieldNamesTypesForSchemaChange = fieldNamesTypesForSchemaChange;
     m_classIds = classIds;
     m_parentTableIds = parentTableIds;
}

void  FrameworkObjectManagerPrimaryChangedMessage::setAnyConfigurationChangeTrackingNumber (const UI64 &trackingNumber)
{
    m_anyConfiguraitonChangeTrackingNumber = trackingNumber;
}

UI64  FrameworkObjectManagerPrimaryChangedMessage::getAnyConfigurationChangeTrackingNumber () const
{
    return (m_anyConfiguraitonChangeTrackingNumber);
}

FrameworkObjectManagerPrimaryChangedHaPeerMessage::FrameworkObjectManagerPrimaryChangedHaPeerMessage ()
    : FrameworkObjectManagerPrimaryChangedMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_MESSAGE_HA_PEER),
      m_isDBEmptyRequired (true)
{
}

FrameworkObjectManagerPrimaryChangedHaPeerMessage::~FrameworkObjectManagerPrimaryChangedHaPeerMessage ()
{
}

void FrameworkObjectManagerPrimaryChangedHaPeerMessage::setupAttributesForSerialization ()
{
    FrameworkObjectManagerPrimaryChangedMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_isDBEmptyRequired,  "isDBEmptyRequired"));
}

void FrameworkObjectManagerPrimaryChangedHaPeerMessage::setDBEmptyRequired (const bool &isDBEmptyRequired)
{
    m_isDBEmptyRequired = isDBEmptyRequired;
}

bool FrameworkObjectManagerPrimaryChangedHaPeerMessage::getIsDBEmptyRequired () const
{
    return (m_isDBEmptyRequired);
}

FrameworkObjectManagerPrimaryChangedPhase1Message::FrameworkObjectManagerPrimaryChangedPhase1Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_1_MESSAGE),
      m_anyConfiguraitonChangeTrackingNumber (0)
{
}

FrameworkObjectManagerPrimaryChangedPhase1Message::FrameworkObjectManagerPrimaryChangedPhase1Message (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode),
      m_anyConfiguraitonChangeTrackingNumber (0)
{
}

FrameworkObjectManagerPrimaryChangedPhase1Message::~FrameworkObjectManagerPrimaryChangedPhase1Message ()
{
}

UI32 FrameworkObjectManagerPrimaryChangedPhase1Message::getDatabaseBackupBufferTag ()
{
    return (0);
}

void FrameworkObjectManagerPrimaryChangedPhase1Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeUI64         (&m_anyConfiguraitonChangeTrackingNumber,   "anyConfiguraitonChangeTrackingNumber"));
}

void FrameworkObjectManagerPrimaryChangedPhase1Message::setAnyConfigurationChangeTrackingNumber (const UI64 &trackingNumber)
{
    m_anyConfiguraitonChangeTrackingNumber = trackingNumber;
}

UI64 FrameworkObjectManagerPrimaryChangedPhase1Message::getAnyConfigurationChangeTrackingNumber () const
{
    return (m_anyConfiguraitonChangeTrackingNumber);
}

FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message::FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message ()
    : FrameworkObjectManagerPrimaryChangedPhase1Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_1_HA_PEER_MESSAGE),
      m_isDBRestoreRequired (true)
{
}

FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message::~FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message ()
{
}

void FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message::setupAttributesForSerialization ()
{
    FrameworkObjectManagerPrimaryChangedPhase1Message::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_isDBRestoreRequired, "isDBRestoreRequired"));
}

void FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message::setDBRestoreRequired (const bool &isDBRestoreRequired)
{
    m_isDBRestoreRequired = isDBRestoreRequired;
}

bool FrameworkObjectManagerPrimaryChangedHaPeerPhase1Message::getIsDBRestoreRequired () const
{
    return (m_isDBRestoreRequired);
}

FrameworkObjectManagerPrimaryChangedPhase2Message::FrameworkObjectManagerPrimaryChangedPhase2Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_2_MESSAGE)
{
}

FrameworkObjectManagerPrimaryChangedPhase2Message::~FrameworkObjectManagerPrimaryChangedPhase2Message ()
{
}

FrameworkObjectManagerPrimaryChangedPhase3Message::FrameworkObjectManagerPrimaryChangedPhase3Message ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_3_MESSAGE)
{
}

FrameworkObjectManagerPrimaryChangedPhase3Message::FrameworkObjectManagerPrimaryChangedPhase3Message (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode)
{
}

FrameworkObjectManagerPrimaryChangedPhase3Message::~FrameworkObjectManagerPrimaryChangedPhase3Message ()
{
}

void FrameworkObjectManagerPrimaryChangedPhase3Message::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message::FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message ()
    : FrameworkObjectManagerPrimaryChangedPhase3Message (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_PHASE_3_HA_PEER_MESSAGE)
{
}

FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message::~FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message ()
{
}

void FrameworkObjectManagerPrimaryChangedHaPeerPhase3Message::setupAttributesForSerialization ()
{
    FrameworkObjectManagerPrimaryChangedPhase3Message::setupAttributesForSerialization ();
}

FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage::FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_ROLLBACK_STANDBY_ON_ACTIVE_ROLLBACK)
{
}

FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage::~FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage ()
{
}

void FrameworkObjectManagerRollbackStandbyOnActiveRollbackMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

FrameworkObjectManagerServiceControlListMessage::FrameworkObjectManagerServiceControlListMessage ()
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName (), FRAMEWORK_OBJECT_MANAGER_SERVICE_CONTROL_LIST_MESSAGE)
{
}

FrameworkObjectManagerServiceControlListMessage::~FrameworkObjectManagerServiceControlListMessage ()
{
}

void FrameworkObjectManagerServiceControlListMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeWaveServiceIdVector (&m_waveServiceIds,   "waveServiceIds"));
     addSerializableAttribute (new AttributeStringVector         (&m_serviceNames,      "serviceNames"));
     addSerializableAttribute (new AttributeBoolVector           (&m_enabled,           "enabled"));
     addSerializableAttribute (new AttributeBoolVector           (&m_local,             "local"));
     addSerializableAttribute (new AttributeStringVector         (&m_cpuAffinity,       "cpuAffinity"));
}

UI32 FrameworkObjectManagerServiceControlListMessage::getNumberOfServices () const
{
    return (m_waveServiceIds.size ());
}

void FrameworkObjectManagerServiceControlListMessage::addAService (const WaveServiceId &waveServiceId, const string &serviceName, const bool &isEnabled, const bool &isLocal, const string &cpuAffinity)
{
    m_waveServiceIds.push_back (waveServiceId);
    m_serviceNames.push_back    (serviceName);
    m_enabled.push_back         (isEnabled);
    m_local.push_back           (isLocal);
    m_cpuAffinity.push_back     (cpuAffinity);
}

void FrameworkObjectManagerServiceControlListMessage::getServiceAtIndex (const UI32 &index, WaveServiceId &waveServiceId, string &serviceName, bool &isEnabled, bool &isLocal, string &cpuAffinity)
{
    UI32 numberOfServices = getNumberOfServices ();

    waveAssert (index < numberOfServices, __FILE__, __LINE__);

    waveServiceId = m_waveServiceIds[index];
    serviceName    = m_serviceNames[index];
    isEnabled      = m_enabled[index];
    isLocal        = m_local[index];
    cpuAffinity    = m_cpuAffinity[index];
}

FrameworkObjectManagerServiceSetCpuAffinityMessage::FrameworkObjectManagerServiceSetCpuAffinityMessage ()
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName (), FRAMEWORK_OBJECT_MANAGER_SERVICE_SET_CPU_AFFINITY_MESSAGE),
      m_waveServiceId(0)
{
}

FrameworkObjectManagerServiceSetCpuAffinityMessage::FrameworkObjectManagerServiceSetCpuAffinityMessage (const WaveServiceId &waveServiceId, const vector<UI32> &cpuAffinityVector)
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName (), FRAMEWORK_OBJECT_MANAGER_SERVICE_SET_CPU_AFFINITY_MESSAGE),
      m_waveServiceId           (waveServiceId),
      m_cpuAffinityVector        (cpuAffinityVector)
{
}

FrameworkObjectManagerServiceSetCpuAffinityMessage::~FrameworkObjectManagerServiceSetCpuAffinityMessage ()
{
}

void FrameworkObjectManagerServiceSetCpuAffinityMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeWaveServiceId (&m_waveServiceId,      "waveServiceId"));
     addSerializableAttribute (new AttributeUI32Vector     (&m_cpuAffinityVector,   "cpuAffinityVector"));
}

WaveServiceId FrameworkObjectManagerServiceSetCpuAffinityMessage::getWaveServiceId ()
{
    return (m_waveServiceId);
}

vector<UI32> FrameworkObjectManagerServiceSetCpuAffinityMessage::getCpuAffinityVector () const
{
    return (m_cpuAffinityVector);
}

FrameworkObjectManagerStartExternalStateSynchronizationMessage::FrameworkObjectManagerStartExternalStateSynchronizationMessage (const UI32 fssStageNumber, const ResourceId serviceType)
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName (), FRAMEWORK_OBJECT_MANAGER_START_EXTERNAL_STATE_SYNCHRONIZATION),
    m_fssStageNumber    (fssStageNumber),
    m_serviceType       (serviceType)
{

}

void FrameworkObjectManagerStartExternalStateSynchronizationMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32     (&m_fssStageNumber,    "fssStageNumber"));
     addSerializableAttribute (new AttributeResourceId (&m_serviceType,     "serviceType"));
}

UI32 FrameworkObjectManagerStartExternalStateSynchronizationMessage::getFssStageNumber () const
{
    return (m_fssStageNumber);
}

ResourceId FrameworkObjectManagerStartExternalStateSynchronizationMessage::getServiceType () const
{
    return (m_serviceType);
}



FrameworkObjectManagerStartSlotFailoverMessage::FrameworkObjectManagerStartSlotFailoverMessage (const UI32 slotNumber)
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName (), FRAMEWORK_OBJECT_MANAGER_START_SLOT_FAILOVER),
    m_slotNumber (slotNumber)
{

}

void FrameworkObjectManagerStartSlotFailoverMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32     (&m_slotNumber, "slotNumber"));
}

UI32 FrameworkObjectManagerStartSlotFailoverMessage::getSlotNumber () const
{
    return (m_slotNumber);
}


FrameworkObjectManagerNewPrincipalEstablishedMessage::FrameworkObjectManagerNewPrincipalEstablishedMessage(const string & failedPrincipalIpAddress,UI32 failedPrincipalPort,LocationId failedPrincipalLocationId)
      :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(),FRAMEWORK_OBJECT_MANAGER_NEW_PRINCIPAL_ESTABLISHED_AFTER_FAILOVER),
       mFailedPrincipalIpAddress(failedPrincipalIpAddress),
       mFailedPrincipalPort(failedPrincipalPort),
       mFailedPrincipalLocationId(failedPrincipalLocationId),
       mTriggerControlledFailover (false)
{
}


FrameworkObjectManagerNewPrincipalEstablishedMessage::~FrameworkObjectManagerNewPrincipalEstablishedMessage()
{
}

void FrameworkObjectManagerNewPrincipalEstablishedMessage::setFailedPrincipalIpAddress(const string & failedPrincipalIpAddress)
{
    mFailedPrincipalIpAddress = failedPrincipalIpAddress;
}

void FrameworkObjectManagerNewPrincipalEstablishedMessage::setFailedPrinciapalPort(UI32 failedPrincipalPort)
{
    mFailedPrincipalPort = failedPrincipalPort;
}

void FrameworkObjectManagerNewPrincipalEstablishedMessage::setFailedPrincipalLocationId(LocationId locationId)
{
    mFailedPrincipalLocationId = locationId;
}

void FrameworkObjectManagerNewPrincipalEstablishedMessage::setTriggerControlledFaileover ()
{
    mTriggerControlledFailover = true;
}

string const & FrameworkObjectManagerNewPrincipalEstablishedMessage::getFailedPrincipalIpAddress() const
{
    return mFailedPrincipalIpAddress;
}
UI32  FrameworkObjectManagerNewPrincipalEstablishedMessage::getFailedPrincipalPort()  const
{
    return mFailedPrincipalPort;
}
LocationId     FrameworkObjectManagerNewPrincipalEstablishedMessage::getFailedPrincipalLocationId() const
{
    return mFailedPrincipalLocationId;
}

bool FrameworkObjectManagerNewPrincipalEstablishedMessage::getTriggerControlledFailover () const
{
    return mTriggerControlledFailover;
}

FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::FrameworkObjectManagerSecondaryNodeFailureNotificationMessage()
      :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(),FRAMEWORK_OBJECT_MANAGER_SECONDARY_NODE_FAILURE_NOTIFICATION),
       m_isControlledFailoverInSpecialCase (false)
      
{
}

FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::FrameworkObjectManagerSecondaryNodeFailureNotificationMessage(const string & failedIpAddress,UI32 failedPort,LocationId failedLocationId)
      :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(),FRAMEWORK_OBJECT_MANAGER_SECONDARY_NODE_FAILURE_NOTIFICATION),
       m_isControlledFailoverInSpecialCase (false)
      
{
    mFailedIpAddresses.push_back(failedIpAddress);
    mFailedPorts.push_back(failedPort);
    mFailedLocationIds.push_back(failedLocationId);
}


FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::~FrameworkObjectManagerSecondaryNodeFailureNotificationMessage()
{
}

void FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::addFailedIpAddress(const string & failedIpAddress)
{
    mFailedIpAddresses.push_back(failedIpAddress);
}

void FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::addFailedPort(UI32 failedPort)
{
    mFailedPorts.push_back(failedPort);
}

void FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::addFailedLocationId(LocationId locationId)
{
    mFailedLocationIds.push_back(locationId);
}

vector<string> const & FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::getFailedIpAddresses() const
{
    return mFailedIpAddresses;
}
vector<UI32> const &  FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::getFailedPorts()  const
{
    return mFailedPorts;
}
vector<LocationId> const &     FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::getFailedLocationIds() const
{
    return mFailedLocationIds;
}

void FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::setIsControlledFailoverInSpecialCase (bool const &isControlledFailoverInSpecialCase)
{
    m_isControlledFailoverInSpecialCase = isControlledFailoverInSpecialCase;
}

bool FrameworkObjectManagerSecondaryNodeFailureNotificationMessage::getIsControlledFailoverInSpecialCase () const
{
    return (m_isControlledFailoverInSpecialCase);
}

FrameworkObjectManagerDisconnectFromAllNodesMessage::FrameworkObjectManagerDisconnectFromAllNodesMessage()
      :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(),FRAMEWORK_OBJECT_MANAGER_DISCONNECT_FROM_ALL_NODES)
{
}


FrameworkObjectManagerDisconnectFromAllNodesMessage::~FrameworkObjectManagerDisconnectFromAllNodesMessage()
{
}

FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage::FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage ()
      :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(),FRAMEWORK_OBJECT_MANAGER_ESTABLISH_PRINCIPAL_AFTER_CLUSTER_REBOOT)

{

}

FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage::~FrameworkObjectManagerEstablishPrincipalAfterClusterRebootMessage ()
{

}

FrameworkObjectManagerResetNodeToUnconfirmRole::FrameworkObjectManagerResetNodeToUnconfirmRole ()
    :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_RESET_NODE_FOR_CLUSTER_MERGE)
{

}

FrameworkObjectManagerResetNodeToUnconfirmRole::~FrameworkObjectManagerResetNodeToUnconfirmRole ()
{

}

FrameworkObjectManagerRemoveKnownLocationsMessage::FrameworkObjectManagerRemoveKnownLocationsMessage ()
      :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_REMOVE_KNOWN_LOCATIONS_MESSAGE)
{
}


FrameworkObjectManagerRemoveKnownLocationsMessage::~FrameworkObjectManagerRemoveKnownLocationsMessage ()
{
}

void FrameworkObjectManagerRemoveKnownLocationsMessage::setFailedLocations (const vector<LocationId> locations)
{
    m_failedLocationIds = locations;
}

vector<LocationId> FrameworkObjectManagerRemoveKnownLocationsMessage::getFailedLocationIds () const
{
    return (m_failedLocationIds);
}

void FrameworkObjectManagerRemoveKnownLocationsMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32Vector (&m_failedLocationIds, "failedLocationIds"));
}

FrameworkObjectManagerStartHaSyncMessage::FrameworkObjectManagerStartHaSyncMessage (const string &peerHaIpAddress, const SI32 &peerHaIpPort)
      :WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_START_HA_SYNC_MESSAGE),
       m_peerHaIpAddress(peerHaIpAddress),
       m_peerHaIpPort(peerHaIpPort),
       m_firmwareVersion (""),
       m_haVersion (0),
       m_returnData ("")
{
}

FrameworkObjectManagerStartHaSyncMessage::~FrameworkObjectManagerStartHaSyncMessage()
{
}

void FrameworkObjectManagerStartHaSyncMessage::setPeerHaIpAddress(const string &peerHaIpAddress)
{
    m_peerHaIpAddress = peerHaIpAddress;
}

void FrameworkObjectManagerStartHaSyncMessage::setPeerHaIpPort(const SI32 &peerHaIpPort)
{
    m_peerHaIpPort = peerHaIpPort;
}

string FrameworkObjectManagerStartHaSyncMessage::getPeerHaIpAddress() const
{
    return m_peerHaIpAddress;
}

SI32 FrameworkObjectManagerStartHaSyncMessage::getPeerHaIpPort() const
{
    return m_peerHaIpPort;
}

void FrameworkObjectManagerStartHaSyncMessage::setFirmwareVersion(const string &firmwareVersion)
{
    m_firmwareVersion = firmwareVersion;
}

string FrameworkObjectManagerStartHaSyncMessage::getFirmwareVersion() const
{
    return m_firmwareVersion;
}

void FrameworkObjectManagerStartHaSyncMessage::setHAVersion(const UI32 &haVersion)
{
    m_haVersion = haVersion;
}

UI32 FrameworkObjectManagerStartHaSyncMessage::getHAVersion() const
{
    return m_haVersion;
}

void FrameworkObjectManagerStartHaSyncMessage::setReturnData (const string &returnData)
{
    m_returnData = returnData;
}

string FrameworkObjectManagerStartHaSyncMessage::getReturnData () const
{
    return m_returnData ;
}

void FrameworkObjectManagerStartHaSyncMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_peerHaIpAddress, "peerHaIpAddress"));
     addSerializableAttribute (new AttributeSI32 (&m_peerHaIpPort,      "peerHaIpPort"));
     addSerializableAttribute (new AttributeString (&m_firmwareVersion, "firmwareVersion"));
     addSerializableAttribute (new AttributeUI32 (&m_haVersion,         "haVersion"));
     addSerializableAttribute (new AttributeString (&m_returnData,      "returnData"));
}

FrameworkObjectManagerEndHaSyncMessage::FrameworkObjectManagerEndHaSyncMessage ()
      :WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_END_HA_SYNC_MESSAGE)
{
}

FrameworkObjectManagerEndHaSyncMessage::~FrameworkObjectManagerEndHaSyncMessage()
{
}

FrameworkObjectManagerInitHaIpAddressMessage::FrameworkObjectManagerInitHaIpAddressMessage (const string &localHaIpAddress, const SI32 &localHaIpPort)
      :WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_INIT_HA_IPADDR_MESSAGE),
       m_localHaIpAddress(localHaIpAddress),
       m_localHaIpPort(localHaIpPort)
{
}

FrameworkObjectManagerInitHaIpAddressMessage::~FrameworkObjectManagerInitHaIpAddressMessage()
{
}

void FrameworkObjectManagerInitHaIpAddressMessage::setLocalHaIpAddress(const string &localHaIpAddress)
{
    m_localHaIpAddress = localHaIpAddress;
}

void FrameworkObjectManagerInitHaIpAddressMessage::setLocalHaIpPort(const SI32 &localHaIpPort)
{
    m_localHaIpPort = localHaIpPort;
}

string FrameworkObjectManagerInitHaIpAddressMessage::getLocalHaIpAddress() const
{
    return m_localHaIpAddress;
}

SI32 FrameworkObjectManagerInitHaIpAddressMessage::getLocalHaIpPort() const
{
    return m_localHaIpPort;
}

void FrameworkObjectManagerInitHaIpAddressMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_localHaIpAddress,    "localHaIpAddress"));
     addSerializableAttribute (new AttributeSI32 (&m_localHaIpPort,         "localHaIpPort"));
}

WaveHaSyncConfigureStandbyMessage::WaveHaSyncConfigureStandbyMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_HA_SYNC_CONFIGURE_STANDBY),
    m_activeWaveVersion (""),
    m_activeLocationRole (LOCATION_STAND_ALONE)
{
}

WaveHaSyncConfigureStandbyMessage::WaveHaSyncConfigureStandbyMessage (const string &activeWaveVersion, const LocationRole &activeLocationRole)
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_HA_SYNC_CONFIGURE_STANDBY),
      m_activeWaveVersion (activeWaveVersion),
      m_activeLocationRole (activeLocationRole)
{
}

WaveHaSyncConfigureStandbyMessage::~WaveHaSyncConfigureStandbyMessage ()
{
}

void WaveHaSyncConfigureStandbyMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
    addSerializableAttribute (new AttributeString (&m_activeWaveVersion,   "activeWaveVersion"));
    addSerializableAttribute (new AttributeUI32   (&m_activeLocationRole,   "activeLocationRole"));
}

void WaveHaSyncConfigureStandbyMessage::setupAttributesForSerializationInAttributeOrderFormat ()
{
    WaveMessage::setupAttributesForSerializationInAttributeOrderFormat ();

    addAttributeNameForOrderToNameMapping ("activeWaveVersion");
    addAttributeNameForOrderToNameMapping ("activeLocationRole");
}

string WaveHaSyncConfigureStandbyMessage::getActiveWaveVersion ()
{
    return (m_activeWaveVersion);
}

LocationRole WaveHaSyncConfigureStandbyMessage::getActiveLocationRole ()
{
    return ((LocationRole)(m_activeLocationRole));
}

UI32 WaveHaSyncConfigureStandbyMessage::getDatabaseBackupBufferTag ()
{
    return (UINT_MAX);
}

void WaveHaSyncConfigureStandbyMessage::setValidationDetails (const UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToMessage)
{
    addBuffer (VALIDATION_DETAILS_BUFFER_TAG, bufferSize, pBuffer, transferBufferOwnershipToMessage);
}

void WaveHaSyncConfigureStandbyMessage::getValidationDetails (UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToUser)
{
    if (true == transferBufferOwnershipToUser)
    {
        pBuffer = transferBufferToUser (VALIDATION_DETAILS_BUFFER_TAG, bufferSize);
    }
    else
    {
        pBuffer = findBuffer (VALIDATION_DETAILS_BUFFER_TAG, bufferSize);
    }
}

void WaveHaSyncConfigureStandbyMessage::setValidationResults (const UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToMessage)
{
    addBuffer (VALIDATION_RESULTS_BUFFER_TAG, bufferSize, pBuffer, transferBufferOwnershipToMessage);
}

void WaveHaSyncConfigureStandbyMessage::getValidationResults (UI32 &bufferSize, void *&pBuffer, bool transferBufferOwnershipToUser)
{
    if (true == transferBufferOwnershipToUser)
    {
        pBuffer = transferBufferToUser (VALIDATION_RESULTS_BUFFER_TAG, bufferSize);
    }
    else
    {
        pBuffer = findBuffer (VALIDATION_RESULTS_BUFFER_TAG, bufferSize);
    }
}

FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage::FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage()
      : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName(), FRAMEWORK_OBJECT_MANAGER_DISCONNECT_FROM_ALL_INSTANCE_CLIENTS)
{
}


FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage::~FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage()
{
}

void FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_clientIpAddress, "clientIpAddress1"));
}

void FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage::setClientIpAddress(const string & clientIpAddress)
{
    m_clientIpAddress = clientIpAddress;
}

string const & FrameworkObjectManagerDisconnectFromAllInstanceClientsMessage::getClientIpAddress() const
{
    return m_clientIpAddress;
}

FrameworkObjectManagerPrepareNodeForHAMessage::FrameworkObjectManagerPrepareNodeForHAMessage ()
      : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_PREPARE_NODE_FOR_HA)
{

}

FrameworkObjectManagerPrepareNodeForHAMessage::~FrameworkObjectManagerPrepareNodeForHAMessage ()
{

}

FrameworkObjectManagerUpdateDatabaseSchema::FrameworkObjectManagerUpdateDatabaseSchema()
    : WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_UPDATE_DATABASE_SCHEMA)
{
}

FrameworkObjectManagerUpdateDatabaseSchema::~FrameworkObjectManagerUpdateDatabaseSchema()
{
}

FrameworkObjectManagerListenForManagedObjectMessage::FrameworkObjectManagerListenForManagedObjectMessage (const string &managedObjectClassName, const WaveManagedObjectListenOperation &managedObjectOperation)
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName(), FRAMEWORK_OBJECT_MANAGER_LISTEN_FOR_MANAGED_OBJECT),
      m_managedObjectClassName (managedObjectClassName),
      m_managedObjectOperation (managedObjectOperation)
{
}

FrameworkObjectManagerListenForManagedObjectMessage::~FrameworkObjectManagerListenForManagedObjectMessage ()
{
}

void FrameworkObjectManagerListenForManagedObjectMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString     (               &m_managedObjectClassName,  "managedObjectClassName"));
    addSerializableAttribute (new AttributeResourceId ((ResourceId *) &m_managedObjectOperation,   "managedObjectOperation"));
}

FrameworkObjectManagerHaSyncUpdateMessage::FrameworkObjectManagerHaSyncUpdateMessage()
    :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_HA_SYNC_UPDATE), 
     m_isDbSyncRequired (false)
{
}

FrameworkObjectManagerHaSyncUpdateMessage::~FrameworkObjectManagerHaSyncUpdateMessage()
{
}

void FrameworkObjectManagerHaSyncUpdateMessage::setIsDbSyncRequired (const bool &isDbSyncRequired)
{
    m_isDbSyncRequired = isDbSyncRequired;
}

bool FrameworkObjectManagerHaSyncUpdateMessage::getIsDbSyncRequired ()
{
    return (m_isDbSyncRequired);
}

FrameworkObjectManagerGetFirmwareVersionMessage::FrameworkObjectManagerGetFirmwareVersionMessage()
    :WaveMessage(WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_GET_FIRMWARE_VERSION),
     m_firmwareVersion ("")
{
}

FrameworkObjectManagerGetFirmwareVersionMessage::~FrameworkObjectManagerGetFirmwareVersionMessage()
{
}

void FrameworkObjectManagerGetFirmwareVersionMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_firmwareVersion, "firmwareVersion"));
}

void FrameworkObjectManagerGetFirmwareVersionMessage::setupAttributesForSerializationInAttributeOrderFormat ()
{
    WaveMessage::setupAttributesForSerializationInAttributeOrderFormat ();

    addAttributeNameForOrderToNameMapping ("firmwareVersion");
}

void FrameworkObjectManagerGetFirmwareVersionMessage::setFirmwareVersion (const string &firmwareVersion)
{
    m_firmwareVersion = firmwareVersion;
}

string FrameworkObjectManagerGetFirmwareVersionMessage::getFirmwareVersion () 
{
    return m_firmwareVersion;
}

FrameworkObjectManagerStartCcmdHaSyncMessage::FrameworkObjectManagerStartCcmdHaSyncMessage (const string &peerHaIpAddress, const SI32 &peerHaIpPort)
      :WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_START_CCMD_HA_SYNC_MESSAGE),
       m_peerHaIpAddress(peerHaIpAddress),
       m_peerHaIpPort(peerHaIpPort),
       m_firmwareVersion (""),
       m_haVersion (0),
       m_returnData ("")
{
}

FrameworkObjectManagerStartCcmdHaSyncMessage::~FrameworkObjectManagerStartCcmdHaSyncMessage()
{
}

void FrameworkObjectManagerStartCcmdHaSyncMessage::setPeerHaIpAddress(const string &peerHaIpAddress)
{
    m_peerHaIpAddress = peerHaIpAddress;
}

void FrameworkObjectManagerStartCcmdHaSyncMessage::setPeerHaIpPort(const SI32 &peerHaIpPort)
{
    m_peerHaIpPort = peerHaIpPort;
}

string FrameworkObjectManagerStartCcmdHaSyncMessage::getPeerHaIpAddress() const
{
    return m_peerHaIpAddress;
}

SI32 FrameworkObjectManagerStartCcmdHaSyncMessage::getPeerHaIpPort() const
{
    return m_peerHaIpPort;
}

void FrameworkObjectManagerStartCcmdHaSyncMessage::setFirmwareVersion(const string &firmwareVersion)
{
    m_firmwareVersion = firmwareVersion;
}

string FrameworkObjectManagerStartCcmdHaSyncMessage::getFirmwareVersion() const
{
    return m_firmwareVersion;
}

void FrameworkObjectManagerStartCcmdHaSyncMessage::setHAVersion(const UI32 &haVersion)
{
    m_haVersion = haVersion;
}

UI32 FrameworkObjectManagerStartCcmdHaSyncMessage::getHAVersion() const
{
    return m_haVersion;
}

void FrameworkObjectManagerStartCcmdHaSyncMessage::setReturnData (const string &returnData)
{
    m_returnData = returnData;
}

string FrameworkObjectManagerStartCcmdHaSyncMessage::getReturnData () const
{
    return m_returnData ;
}

void FrameworkObjectManagerStartCcmdHaSyncMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString  (&m_peerHaIpAddress,    "peerHaIpAddress"));
     addSerializableAttribute (new AttributeSI32    (&m_peerHaIpPort,       "peerHaIpPort"));
     addSerializableAttribute (new AttributeString  (&m_firmwareVersion,    "firmwareVersion"));
     addSerializableAttribute (new AttributeUI32    (&m_haVersion,          "haVersion"));
     addSerializableAttribute (new AttributeString  (&m_returnData,         "returnData"));
}

FrameworkObjectManagerCcmdHaSyncUpdateMessage::FrameworkObjectManagerCcmdHaSyncUpdateMessage ()
    : ManagementInterfaceMessage (WaveFrameworkObjectManager::getServiceName (), FRAMEWORK_OBJECT_MANAGER_CCMD_HA_SYNC_UPDATE_MESSAGE)
{
}

FrameworkObjectManagerCcmdHaSyncUpdateMessage::~FrameworkObjectManagerCcmdHaSyncUpdateMessage ()
{
}

void FrameworkObjectManagerCcmdHaSyncUpdateMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
}

FrameworkObjectManagerSetSyncStateMessage::FrameworkObjectManagerSetSyncStateMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_SET_SYNC_STATE_MESSAGE),
      m_syncState (UNKNOWN_SYNC_STATE)
{
}

FrameworkObjectManagerSetSyncStateMessage::FrameworkObjectManagerSetSyncStateMessage (const UI32 &syncState)
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_SET_SYNC_STATE_MESSAGE),
      m_syncState (syncState)
{
}

FrameworkObjectManagerSetSyncStateMessage::~FrameworkObjectManagerSetSyncStateMessage ()
{
}

void FrameworkObjectManagerSetSyncStateMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32 (&m_syncState, "syncState"));
}

void FrameworkObjectManagerSetSyncStateMessage::setSyncState (const UI32 &syncState)
{
    m_syncState = syncState;
}

UI32 FrameworkObjectManagerSetSyncStateMessage::getSyncState () const
{
    return m_syncState;
}

FrameworkObjectManagerGetSyncStateMessage::FrameworkObjectManagerGetSyncStateMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_GET_SYNC_STATE_MESSAGE),
      m_syncState (UNKNOWN_SYNC_STATE)
{
}

FrameworkObjectManagerGetSyncStateMessage::~FrameworkObjectManagerGetSyncStateMessage ()
{
}

void FrameworkObjectManagerGetSyncStateMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32 (&m_syncState, "syncState"));
}

void FrameworkObjectManagerGetSyncStateMessage::setSyncState (const UI32 &syncState)
{
    m_syncState = syncState;
}

UI32 FrameworkObjectManagerGetSyncStateMessage::getSyncState () const
{
    return m_syncState;
}

FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration::FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PREPARE_FOR_WARM_RECOV_WITH_DEFAULT_CONFIG_MESSAGE)
{
}

FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration::~FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration ()
{
}

void FrameworkObjectManagerPrepareForWarmRecoveryWithDefaultConfiguration::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration::FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PREPARE_FOR_HA_RECOV_WITH_PERSISTENT_CONFIG_MESSAGE),
      m_isWarmRecoveryInvolved (false)
{
}

FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration::~FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration ()
{
}

void FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_isWarmRecoveryInvolved, "isWarmRecoveryInvolved"));
}

bool FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration::isWarmHaRecoveryPreparationInProgress ()
{
    return (m_isWarmRecoveryInvolved);
}

void FrameworkObjectManagerPrepareForHaFailoverWithPersistentConfiguration::setWarmHaRecoveryPreparationInProgress (const bool &isWarmRecovery)
{
    m_isWarmRecoveryInvolved = isWarmRecovery;
}

FrameworkObjectManagerSyncConfigurationMessage::FrameworkObjectManagerSyncConfigurationMessage ()
     :WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_SYNC_CONFIGURATION_MESSAGE),
      m_waveFrameworkConfigurationFileName ("")
{
}

FrameworkObjectManagerSyncConfigurationMessage::FrameworkObjectManagerSyncConfigurationMessage (const string &waveFrameworkConfigurationFileName)
     :WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_SYNC_CONFIGURATION_MESSAGE),
      m_waveFrameworkConfigurationFileName (waveFrameworkConfigurationFileName)
{
}

FrameworkObjectManagerSyncConfigurationMessage::~FrameworkObjectManagerSyncConfigurationMessage ()
{
}

void FrameworkObjectManagerSyncConfigurationMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_waveFrameworkConfigurationFileName, "waveFrameworkConfigurationFileName"));
 //    addSerializableAttribute (new AttributeSerializableObject<WaveFrameworkConfiguration> (&m_waveFrameworkConfigurationObject, "waveFrameworkConfigurationObject"));
}

string FrameworkObjectManagerSyncConfigurationMessage::getWaveFrameworkConfigurationFileName () const
{
    return (m_waveFrameworkConfigurationFileName);
}

void FrameworkObjectManagerSyncConfigurationMessage::setWaveFrameworkConfigurationFileName (const string &waveFrameworkConfigurationFileName)
{
    m_waveFrameworkConfigurationFileName = waveFrameworkConfigurationFileName;
}

WaveFrameworkConfiguration FrameworkObjectManagerSyncConfigurationMessage::getWaveFrameworkConfigurationObject () const
{
    return (m_waveFrameworkConfigurationObject);
}

void FrameworkObjectManagerSyncConfigurationMessage::setWaveFrameworkConfigurationObject (const WaveFrameworkConfiguration &waveFrameworkConfiguration)
{
    m_waveFrameworkConfigurationObject = waveFrameworkConfiguration;
}

}
