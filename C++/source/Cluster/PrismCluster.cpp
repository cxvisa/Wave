/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/PrismCluster.h"
#include "Cluster/Local/WaveNode.h"

namespace WaveNs
{

PrismCluster::PrismCluster (WaveObjectManager *pWaveObjectManager)
    : WaveElement (pWaveObjectManager),
      PrismPersistableObject (PrismCluster::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager),
      m_primaryLocationId (0),
      m_primaryPort (0)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

PrismCluster::~PrismCluster ()
{
}

string PrismCluster::getClassName ()
{
    return ("PrismCluster");
}

void PrismCluster::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeLocationId                (&m_primaryLocationId, "primaryLocationId"));
    addPersistableAttribute (new AttributeString                    (&m_primaryIpAddress,  "primaryIpAddress"));
    addPersistableAttribute (new AttributeUI32                      (&m_primaryPort,       "primaryPort"));
    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_secondaryNodes,    "secondaryNodes", getClassName (), getObjectId (), WaveNode::getClassName ()));
}

void PrismCluster::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeLocationId                (&m_primaryLocationId, "primaryLocationId"));
    addPersistableAttributeForCreate (new AttributeString                    (&m_primaryIpAddress,  "primaryIpAddress"));
    addPersistableAttributeForCreate (new AttributeUI32                      (&m_primaryPort,       "primaryPort"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_secondaryNodes,    "secondaryNodes", getClassName (), getObjectId (), WaveNode::getClassName ()));
}

LocationId PrismCluster::getPrimaryLocationId () const
{
    return (m_primaryLocationId);
}

void PrismCluster::setPrimaryLocationId (const LocationId &primaryLocationId)
{
    m_primaryLocationId = primaryLocationId;
}

string PrismCluster::getPrimaryIpAddress () const
{
    return (m_primaryIpAddress);
}

void PrismCluster::setPrimaryIpAddress (const string &primaryIpAddress)
{
    m_primaryIpAddress = primaryIpAddress;
}

UI32 PrismCluster::getPrimaryPort () const
{
    return (m_primaryPort);
}

void PrismCluster::setPrimaryPort (const UI32 &primaryPort)
{
    m_primaryPort = primaryPort;
}

void PrismCluster::removeAllSecondryNodes ()
{
    m_secondaryNodes.clear ();
}

bool PrismCluster::isAKnownSecondaryNode  (const ObjectId &secondaryNodeObjectId)
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

void PrismCluster::addSecondaryNode (const ObjectId &secondaryNodeObjectId)
{
    if (true == (isAKnownSecondaryNode(secondaryNodeObjectId)))
    {
        trace (TRACE_LEVEL_FATAL, "PrismCluster::addSecondaryNode : Secondary Node (" + secondaryNodeObjectId.toString () + ") Already exists.");
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        m_secondaryNodes.push_back (secondaryNodeObjectId);
    }
}

void PrismCluster::removeSecondaryNode (const ObjectId &secondaryNodeObjectId)
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
        trace (TRACE_LEVEL_FATAL, "PrismCluster::removeSecondaryNode : Unknown node (" + secondaryNodeObjectId.toString () + ") cannot be removed.");
    }
}

void PrismCluster::setSecondaryNodes (vector<ObjectId> &secondaryNodes)
{
    m_secondaryNodes = secondaryNodes;
}

vector<ObjectId> PrismCluster::getSecondaryNodes () const
{
    return (m_secondaryNodes);
}

}
