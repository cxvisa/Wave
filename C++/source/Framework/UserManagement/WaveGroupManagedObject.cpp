/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/UserManagement/WaveGroupManagedObject.h"
#include "Framework/UserManagement/WaveUserManagedObject.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/PrismPersistableObject.h"

#include <algorithm>

namespace WaveNs
{

WaveGroupManagedObject::WaveGroupManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement           (pWaveObjectManager),
      PrismPersistableObject (WaveGroupManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject      (pWaveObjectManager),
      m_groupId              (0),
      m_isActive             (false)
{
}

WaveGroupManagedObject::WaveGroupManagedObject (WaveObjectManager *pWaveObjectManager, const string &name)
    : WaveElement           (pWaveObjectManager),
      PrismPersistableObject (WaveGroupManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject      (pWaveObjectManager),
      m_groupId              (0),
      m_isActive             (false)
{
    setName (name);
}

WaveGroupManagedObject::~WaveGroupManagedObject ()
{
}

string WaveGroupManagedObject::getClassName ()
{
    return ("WaveGroupManagedObject");
}

void WaveGroupManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                      (&m_groupId,  "groupId"));
    addPersistableAttribute (new AttributeBool                      (&m_isActive, "isActive"));
    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_associatedUserObjectIds, "associatedUserObjectIds", getClassName (), getObjectId (), WaveUserManagedObject::getClassName ()));
}

void WaveGroupManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                      (&m_groupId,  "groupId"));
    addPersistableAttributeForCreate (new AttributeBool                      (&m_isActive, "isActive"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_associatedUserObjectIds, "associatedUserObjectIds", getClassName (), getObjectId (), WaveUserManagedObject::getClassName ()));
}

UI32 WaveGroupManagedObject::getGroupId () const
{
    return (m_groupId);
}

void WaveGroupManagedObject::setGroupId (const UI32 &groupId)
{
    m_groupId = groupId;
}

bool WaveGroupManagedObject::getIsActive ()const
{
    return (m_isActive);
}

void WaveGroupManagedObject::setIsActive (const bool &isActive)
{
    m_isActive = isActive;
}

vector<ObjectId> WaveGroupManagedObject::getAssociatedUserObjectIds () const
{
    return (m_associatedUserObjectIds);
}

void WaveGroupManagedObject::setAssociatedUserObjectIds (const vector<ObjectId> &associatedUserObjectIds)
{
    m_associatedUserObjectIds = associatedUserObjectIds;
}

void WaveGroupManagedObject::addAssociatedUserObjectId (const ObjectId &associatedUserObjectId)
{
    if (false == (isAnAssociatedUserObjectId (associatedUserObjectId)))
    {
        m_associatedUserObjectIds.push_back (associatedUserObjectId);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveGroupManagedObject::addAssociatedUserObjectId : Adding a duplicate User Object Id : " + associatedUserObjectId.toString ());
        waveAssert (false, __FILE__, __LINE__);
    }
}

void WaveGroupManagedObject::deleteAssociatedUserObjectId (const ObjectId &associatedUserObjectId)
{
    vector<ObjectId>::iterator element    = std::find (m_associatedUserObjectIds.begin (), m_associatedUserObjectIds.end (), associatedUserObjectId);
    vector<ObjectId>::iterator endElement = m_associatedUserObjectIds.end ();

    if (element != endElement)
    {
        m_associatedUserObjectIds.erase (element);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveGroupManagedObject::addAssociatedUserObjectId : Trying to delete a non associated User Object Id : " + associatedUserObjectId.toString ());
        waveAssert (false, __FILE__, __LINE__);
    }
}

bool WaveGroupManagedObject::isAnAssociatedUserObjectId (const ObjectId &associatedUserObjectId) const
{
    vector<ObjectId>::const_iterator element    = std::find (m_associatedUserObjectIds.begin (), m_associatedUserObjectIds.end (), associatedUserObjectId);
    vector<ObjectId>::const_iterator endElement = m_associatedUserObjectIds.end ();

    if (element != endElement)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

}
