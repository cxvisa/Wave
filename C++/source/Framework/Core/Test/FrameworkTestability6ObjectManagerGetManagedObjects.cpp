/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/FrameworkTestability6ObjectManagerGetManagedObjects.h"
#include "Framework/Core/Test/FrameworkTestabilityTypes.h"
#include "Framework/Core/Test/FrameworkTestability6ObjectManager.h"

namespace WaveNs
{

FrameworkTestability6ObjectManagerGetManagedObjects::FrameworkTestability6ObjectManagerGetManagedObjects()
        : ManagementInterfaceMessage (FrameworkTestability6ObjectManager::getWaveServiceName (), FRAMEWORK_TESTABILITY_6_GET_MANAGED_OBJECTS),
        m_managedObjectClassName   (""),
        m_schemaName               ("WaveCurrent"),
        m_numberOfManagedObjects   (0),
        m_useRawFormat             (false)
{
}

FrameworkTestability6ObjectManagerGetManagedObjects::FrameworkTestability6ObjectManagerGetManagedObjects(const string &managedObjectClassName, const string &schemaName)
        : ManagementInterfaceMessage (FrameworkTestability6ObjectManager::getWaveServiceName (), FRAMEWORK_TESTABILITY_6_GET_MANAGED_OBJECTS),
        m_managedObjectClassName   (managedObjectClassName),
        m_schemaName               (schemaName),
        m_numberOfManagedObjects   (0),
        m_useRawFormat             (false)
{
}

FrameworkTestability6ObjectManagerGetManagedObjects::~FrameworkTestability6ObjectManagerGetManagedObjects ()
{
}

void FrameworkTestability6ObjectManagerGetManagedObjects::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString       (&m_managedObjectClassName,    "managedObjectClassName"));
     addSerializableAttribute (new AttributeString       (&m_schemaName,                "schemaName"));
     addSerializableAttribute (new AttributeUI32         (&m_numberOfManagedObjects,    "numberOfManagedObjects"));
     addSerializableAttribute (new AttributeStringVector (&m_managedObjects,            "managedObjects"));
     addSerializableAttribute (new AttributeBool         (&m_useRawFormat,              "useRawFormat"));
}

string FrameworkTestability6ObjectManagerGetManagedObjects::getManagedObjectClassName () const
{
    return (m_managedObjectClassName);
}

void FrameworkTestability6ObjectManagerGetManagedObjects::setManagedObjectClassName (const string &managedObjectClassName)
{
    m_managedObjectClassName = managedObjectClassName;
}

string FrameworkTestability6ObjectManagerGetManagedObjects::getSchemaName () const
{
    return (m_schemaName);
}

void FrameworkTestability6ObjectManagerGetManagedObjects::setSchemaName (const string &schemaName)
{
    m_schemaName = schemaName;
}

UI32 FrameworkTestability6ObjectManagerGetManagedObjects::getNumberOfManagedObjects () const
{
    return (m_numberOfManagedObjects);
}

void FrameworkTestability6ObjectManagerGetManagedObjects::setNumberOfManagedObjects (const UI32 &numberOfManagedObjects)
{
    m_numberOfManagedObjects = numberOfManagedObjects;
}

vector<string> &FrameworkTestability6ObjectManagerGetManagedObjects::getManagedObjects ()
{
    return (m_managedObjects);
}

bool FrameworkTestability6ObjectManagerGetManagedObjects::getUseRawFormat() const
{
    return (m_useRawFormat);
}

void FrameworkTestability6ObjectManagerGetManagedObjects::setUseRawFormat(const bool& useRawFormat)
{
    m_useRawFormat = useRawFormat;
}

}
