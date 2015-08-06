/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveObjectManagerCommitTransactionContext.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"

namespace WaveNs
{

WaveObjectManagerCommitTransactionContext::WaveObjectManagerCommitTransactionContext () :
    m_isADelayedCommitTransaction (false)
{
}

WaveObjectManagerCommitTransactionContext::WaveObjectManagerCommitTransactionContext (WaveLinearSequencerContext *pWaveLinearSequencerContext) :
    m_isADelayedCommitTransaction (pWaveLinearSequencerContext->getIsADelayedCommitTransaction ())
{
}

WaveObjectManagerCommitTransactionContext::WaveObjectManagerCommitTransactionContext (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext) :
    m_isADelayedCommitTransaction (pPrismSynchronousLinearSequencerContext->getIsADelayedCommitTransaction ())
{
}

WaveObjectManagerCommitTransactionContext::~WaveObjectManagerCommitTransactionContext ()
{
}

bool WaveObjectManagerCommitTransactionContext::getIsADelayedCommitTransaction () const
{
    return (m_isADelayedCommitTransaction);
}

void WaveObjectManagerCommitTransactionContext::setIsADelayedCommitTransaction (const bool &isADelayedCommitTransaction)
{
    m_isADelayedCommitTransaction = isADelayedCommitTransaction;
}

}
