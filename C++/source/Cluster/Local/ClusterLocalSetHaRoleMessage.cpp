/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                                   *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalSetHaRoleMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/WaveHaNodeTypes.h"

namespace WaveNs
{

ClusterLocalSetHaRoleMessage::ClusterLocalSetHaRoleMessage ()
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SET_HA_ROLE),
      m_haRole                (WAVE_HA_NODE_STANDBY_UNCONFIRMED)
{
}

ClusterLocalSetHaRoleMessage::ClusterLocalSetHaRoleMessage (const UI32 &haRole)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SET_HA_ROLE),
      m_haRole                (haRole)
{
}

ClusterLocalSetHaRoleMessage::~ClusterLocalSetHaRoleMessage ()
{
}

UI32 ClusterLocalSetHaRoleMessage::getHaRole () const
{
    return (m_haRole);
}

void ClusterLocalSetHaRoleMessage::setHaRole (const UI32 &haRole)
{
    m_haRole = haRole;
}

}
