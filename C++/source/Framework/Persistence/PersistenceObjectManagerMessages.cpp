/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerMessages.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"

namespace WaveNs
{

PersistenceObjectManagerAddXPathStringsMessage::PersistenceObjectManagerAddXPathStringsMessage (const vector<string> &xPathStrings)
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_ADD_XPATH_STRINGS_MESSAGE),
      m_xPathStrings                        (xPathStrings)
{
}

PersistenceObjectManagerAddXPathStringsMessage::PersistenceObjectManagerAddXPathStringsMessage ()
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_ADD_XPATH_STRINGS_MESSAGE)
{
}

PersistenceObjectManagerAddXPathStringsMessage::~PersistenceObjectManagerAddXPathStringsMessage ()
{
}

void PersistenceObjectManagerAddXPathStringsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_xPathStrings, "xPathStrings"));
}

vector<string> PersistenceObjectManagerAddXPathStringsMessage::getXPathStrings () const
{
    return m_xPathStrings;
}

void PersistenceObjectManagerAddXPathStringsMessage::setXPathStrings (const vector<string> &xPathStrings)
{
    m_xPathStrings = xPathStrings;
}




PersistenceObjectManagerDeleteXPathStringsMessage::PersistenceObjectManagerDeleteXPathStringsMessage (const vector<string> &xPathStrings)
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_DELETE_XPATH_STRINGS_MESSAGE),
      m_xPathStrings                        (xPathStrings)
{
}

PersistenceObjectManagerDeleteXPathStringsMessage::PersistenceObjectManagerDeleteXPathStringsMessage ()
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_DELETE_XPATH_STRINGS_MESSAGE)
{
}

PersistenceObjectManagerDeleteXPathStringsMessage::~PersistenceObjectManagerDeleteXPathStringsMessage ()
{
}

void PersistenceObjectManagerDeleteXPathStringsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_xPathStrings, "xPathStrings"));
}

vector<string> PersistenceObjectManagerDeleteXPathStringsMessage::getXPathStrings () const
{
    return m_xPathStrings;
}

void PersistenceObjectManagerDeleteXPathStringsMessage::setXPathStrings (const vector<string> &xPathStrings)
{
    m_xPathStrings = xPathStrings;
}




// This message will typically come from any node, and will be serviced by PersistenceObjectManager.

PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage (const vector<string> &xPathStrings)
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_GET_LAST_UPDATE_TIMESTAMPS_FOR_XPATH_STRINGS_MESSAGE),
      m_xPathStrings                        (xPathStrings)
{
}

PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage ()
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_GET_LAST_UPDATE_TIMESTAMPS_FOR_XPATH_STRINGS_MESSAGE)
{
}

PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::~PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage ()
{
}

void PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector         (&m_xPathStrings,          "xPathStrings"));
     addSerializableAttribute (new AttributeUI64Vector           (&m_lastUpdatedTimestamps, "lastUpdatedTimestamps"));
}

vector<string> PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::getXPathStrings () const
{
    return m_xPathStrings;
}

void PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::setXPathStrings (const vector<string> &xPathStrings)
{
    m_xPathStrings = xPathStrings;
}

vector<UI64> PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::getLastUpdatedTimestamps () const
{
    return m_lastUpdatedTimestamps;
}

void PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage::setLastUpdatedTimestamps (const vector<UI64> &lastUpdatedTimestamps)
{
    m_lastUpdatedTimestamps = lastUpdatedTimestamps;
}




PersistenceObjectManagerResetXPathStringsTimestampsMessage::PersistenceObjectManagerResetXPathStringsTimestampsMessage ()
    : ManagementInterfaceMessage            (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_RESET_XPATH_STRINGS_TIMESTAMPS)
{
}

PersistenceObjectManagerResetXPathStringsTimestampsMessage::~PersistenceObjectManagerResetXPathStringsTimestampsMessage ()
{
}

void PersistenceObjectManagerResetXPathStringsTimestampsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
}


}
