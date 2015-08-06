/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#include "Framework/CliBlockManagement/CliBlockServiceIndependentMessage.h"
#include "Framework/CliBlockManagement/CliBlockMessage.h"
#include "Framework/CliBlockManagement/CliBlockType.h"
#include "Framework/Attributes/Attributes.h" 
#include "Framework/Attributes/AttributeResourceId.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{

CliBlockServiceIndependentMessage::CliBlockServiceIndependentMessage (const CliBlockMessage &cliBlockMessage)
    : WaveServiceIndependentMessage (ClusterLocalObjectManager::getWaveServiceId (), CLI_BLOCK_SERVICE_INDEPENDENT)
{

    m_operation         = cliBlockMessage.getOperation            ();
    m_reason            = cliBlockMessage.getReason               ();
    m_originator        = cliBlockMessage.getOriginator           ();
    m_waveServiceId    = cliBlockMessage.getWaveServiceId       ();

}

CliBlockServiceIndependentMessage::CliBlockServiceIndependentMessage ()
    : WaveServiceIndependentMessage (ClusterLocalObjectManager::getWaveServiceId (), CLI_BLOCK_SERVICE_INDEPENDENT)
{
    m_operation      = true;
    m_reason         = WAVE_FRAMEWORK_STATE_UNKNOWN_STATE;
    m_originator     = 0;
    m_waveServiceId = 0;
}

CliBlockServiceIndependentMessage::~CliBlockServiceIndependentMessage ()
{
}

void CliBlockServiceIndependentMessage::setupAttributesForSerialization ()
{

    WaveServiceIndependentMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_operation, "operation"));
    addSerializableAttribute (new AttributeResourceId (&m_reason, "reason"));
    addSerializableAttribute (new AttributeLocationId (&m_originator, "originator"));
    addSerializableAttribute (new AttributeUI32 (&m_waveServiceId, "prismServiceId"));

}

const ResourceId CliBlockServiceIndependentMessage::getReason () const
{
    return (m_reason);
}

const bool CliBlockServiceIndependentMessage::getOperation () const
{
    return (m_operation);
}

const LocationId CliBlockServiceIndependentMessage::getOriginator () const
{
    return (m_originator);
}

const WaveServiceId CliBlockServiceIndependentMessage::getWaveServiceId () const
{
    return (m_waveServiceId);
}

}
