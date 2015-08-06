/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Core/DeleteNodeOnSecondaryContext.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

DeleteNodeOnSecondaryContext::DeleteNodeOnSecondaryContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_IsStartServiceIsRequired (true)
{
}

DeleteNodeOnSecondaryContext::DeleteNodeOnSecondaryContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_IsStartServiceIsRequired (true)
{
}

DeleteNodeOnSecondaryContext::~DeleteNodeOnSecondaryContext ()
{
}

void DeleteNodeOnSecondaryContext::addKnownLocationId (const LocationId &locationId)
{
    m_KnownLocationIdsVector.push_back (locationId);
}

vector<LocationId> DeleteNodeOnSecondaryContext::getKnownLocationId ()
{
    return (m_KnownLocationIdsVector);
}

bool DeleteNodeOnSecondaryContext::getIsStartServiceIsRequired () const
{
    return (m_IsStartServiceIsRequired);
}

void DeleteNodeOnSecondaryContext::setIsStartServiceIsRequired (const bool &isStartServiceIsRequired)
{
    m_IsStartServiceIsRequired = isStartServiceIsRequired;
}

}
