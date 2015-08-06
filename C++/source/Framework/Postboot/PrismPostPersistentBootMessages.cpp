/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostPersistentBootMessages.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

PrismPostPersistenceBootMessage::PrismPostPersistenceBootMessage ()
    : WaveMessage (PrismFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_PASSES),
    m_isPostbootRequired            (true),
    m_executeConfigReplaySequence   (true),
    m_executeNodeReadySequence      (true),
    m_isBannerOutputToClientsRequired   (true),
    m_eventId                       (0),
    m_parameter                     (0),
    m_recoveryType                  (0)
{
}

PrismPostPersistenceBootMessage::PrismPostPersistenceBootMessage (bool isPostbootRequired, bool executeConfigReplaySequence, bool executeNodeReadySequence, bool isBannerOutputToClientsRequired)
    : WaveMessage (PrismFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_PASSES),
    m_isPostbootRequired                (isPostbootRequired),
    m_executeConfigReplaySequence       (executeConfigReplaySequence),
    m_executeNodeReadySequence          (executeNodeReadySequence),
    m_isBannerOutputToClientsRequired   (isBannerOutputToClientsRequired),
    m_eventId                           (0),
    m_parameter                         (0),
    m_recoveryType                      (0)
{
}

    PrismPostPersistenceBootMessage::PrismPostPersistenceBootMessage (const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType)
    : WaveMessage (PrismFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_PASSES),
      m_isPostbootRequired            (true),
      m_executeConfigReplaySequence   (true),
      m_executeNodeReadySequence      (true),
      m_isBannerOutputToClientsRequired   (true),
      m_eventId                       (eventId),
      m_parameter                     (parameter),
      m_recoveryType                  (recoveryType)
{
}

PrismPostPersistenceBootMessage::~PrismPostPersistenceBootMessage ()
{
}

void  PrismPostPersistenceBootMessage::setupAttributesForSerialization()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_isPostbootRequired,                "isPostbootRequired"));
     addSerializableAttribute (new AttributeBool (&m_executeConfigReplaySequence,       "executeConfigReplaySequence"));
     addSerializableAttribute (new AttributeBool (&m_executeNodeReadySequence,          "executeNodeReadySequence"));
     addSerializableAttribute (new AttributeBool (&m_isBannerOutputToClientsRequired,   "isBannerOutputToClientsRequired"));
     addSerializableAttribute (new AttributeUI32 (&m_eventId,                           "eventId"));
     addSerializableAttribute (new AttributeUI32 (&m_parameter,                         "parameter"));
     addSerializableAttribute (new AttributeResourceId (&m_recoveryType,                "recoveryType"));
}

void PrismPostPersistenceBootMessage::setEventId(const UI32 &eventId)
{
    m_eventId  =  eventId;
}

UI32 PrismPostPersistenceBootMessage::getEventId() const
{
    return (m_eventId);
}

void  PrismPostPersistenceBootMessage::setParameter(const UI32 &parameter)
{
    m_parameter  =  parameter;
}

UI32  PrismPostPersistenceBootMessage::getParameter() const
{
    return (m_parameter);
}

void  PrismPostPersistenceBootMessage::setRecoveryType(const ResourceId &recoveryType)
{
    m_recoveryType  =  recoveryType;
}

ResourceId  PrismPostPersistenceBootMessage::getRecoveryType() const
{
    return (m_recoveryType);
}


bool PrismPostPersistenceBootMessage::getExecuteConfigReplaySequence () const
{
    return (m_executeConfigReplaySequence);
}

void PrismPostPersistenceBootMessage::setExecuteConfigReplaySequence (bool executeConfigReplaySequence)
{
    m_executeConfigReplaySequence = executeConfigReplaySequence;
}

bool PrismPostPersistenceBootMessage::getExecuteNodeReadySequence () const
{
    return (m_executeNodeReadySequence);
}

void PrismPostPersistenceBootMessage::setExecuteNodeReadySequence (bool executeNodeReadySequence)
{
    m_executeNodeReadySequence = executeNodeReadySequence;
}

bool PrismPostPersistenceBootMessage::getIsPostbootRequired () const
{
    return (m_isPostbootRequired);
}

void PrismPostPersistenceBootMessage::setIsPostbootRequired (bool isPostbootRequired)
{
    m_isPostbootRequired = isPostbootRequired;
}

bool PrismPostPersistenceBootMessage::getIsBannerOutputToClientsRequired () const
{
    return (m_isBannerOutputToClientsRequired);
}

void PrismPostPersistenceBootMessage::setIsBannerOutputToClientsRequired (bool isBannerOutputToClientsRequired)
{
    m_isBannerOutputToClientsRequired = isBannerOutputToClientsRequired;
}


PrismPostPersistenceBootServiceAndWaveSlotsMessage::PrismPostPersistenceBootServiceAndWaveSlotsMessage ()
    : WaveMessage (PrismFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_SERVICE_AND_WAVE_SLOTS)
{
}

PrismPostPersistenceBootServiceAndWaveSlotsMessage::~PrismPostPersistenceBootServiceAndWaveSlotsMessage ()
{
}

void PrismPostPersistenceBootServiceAndWaveSlotsMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

}
