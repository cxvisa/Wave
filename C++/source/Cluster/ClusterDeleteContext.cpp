/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/ClusterDeleteContext.h"
#include "Cluster/WaveCluster.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

ClusterDeleteContext::ClusterDeleteContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pWaveCluster             (NULL),
      m_pSecondaryNodes           (NULL)
{
}

ClusterDeleteContext::ClusterDeleteContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_pWaveCluster             (NULL),
      m_pSecondaryNodes           (NULL)
{
}

ClusterDeleteContext::~ClusterDeleteContext ()
{
    if (NULL != m_pWaveCluster)
    {
        delete m_pWaveCluster;
        m_pWaveCluster = NULL;
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

WaveCluster *ClusterDeleteContext::getPWaveCluster () const
{
    return (m_pWaveCluster);
}

void ClusterDeleteContext::setPWaveCluster (WaveCluster *pWaveCluster)
{
    m_pWaveCluster = pWaveCluster;
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
