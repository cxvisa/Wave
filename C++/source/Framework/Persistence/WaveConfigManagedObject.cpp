/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/Persistence/WaveConfigManagedObject.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{
WaveConfigManagedObject::WaveConfigManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveConfigurationAttributes ("", "", 0),
      WaveElement               (pWaveObjectManager),
      WavePersistableObject     (WaveConfigManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager)
{
    setEmptyNeededOnPersistentBoot (false);
    setEmptyNeededOnPersistentBootWithDefault (true);
}

WaveConfigManagedObject::~WaveConfigManagedObject ()
{
}

string WaveConfigManagedObject::getClassName ()
{
    return ("WaveConfigManagedObject");
}

void WaveConfigManagedObject::setConfigName (const string &configName)
{
    m_configName = configName;
}

string WaveConfigManagedObject::getConfigName () const
{
    return (m_configName);
}

void WaveConfigManagedObject::setConfigValue (const string &configValue)
{
    m_configValue = configValue;
}

string WaveConfigManagedObject::getConfigValue () const
{
    return (m_configValue);
}

void WaveConfigManagedObject::setConfigAttributeType (const ResourceId &configAttributeType)
{
    m_configAttributeType = configAttributeType;
}

ResourceId WaveConfigManagedObject::getConfigAttributeType () const
{
    return (m_configAttributeType);
}

void WaveConfigManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeString (&m_configName, "configName"));
    addPersistableAttribute (new AttributeString (&m_configValue, "configValue"));
    addPersistableAttribute (new AttributeResourceId (&m_configAttributeType, "configAttributeType"));
}

void WaveConfigManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeString (&m_configName, "configName"));
    addPersistableAttributeForCreate (new AttributeString (&m_configValue, "configValue"));
    addPersistableAttributeForCreate (new AttributeResourceId (&m_configAttributeType, "configAttributeType"));

    vector<string > keyName;
    keyName.push_back ("configName");
    setUserDefinedKeyCombination (keyName);
}

}
