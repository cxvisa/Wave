/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/UserManagement/WaveUserManagedObject.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/PrismPersistableObject.h"
#include "Framework/UserManagement/WaveGroupManagedObject.h"

namespace WaveNs
{

WaveUserManagedObject::WaveUserManagedObject (WaveObjectManager *pWaveObjectManager)
    : PrismElement           (pWaveObjectManager),
      PrismPersistableObject (WaveUserManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject      (pWaveObjectManager),
      m_userId               (0),
      m_isActive             (false)
{
}

WaveUserManagedObject::WaveUserManagedObject (WaveObjectManager *pWaveObjectManager, const string &name)
    : PrismElement           (pWaveObjectManager),
      PrismPersistableObject (WaveUserManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject      (pWaveObjectManager),
      m_userId               (0),
      m_isActive             (false)
{
    setName (name);
}

WaveUserManagedObject::~WaveUserManagedObject ()
{
}

string WaveUserManagedObject::getClassName ()
{
    return ("WaveUserManagedObject");
}

void WaveUserManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeUI32                      (&m_userId,                   "userId"));
    addPersistableAttribute (new AttributeObjectIdAssociation       (&m_groupObjectId,            "groupObjectId",            WaveGroupManagedObject::getClassName ()));
    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_associatedGroupObjectIds, "associatedGroupObjectIds", getClassName (), getObjectId (), WaveGroupManagedObject::getClassName ()));
    addPersistableAttribute (new AttributeString                    (&m_encryptedPassword,        "encryptedPassword"));
    addPersistableAttribute (new AttributeBool                      (&m_isActive,                 "isActive"));
    addPersistableAttribute (new AttributeString                    (&m_homeDirectory,            "homeDirectory"));
}

void WaveUserManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeUI32                      (&m_userId,                   "userId"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation       (&m_groupObjectId,            "groupObjectId",            WaveGroupManagedObject::getClassName ()));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_associatedGroupObjectIds, "associatedGroupObjectIds", getClassName (), getObjectId (), WaveGroupManagedObject::getClassName ()));
    addPersistableAttributeForCreate (new AttributeString                    (&m_encryptedPassword,        "encryptedPassword"));
    addPersistableAttributeForCreate (new AttributeBool                      (&m_isActive,                 "isActive"));
    addPersistableAttributeForCreate (new AttributeString                    (&m_homeDirectory,            "homeDirectory"));
}

UI32 WaveUserManagedObject::getUserId () const
{
    return (m_userId);
}

void WaveUserManagedObject::setUserId (const UI32 &userId)
{
    m_userId = userId;
}

ObjectId WaveUserManagedObject::getGroupObjectId () const
{
    return (m_groupObjectId);
}

void WaveUserManagedObject::setGroupObjectId (const ObjectId &groupObjectId)
{
    m_groupObjectId = groupObjectId;
}

string WaveUserManagedObject::getEncryptedPassword () const
{
    return (m_encryptedPassword);
}

void WaveUserManagedObject::setEncryptedPassword (const string &encryptedPassword)
{
    m_encryptedPassword = encryptedPassword;
}

bool WaveUserManagedObject::getIsActive () const
{
    return (m_isActive);
}

void WaveUserManagedObject::setIsActive (const bool &isActive)
{
    m_isActive = isActive;
}

string WaveUserManagedObject::getHomeDirectory () const
{
    return (m_homeDirectory);
}

void WaveUserManagedObject::setHomeDirectory (const string &homeDirectory)
{
    m_homeDirectory = homeDirectory;
}

}
