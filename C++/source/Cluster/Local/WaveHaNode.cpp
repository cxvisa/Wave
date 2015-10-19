/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Cluster/Local/WaveHaNode.h"
#include "Framework/Attributes/AttributeEnum.h"

namespace WaveNs
{

WaveHaNode::WaveHaNode (WaveObjectManager *pWaveObjectManager)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (WaveHaNode::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pWaveObjectManager)
{
    setOwnerWaveNodeObjectId (getObjectId ());
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

WaveHaNode::WaveHaNode (WaveObjectManager *pWaveObjectManager, const WaveHaNodeRole &role, const string &internalIpAddress, const string &serialNumber)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (WaveHaNode::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pWaveObjectManager),
      m_haRole                   (role),
      m_internalIpAddress        (internalIpAddress),
      m_serialNumber             (serialNumber)
{
    setOwnerWaveNodeObjectId (getObjectId ());
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

WaveHaNode::WaveHaNode (WaveObjectManager *pWaveObjectManager, const WaveHaNodeRole &role)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (WaveHaNode::getClassName (), WaveLocalManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this),
      WaveLocalManagedObject     (pWaveObjectManager),
      m_haRole                   (role),
      m_internalIpAddress        (""),
      m_serialNumber             ("")
{
    setOwnerWaveNodeObjectId (getObjectId ());
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

WaveHaNode::~WaveHaNode ()
{
}

string WaveHaNode::getClassName ()
{
    return ("WaveHaNode");
}

void WaveHaNode::setupAttributesForPersistence ()
{
    WaveLocalManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeEnum       ((UI32 *) (&m_haRole),       "haRole"));
    addPersistableAttribute (new AttributeString     (&m_internalIpAddress,  "internalIpAddress"));
    addPersistableAttribute (new AttributeString     (&m_serialNumber,  "serialNumber"));
}

void WaveHaNode::setupAttributesForCreate ()
{
    WaveLocalManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeEnum       ((UI32 *) (&m_haRole),       "haRole"));
    addPersistableAttributeForCreate (new AttributeString     (&m_internalIpAddress,  "internalIpAddress"));
    addPersistableAttributeForCreate (new AttributeString     (&m_serialNumber,  "serialNumber"));
}

string WaveHaNode::getInternalIpAddress () const
{
    return (m_internalIpAddress);
}

void WaveHaNode::setInternalIpAddress (const string &ipAddress)
{
    m_internalIpAddress = ipAddress;
}

string WaveHaNode::getSerialNumber () const
{
    return (m_serialNumber);
}

void WaveHaNode::setSerialNumber (const string &serialNumber)
{
    m_serialNumber = serialNumber;
}

WaveHaNodeRole WaveHaNode::getHaRole () const
{
    return (m_haRole);
}

void WaveHaNode::setHaRole (const WaveHaNodeRole &role)
{
    m_haRole = role;
}

}
