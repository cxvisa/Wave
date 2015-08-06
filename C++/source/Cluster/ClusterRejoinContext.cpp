/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Cluster/ClusterRejoinContext.h"

namespace WaveNs
{

ClusterRejoinContext::ClusterRejoinContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
    m_isReplaceRejoin             (false)
{
}

ClusterRejoinContext::~ClusterRejoinContext ()
{
}

bool ClusterRejoinContext::getIsReplaceRejoin () const
{
    return (m_isReplaceRejoin);
}

void ClusterRejoinContext::setIsReplaceRejoin (const bool &isReplaceRejoin)
{
    m_isReplaceRejoin = isReplaceRejoin;
}

}
