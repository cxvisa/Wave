/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#include "Framework/CliBlockManagement/CliBlockMessage.h"
#include "Framework/CliBlockManagement/CliBlockDetail.h"
#include "Framework/CliBlockManagement/CliBlockType.h"
#include "Framework/Attributes/Attributes.h" 
#include "Framework/Attributes/AttributeResourceId.h"
#include "Cluster/CentralClusterConfigObjectManager.h"

namespace WaveNs
{

CliBlockMessage::CliBlockMessage (bool operation, const CliBlockDetail &cliBlockDetail)
    : WaveMessage (CentralClusterConfigObjectManager::getWaveServiceId (), CLI_BLOCK)
{
    m_operation         = operation;
    m_reason            = (cliBlockDetail.getCliBlockContext ()).getReason ();
    m_originator        = cliBlockDetail.getOriginator ();
    m_waveServiceId    = cliBlockDetail.getWaveServiceId ();
}

CliBlockMessage::CliBlockMessage ()
    : WaveMessage (CentralClusterConfigObjectManager::getWaveServiceId (), CLI_BLOCK)
{
    m_operation      = true;
    m_reason         = WAVE_FRAMEWORK_STATE_UNKNOWN_STATE;
    m_originator     = 0;
    m_waveServiceId = 0;
}

CliBlockMessage::~CliBlockMessage ()
{
}

void CliBlockMessage::setupAttributesForSerialization ()
{

    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_operation, "operation"));
    addSerializableAttribute (new AttributeResourceId (&m_reason, "reason"));
    addSerializableAttribute (new AttributeLocationId (&m_originator, "originator"));
    addSerializableAttribute (new AttributeUI32 (&m_waveServiceId, "waveServiceId"));

}

const ResourceId CliBlockMessage::getReason () const
{
    return (m_reason);
}

const bool CliBlockMessage::getOperation () const
{
    return (m_operation);
}

const LocationId CliBlockMessage::getOriginator () const
{
    return (m_originator);
}

const WaveServiceId CliBlockMessage::getWaveServiceId () const
{
    return (m_waveServiceId);
}

}
