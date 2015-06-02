/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#include "Cluster/Local/WaveSlotLocalManagedObjectBase.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

// Dummy Constructor: This should not be called
WaveSlotLocalManagedObjectBase::WaveSlotLocalManagedObjectBase ()
{
} 

WaveSlotLocalManagedObjectBase::WaveSlotLocalManagedObjectBase (WaveManagedObject *pWaveManagedObject)
    : m_pWaveManagedObject (pWaveManagedObject),
      m_slotNumber         (0),
      m_objectType         (0),
      m_hwType             (0),
      m_hwId               (0),
      m_slotState          (0),
      m_reason             (0),
      m_version            (0)
{
}

WaveSlotLocalManagedObjectBase::WaveSlotLocalManagedObjectBase (WaveManagedObject *pWaveManagedObject, UI32 &slotNumber, UI32 &objectType, UI32 &hwType, UI32 &hwId, UI32 &slotState, UI32 &reason, UI32 &version)
    : m_pWaveManagedObject (pWaveManagedObject),
      m_slotNumber         (slotNumber),
      m_objectType         (objectType),
      m_hwType             (hwType),
      m_hwId               (hwId),
      m_slotState          (slotState),
      m_reason             (reason),
      m_version            (version)
{
}

WaveSlotLocalManagedObjectBase::~WaveSlotLocalManagedObjectBase ()
{
}

void WaveSlotLocalManagedObjectBase::setupAttributesForPersistence ()
{
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_slotNumber, "slotNumber"));
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_objectType, "objectType"));
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_hwType, "hwType"));
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_hwId, "hwId"));
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_slotState, "slotState"));
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_reason, "reason"));
    m_pWaveManagedObject->addPersistableAttribute (new AttributeUI32 (&m_version, "version"));
}

void WaveSlotLocalManagedObjectBase::setupAttributesForCreate ()
{
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_slotNumber, "slotNumber"));
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_objectType, "objectType"));
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_hwType, "hwType"));
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_hwId, "hwId"));
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_slotState, "slotState"));
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_reason, "reason"));
    m_pWaveManagedObject->addPersistableAttributeForCreate (new AttributeUI32 (&m_version, "version"));
}

string WaveSlotLocalManagedObjectBase::getClassName ()
{
    return ("WaveSlotLocalManagedObjectBase");
}

UI32 WaveSlotLocalManagedObjectBase::getSlotNumber ()
{
    return (m_slotNumber);
}

void WaveSlotLocalManagedObjectBase::setSlotNumber (const UI32 &slotNumber)
{
    m_slotNumber = slotNumber;
}

UI32 WaveSlotLocalManagedObjectBase::getObjectType ()
{
    return (m_objectType);
}

void WaveSlotLocalManagedObjectBase::setObjectType (const UI32 &objectType)
{
    m_objectType = objectType;
}

UI32 WaveSlotLocalManagedObjectBase::getReason ()
{
    return (m_reason);
}

void WaveSlotLocalManagedObjectBase::setReason (const UI32 &reason)
{
    m_reason = reason;
}

UI32 WaveSlotLocalManagedObjectBase::getHwType ()
{
    return (m_hwType);
}

void WaveSlotLocalManagedObjectBase::setHwType (const UI32 &hwType)
{
    m_hwType = hwType;
}

UI32 WaveSlotLocalManagedObjectBase::getHwId ()
{
    return (m_hwId);
}

void WaveSlotLocalManagedObjectBase::setHwId (const UI32 &hwId)
{
    m_hwId = hwId;
}

UI32 WaveSlotLocalManagedObjectBase::getVersion ()
{
    return (m_version);
}

void WaveSlotLocalManagedObjectBase::setVersion (const UI32 &version)
{
    m_version = version;
}

UI32 WaveSlotLocalManagedObjectBase::getSlotState ()
{
    return (m_slotState);
}

void WaveSlotLocalManagedObjectBase::setSlotState (const UI32 &slotState)
{
    m_slotState = slotState;
}

}
