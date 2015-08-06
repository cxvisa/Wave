/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/ClusterDeleteContext.h"
#include "Cluster/PrismCluster.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

ClusterDeleteContext::ClusterDeleteContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pPrismCluster             (NULL),
      m_pSecondaryNodes           (NULL)
{
}

ClusterDeleteContext::ClusterDeleteContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_pPrismCluster             (NULL),
      m_pSecondaryNodes           (NULL)
{
}

ClusterDeleteContext::~ClusterDeleteContext ()
{
    if (NULL != m_pPrismCluster)
    {
        delete m_pPrismCluster;
        m_pPrismCluster = NULL;
    }

    if (NULL != m_pSecondaryNodes)
    {
        UI32 numberOfSecondaryNodes = m_pSecondaryNodes->size ();
        UI32 i                      = 0;

        for (i = 0; i < numberOfSecondaryNodes; i++)
        {
            delete (*m_pSecondaryNodes)[i];
        }

        m_pSecondaryNodes->clear ();

        delete m_pSecondaryNodes;
        m_pSecondaryNodes = NULL;
    }
}

PrismCluster *ClusterDeleteContext::getPPrismCluster () const
{
    return (m_pPrismCluster);
}

void ClusterDeleteContext::setPPrismCluster (PrismCluster *pPrismCluster)
{
    m_pPrismCluster = pPrismCluster;
}

vector<WaveManagedObject *> *ClusterDeleteContext::getPSecondaryNodes () const
{
    return (m_pSecondaryNodes);
}

void ClusterDeleteContext::setPSecondaryNodes (vector<WaveManagedObject *> *pSecondaryNodes)
{
    m_pSecondaryNodes = pSecondaryNodes;
}

}
