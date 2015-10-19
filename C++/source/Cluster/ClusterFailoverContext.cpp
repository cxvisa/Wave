/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/ClusterFailoverContext.h"
#include "Cluster/WaveCluster.h"
#include "Cluster/NodeManagedObject.h"
#include "Cluster/Local/WaveNode.h"

namespace WaveNs
{

ClusterFailoverContext::ClusterFailoverContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const FrameworkObjectManagerFailoverReason &failoverReason, const vector<LocationId> &failedLocationIds)
    : WaveSynchronousLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_failoverReason (failoverReason),
      m_failedLocationIds (failedLocationIds),
      m_pWaveCluster       (NULL),
      m_pNodeManagedObjects (NULL),
      m_isPrimaryChanged    (false),
      m_isClusterExists     (true),
      m_pThisWaveNode       (NULL)
{
}

ClusterFailoverContext::ClusterFailoverContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const FrameworkObjectManagerFailoverReason &failoverReason, const vector<LocationId> &failedLocationIds)
    : WaveSynchronousLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_failoverReason (failoverReason),
      m_failedLocationIds (failedLocationIds),
      m_pWaveCluster       (NULL),
      m_pNodeManagedObjects (NULL),
      m_isPrimaryChanged    (false),
      m_isClusterExists     (true),
      m_pThisWaveNode       (NULL)
{
}

ClusterFailoverContext::~ClusterFailoverContext ()
{
    if (NULL != m_pWaveCluster)
    {
        delete m_pWaveCluster;
            m_pWaveCluster = NULL;
    }

    if (NULL != m_pNodeManagedObjects)
    {
        UI32 numberOfNodeManagedObjects = m_pNodeManagedObjects->size ();
        UI32 i                          = 0;

        for (i = 0; i < numberOfNodeManagedObjects; i++)
        {
            delete ((*m_pNodeManagedObjects)[i]);
        }

        m_pNodeManagedObjects->clear ();
        delete m_pNodeManagedObjects;
        m_pNodeManagedObjects = NULL;
    }
}

FrameworkObjectManagerFailoverReason ClusterFailoverContext::getFailoverReason () const
{
    return (m_failoverReason);
}

vector<LocationId> &ClusterFailoverContext::getFailedLocationIds ()
{
    return (m_failedLocationIds);
}

WaveCluster *ClusterFailoverContext::getPWaveCluster ()
{
    return (m_pWaveCluster);
}

void ClusterFailoverContext::setPWaveCluster (WaveCluster *pWaveCluster)
{
    m_pWaveCluster = pWaveCluster;
}

vector<WaveManagedObject *> *ClusterFailoverContext::getPNodeManagedObjects ()
{
    return (m_pNodeManagedObjects);
}

void ClusterFailoverContext::setPNodeManagedObjects (vector<WaveManagedObject *> *pNodeManagedObjects)
{
    m_pNodeManagedObjects = pNodeManagedObjects;
}

bool ClusterFailoverContext::getIsPrimaryChanged () const
{
    return (m_isPrimaryChanged);
}

void ClusterFailoverContext::setIsPrimaryChanged (const bool &isPrimaryChanged)
{
    m_isPrimaryChanged = isPrimaryChanged;
}

bool ClusterFailoverContext::isAFailedLocationId (const LocationId &locationId)
{
    UI32 numberOfFailedLocationIds = m_failedLocationIds.size ();
    UI32 i                         = 0;

    for (i = 0; i < numberOfFailedLocationIds; i++)
    {
        if (locationId == m_failedLocationIds[i])
        {
            return (true);
        }
    }

    return (false);
}

bool ClusterFailoverContext::getIsClusterExists () const
{
    return (m_isClusterExists);
}

void ClusterFailoverContext::setIsClusterExists (const bool &isClusterExists)
{
    m_isClusterExists = isClusterExists;
}

WaveNode *ClusterFailoverContext::getThisWaveNode () const
{
    return (m_pThisWaveNode);
}

void ClusterFailoverContext::setThisWaveNode (WaveNode *pWaveNode)
{
    m_pThisWaveNode = pWaveNode;
}

}
