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

DeleteNodeOnSecondaryContext::DeleteNodeOnSecondaryContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pWaveMessage, pPrismElement, pSteps, numberOfSteps),
      m_IsStartServiceIsRequired (true)
{
}

DeleteNodeOnSecondaryContext::DeleteNodeOnSecondaryContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps),
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
