/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Cluster/ClusterRejoinContext.h"

namespace WaveNs
{

ClusterRejoinContext::ClusterRejoinContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps),
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
