/**************************************************************************************
 *  @file : PersistenceObjectManagerCompareDBMessage.cpp
 *   Copyright (C) 2010 Vidyasagara Guntaka                                           *
 *   All rights reserved.                                                             *
 *   Description : Implements a message PersistenceObjectManagerCompareDBMessage used *
                   for databases compare on each nodes in cluster with Primary.       *
 *   Author : Pritee Ghosh                                                            *
 *   Date   : 02/22/2011                                                              *
 **************************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerCompareDBMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"

namespace WaveNs
{

PersistenceObjectManagerCompareDBMessage::PersistenceObjectManagerCompareDBMessage ()
    : ManagementInterfaceMessage (PersistenceObjectManager::getPrismServiceName (), PERSISTENCE_OBNJECT_MANAGER_COMPARE_DB)
{
}

PersistenceObjectManagerCompareDBMessage::~PersistenceObjectManagerCompareDBMessage ()
{
}

void PersistenceObjectManagerCompareDBMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32Vector         (&m_matchingDbLocations,                 "matchingDbLocations"));
     addSerializableAttribute (new AttributeUI32Vector         (&m_nonMatchingDbLocations,              "nonMatchingDbLocations"));
     addSerializableAttribute (new AttributeUI32Vector         (&m_failedLocations,                     "failedLocations"));
     addSerializableAttribute (new AttributeStringVector       (&m_ipAndPortsForMatchingDbLocations,    "ipAndPortsForMatchingDbLocations"));
     addSerializableAttribute (new AttributeStringVector       (&m_ipAndPortsForNonMatchingDbLocations, "ipAndPortsForNonMatchingDbLocations"));
     addSerializableAttribute (new AttributeStringVector       (&m_ipAndPortsForFailedLocations,        "ipAndPortsForFailedLocations"));
}

vector<LocationId> PersistenceObjectManagerCompareDBMessage::getMatchingDbLocations () const
{
    return (m_matchingDbLocations);
}

void PersistenceObjectManagerCompareDBMessage::setMatchingDbLocations (const vector<UI32> &matchingDbLocations)
{
    m_matchingDbLocations = matchingDbLocations;
}

vector<LocationId> PersistenceObjectManagerCompareDBMessage::getNonMatchingDbLocations () const
{
    return (m_nonMatchingDbLocations);
}

void PersistenceObjectManagerCompareDBMessage::setNonMatchingDbLocations (const vector<UI32> &nonMatchingDbLocations)
{
    m_nonMatchingDbLocations = nonMatchingDbLocations;
}

vector<LocationId> PersistenceObjectManagerCompareDBMessage::getFailedLocations () const
{
    return (m_failedLocations);
}

void PersistenceObjectManagerCompareDBMessage::setFailedLocations (const vector<UI32> &failedLocations)
{
    m_failedLocations = failedLocations;
}

vector<string> PersistenceObjectManagerCompareDBMessage::getIpAndPortsForMatchingDbLocations () const
{
    return (m_ipAndPortsForMatchingDbLocations);
}

void PersistenceObjectManagerCompareDBMessage::setIpAndPortsForMatchingDbLocations (const vector<string> &ipAndPortsForMatchingDbLocations)
{
    m_ipAndPortsForMatchingDbLocations = ipAndPortsForMatchingDbLocations;   
}

vector<string> PersistenceObjectManagerCompareDBMessage::getIpAndPortsForNonMatchingDbLocations () const
{
    return (m_ipAndPortsForNonMatchingDbLocations);
}

void PersistenceObjectManagerCompareDBMessage::setIpAndPortsForNonMatchingDbLocations (const vector<string> &ipAndPortsForNonMatchingDbLocations)
{
    m_ipAndPortsForNonMatchingDbLocations = ipAndPortsForNonMatchingDbLocations;
}

vector<string> PersistenceObjectManagerCompareDBMessage::getIpAndPortsForFailedLocations () const
{
    return (m_ipAndPortsForFailedLocations);
}

void PersistenceObjectManagerCompareDBMessage::setIpAndPortsForFailedLocations (const vector<string> &ipAndPortsForFailedLocations)
{
    m_ipAndPortsForFailedLocations = ipAndPortsForFailedLocations;
}
}
