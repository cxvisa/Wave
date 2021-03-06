/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Balachandar Mani                                             *
 ***************************************************************************/

#include "SystemManagement/WaveConfigurationSegmentContext.h"
#include "Framework/Utils/TraceUtils.h"
#include "WaveResourceIdEnums.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

WaveConfigurationSegmentContext::WaveConfigurationSegmentContext ()
    : m_locationId          (0)
{
	m_configHandlerStatus = WAVE_MESSAGE_SUCCESS;
}

WaveConfigurationSegmentContext::~WaveConfigurationSegmentContext ()
{

}

string WaveConfigurationSegmentContext::getManagedObjectClassName () const
{
    return (m_managedObjectClassName);
}

void WaveConfigurationSegmentContext::setManagedObjectClassName (const string &managedObjectClassName)
{
    m_managedObjectClassName = managedObjectClassName;
}

ObjectId WaveConfigurationSegmentContext::getOperateOnWaveManagedObjectId() const
{
    return (m_operateOnWaveManagedObjectId);
}

void WaveConfigurationSegmentContext::setOperateOnWaveManagedObjectId(const WaveNs::ObjectId& waveManagedObjectId)
{
    m_operateOnWaveManagedObjectId = waveManagedObjectId;
}

vector<UI32> WaveConfigurationSegmentContext::getAttributeUserTags () const
{
    return (m_attributeUserTags);
}

void WaveConfigurationSegmentContext::setAttributeUserTags(const std::vector< UI32 >& attributeUserTags)
{
    m_attributeUserTags = attributeUserTags;
}

vector<string> WaveConfigurationSegmentContext::getAttributeNames () const
{
    return (m_attributeNames);
}

void WaveConfigurationSegmentContext::setAttributeNames (const vector<string> &attributeNames)
{
    m_attributeNames = attributeNames;
}

vector<string> WaveConfigurationSegmentContext::getAttributeValues () const
{
    return (m_attributeValues);
}

void WaveConfigurationSegmentContext::setAttributeValues (const vector< string >& attributeValues)
{
    m_attributeValues = attributeValues;
}

ObjectId WaveConfigurationSegmentContext::getParentObjectId () const
{
    return (m_parentObjectId);
}

void WaveConfigurationSegmentContext::setParentObjectId (const ObjectId &parentObjectId)
{
    m_parentObjectId = parentObjectId;
}

UI32 WaveConfigurationSegmentContext::getChildUserTag () const
{
    return (m_childUserTag);
}

void WaveConfigurationSegmentContext::setChildUserTag (const UI32 &childUserTag)
{
    m_childUserTag = childUserTag;
}

LocationId WaveConfigurationSegmentContext::getLocationId() const {
    return m_locationId;
}
void WaveConfigurationSegmentContext::setLocationId(const LocationId &locationId) {
    m_locationId = locationId;
}

ResourceId WaveConfigurationSegmentContext::getConfigHandlerStatus () const
{
    return (m_configHandlerStatus);
}

void WaveConfigurationSegmentContext::setConfigHandlerStatus (const ResourceId configHandlerStatus)
{
	m_configHandlerStatus = configHandlerStatus;
}

string WaveConfigurationSegmentContext::getErrorString () const
{
	return FrameworkToolKit::localize (m_configHandlerStatus);
}

}
