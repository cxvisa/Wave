/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Postboot/WavePostPersistentBootMessages.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

WavePostPersistenceBootMessage::WavePostPersistenceBootMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_PASSES),
    m_isPostbootRequired            (true),
    m_executeConfigReplaySequence   (true),
    m_executeNodeReadySequence      (true),
    m_isBannerOutputToClientsRequired   (true),
    m_eventId                       (0),
    m_parameter                     (0),
    m_recoveryType                  (0)
{
}

WavePostPersistenceBootMessage::WavePostPersistenceBootMessage (bool isPostbootRequired, bool executeConfigReplaySequence, bool executeNodeReadySequence, bool isBannerOutputToClientsRequired)
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_PASSES),
    m_isPostbootRequired                (isPostbootRequired),
    m_executeConfigReplaySequence       (executeConfigReplaySequence),
    m_executeNodeReadySequence          (executeNodeReadySequence),
    m_isBannerOutputToClientsRequired   (isBannerOutputToClientsRequired),
    m_eventId                           (0),
    m_parameter                         (0),
    m_recoveryType                      (0)
{
}

    WavePostPersistenceBootMessage::WavePostPersistenceBootMessage (const UI32 &eventId, const UI32 &parameter, const ResourceId &recoveryType)
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_PASSES),
      m_isPostbootRequired            (true),
      m_executeConfigReplaySequence   (true),
      m_executeNodeReadySequence      (true),
      m_isBannerOutputToClientsRequired   (true),
      m_eventId                       (eventId),
      m_parameter                     (parameter),
      m_recoveryType                  (recoveryType)
{
}

WavePostPersistenceBootMessage::~WavePostPersistenceBootMessage ()
{
}

void  WavePostPersistenceBootMessage::setupAttributesForSerialization()
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

void WavePostPersistenceBootMessage::setEventId(const UI32 &eventId)
{
    m_eventId  =  eventId;
}

UI32 WavePostPersistenceBootMessage::getEventId() const
{
    return (m_eventId);
}

void  WavePostPersistenceBootMessage::setParameter(const UI32 &parameter)
{
    m_parameter  =  parameter;
}

UI32  WavePostPersistenceBootMessage::getParameter() const
{
    return (m_parameter);
}

void  WavePostPersistenceBootMessage::setRecoveryType(const ResourceId &recoveryType)
{
    m_recoveryType  =  recoveryType;
}

ResourceId  WavePostPersistenceBootMessage::getRecoveryType() const
{
    return (m_recoveryType);
}


bool WavePostPersistenceBootMessage::getExecuteConfigReplaySequence () const
{
    return (m_executeConfigReplaySequence);
}

void WavePostPersistenceBootMessage::setExecuteConfigReplaySequence (bool executeConfigReplaySequence)
{
    m_executeConfigReplaySequence = executeConfigReplaySequence;
}

bool WavePostPersistenceBootMessage::getExecuteNodeReadySequence () const
{
    return (m_executeNodeReadySequence);
}

void WavePostPersistenceBootMessage::setExecuteNodeReadySequence (bool executeNodeReadySequence)
{
    m_executeNodeReadySequence = executeNodeReadySequence;
}

bool WavePostPersistenceBootMessage::getIsPostbootRequired () const
{
    return (m_isPostbootRequired);
}

void WavePostPersistenceBootMessage::setIsPostbootRequired (bool isPostbootRequired)
{
    m_isPostbootRequired = isPostbootRequired;
}

bool WavePostPersistenceBootMessage::getIsBannerOutputToClientsRequired () const
{
    return (m_isBannerOutputToClientsRequired);
}

void WavePostPersistenceBootMessage::setIsBannerOutputToClientsRequired (bool isBannerOutputToClientsRequired)
{
    m_isBannerOutputToClientsRequired = isBannerOutputToClientsRequired;
}


WavePostPersistenceBootServiceAndWaveSlotsMessage::WavePostPersistenceBootServiceAndWaveSlotsMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POST_PERSISTENT_BOOT_SERVICE_AND_WAVE_SLOTS)
{
}

WavePostPersistenceBootServiceAndWaveSlotsMessage::~WavePostPersistenceBootServiceAndWaveSlotsMessage ()
{
}

void WavePostPersistenceBootServiceAndWaveSlotsMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

}
