/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/WaveCluster.h"
#include "Cluster/Local/WaveNode.h"

namespace WaveNs
{

WaveCluster::WaveCluster (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      WavePersistableObject (WaveCluster::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_primaryLocationId (0),
      m_primaryPort (0)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

WaveCluster::~WaveCluster ()
{
}

string WaveCluster::getClassName ()
{
    return ("WaveCluster");
}

void WaveCluster::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeLocationId                (&m_primaryLocationId, "primaryLocationId"));
    addPersistableAttribute (new AttributeString                    (&m_primaryIpAddress,  "primaryIpAddress"));
    addPersistableAttribute (new AttributeUI32                      (&m_primaryPort,       "primaryPort"));
    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_secondaryNodes,    "secondaryNodes", getClassName (), getObjectId (), WaveNode::getClassName ()));
}

void WaveCluster::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeLocationId                (&m_primaryLocationId, "primaryLocationId"));
    addPersistableAttributeForCreate (new AttributeString                    (&m_primaryIpAddress,  "primaryIpAddress"));
    addPersistableAttributeForCreate (new AttributeUI32                      (&m_primaryPort,       "primaryPort"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_secondaryNodes,    "secondaryNodes", getClassName (), getObjectId (), WaveNode::getClassName ()));
}

LocationId WaveCluster::getPrimaryLocationId () const
{
    return (m_primaryLocationId);
}

void WaveCluster::setPrimaryLocationId (const LocationId &primaryLocationId)
{
    m_primaryLocationId = primaryLocationId;
}

string WaveCluster::getPrimaryIpAddress () const
{
    return (m_primaryIpAddress);
}

void WaveCluster::setPrimaryIpAddress (const string &primaryIpAddress)
{
    m_primaryIpAddress = primaryIpAddress;
}

UI32 WaveCluster::getPrimaryPort () const
{
    return (m_primaryPort);
}

void WaveCluster::setPrimaryPort (const UI32 &primaryPort)
{
    m_primaryPort = primaryPort;
}

void WaveCluster::removeAllSecondryNodes ()
{
    m_secondaryNodes.clear ();
}

bool WaveCluster::isAKnownSecondaryNode  (const ObjectId &secondaryNodeObjectId)
{
    vector<ObjectId>::iterator element    = m_secondaryNodes.begin ();
    vector<ObjectId>::iterator endElement = m_secondaryNodes.end ();

    while (element != endElement)
    {
        if (secondaryNodeObjectId == (*element))
        {
            return (true);
        }

        element++;
    }

    return (false);
}

void WaveCluster::addSecondaryNode (const ObjectId &secondaryNodeObjectId)
{
    if (true == (isAKnownSecondaryNode(secondaryNodeObjectId)))
    {
        trace (TRACE_LEVEL_FATAL, "WaveCluster::addSecondaryNode : Secondary Node (" + secondaryNodeObjectId.toString () + ") Already exists.");
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        m_secondaryNodes.push_back (secondaryNodeObjectId);
    }
}

void WaveCluster::removeSecondaryNode (const ObjectId &secondaryNodeObjectId)
{
    vector<ObjectId>::iterator element    = m_secondaryNodes.begin ();
    vector<ObjectId>::iterator endElement = m_secondaryNodes.end ();
    bool                       nodeFound  = false;

    while (element != endElement)
    {
        if (secondaryNodeObjectId == (*element))
        {
            nodeFound = true;
            break;
        }

        element++;
    }

    if (true == nodeFound)
    {
        m_secondaryNodes.erase (element);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "WaveCluster::removeSecondaryNode : Unknown node (" + secondaryNodeObjectId.toString () + ") cannot be removed.");
    }
}

void WaveCluster::setSecondaryNodes (vector<ObjectId> &secondaryNodes)
{
    m_secondaryNodes = secondaryNodes;
}

vector<ObjectId> WaveCluster::getSecondaryNodes () const
{
    return (m_secondaryNodes);
}

}
