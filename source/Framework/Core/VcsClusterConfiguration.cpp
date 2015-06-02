/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#include "Framework/Core/VcsClusterConfiguration.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"

using namespace std;

namespace WaveNs
{

VcsClusterConfiguration::VcsClusterConfiguration ()
    : SerializableObject (),
      m_version (0),
      m_vcsMode (false),
      m_vcsId (0),
      m_rbridgeId (0),
      m_clusterType (0),
      m_clusterConf (0)
{
}

VcsClusterConfiguration::~VcsClusterConfiguration ()
{
}

void VcsClusterConfiguration::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeUI32 (&m_version,        "version"));
    addSerializableAttribute (new AttributeBool (&m_vcsMode,        "vcsMode"));
    addSerializableAttribute (new AttributeUI32 (&m_vcsId,          "vcsId"));
    addSerializableAttribute (new AttributeUI32 (&m_rbridgeId,      "rbridgeId"));
    addSerializableAttribute (new AttributeUI32 (&m_clusterType,    "clusterType"));
    addSerializableAttribute (new AttributeSI32 (&m_clusterConf,    "clusterConf"));
}

void VcsClusterConfiguration::setupAttributesForSerializationInAttributeOrderFormat ()
{
    SerializableObject::setupAttributesForSerializationInAttributeOrderFormat ();

    addAttributeNameForOrderToNameMapping ("version");
    addAttributeNameForOrderToNameMapping ("vcsMode");
    addAttributeNameForOrderToNameMapping ("vcsId");
    addAttributeNameForOrderToNameMapping ("rbridgeId");
    addAttributeNameForOrderToNameMapping ("clusterType");
    addAttributeNameForOrderToNameMapping ("clusterConf");
}


void VcsClusterConfiguration::display () const
{
    trace (TRACE_LEVEL_INFO, string ("___________________________________________________"));

    trace (TRACE_LEVEL_INFO, string ("Version       : ") + m_version);
    trace (TRACE_LEVEL_INFO, string ("Vcs Mode      : ") + m_vcsMode);
    trace (TRACE_LEVEL_INFO, string ("Vcs Id        : ") + m_vcsId);

    trace (TRACE_LEVEL_INFO, string ("Rbridge Id    : ") + m_rbridgeId);

    trace (TRACE_LEVEL_INFO, string ("Cluster Type  : ") + m_clusterType);
    trace (TRACE_LEVEL_INFO, string ("Cluster Conf  : ") + m_clusterConf);

    trace (TRACE_LEVEL_INFO, string ("___________________________________________________"));
}

UI32 VcsClusterConfiguration::getVersion () const
{
    return (m_version);
}

void VcsClusterConfiguration::setVersion (const UI32 &version)
{
    m_version = version;
}

bool VcsClusterConfiguration::getVcsMode () const
{
    return (m_vcsMode);
}

void VcsClusterConfiguration::setVcsMode (const bool &vcsMode)
{
    m_vcsMode = vcsMode;
}

UI32 VcsClusterConfiguration::getVcsId () const
{
    return (m_vcsId);
}

void VcsClusterConfiguration::setVcsId (const UI32 &vcsId)
{
    m_vcsId = vcsId;
}

UI32 VcsClusterConfiguration::getRbridgeId () const
{
    return (m_rbridgeId);
}

void VcsClusterConfiguration::setRbridgeId (const UI32 &rbridgeId)
{
    m_rbridgeId = rbridgeId;
}

UI32 VcsClusterConfiguration::getClusterType () const
{
    return (m_clusterType);
}

void VcsClusterConfiguration::setClusterType (const UI32 &clusterType)
{
    m_clusterType = clusterType;
}

SI32 VcsClusterConfiguration::getClusterConf () const
{
    return (m_clusterConf);
}

void VcsClusterConfiguration::setClusterConf (const SI32 &clusterConf)
{
    m_clusterConf = clusterConf;
}

}
