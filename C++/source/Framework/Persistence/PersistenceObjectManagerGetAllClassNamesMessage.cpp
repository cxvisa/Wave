/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerGetAllClassNamesMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Attributes/Attributes.h"
#include "SystemManagement/WaveConfigurationSegmentMap.h"

namespace WaveNs
{

PersistenceObjectManagerGetAllClassNamesMessage::PersistenceObjectManagerGetAllClassNamesMessage ()
    : ManagementInterfaceMessage (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_GET_ALL_CLASS_NAMES)
{
}

PersistenceObjectManagerGetAllClassNamesMessage::~PersistenceObjectManagerGetAllClassNamesMessage ()
{
}

void PersistenceObjectManagerGetAllClassNamesMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeStringVector (&m_allClassNames,                          "allClassNames"));
    addSerializableAttribute (new AttributeStringVector (&m_configurationSegmentNames,              "configurationSegmentNames"));
    addSerializableAttribute (new AttributeStringVector (&m_classNamesForconfigurationSegmentNames, "classNamesForconfigurationSegmentNames"));
}

void PersistenceObjectManagerGetAllClassNamesMessage::getAllClassNames (vector<string> &allClassNames) const
{
    allClassNames = m_allClassNames;
}

void PersistenceObjectManagerGetAllClassNamesMessage::getAllClassNames (set<string> &allClassNames) const
{
    UI32 numberOfClassNames = m_allClassNames.size ();
    UI32 i                  = 0;

    for (i = 0; i < numberOfClassNames; i++)
    {
        allClassNames.insert (m_allClassNames[i]);
    }
}

void PersistenceObjectManagerGetAllClassNamesMessage::setAllClassNames (const vector<string> &allClassNames)
{
    m_allClassNames = allClassNames;

    computeConfigurationSegmentNames ();
}

void PersistenceObjectManagerGetAllClassNamesMessage::setAllClassNames (const set<string> &allClassNames)
{
    set<string>::const_iterator element    = allClassNames.begin ();
    set<string>::const_iterator endElement = allClassNames.end   ();

    while (endElement != element)
    {
        m_allClassNames.push_back (*element);

        element++;
    }

    computeConfigurationSegmentNames ();
}

void PersistenceObjectManagerGetAllClassNamesMessage::getConfigurationSegmentNames (vector<string> &configurationSegmentNames) const
{
    configurationSegmentNames = m_configurationSegmentNames;
}

void PersistenceObjectManagerGetAllClassNamesMessage::setConfigurationSegmentNames (const vector<string> &configurationSegmentNames)
{
    m_configurationSegmentNames = configurationSegmentNames;
}

void PersistenceObjectManagerGetAllClassNamesMessage::getClassNamesForConfigurationSegmentNames (vector<string> &classNamesForConfigurationSegmentNames) const
{
    classNamesForConfigurationSegmentNames = m_classNamesForconfigurationSegmentNames;
}

void PersistenceObjectManagerGetAllClassNamesMessage::setClassNamesForConfigurationSegmentNames (const vector<string> &classNamesForConfigurationSegmentNames)
{
    m_classNamesForconfigurationSegmentNames = classNamesForConfigurationSegmentNames;
}

void PersistenceObjectManagerGetAllClassNamesMessage::computeConfigurationSegmentNames ()
{
    WaveConfigurationSegmentMap::getAllConfigurationSegmentNamesAndManagedObjectClassNames (m_configurationSegmentNames, m_classNamesForconfigurationSegmentNames);
}

}
