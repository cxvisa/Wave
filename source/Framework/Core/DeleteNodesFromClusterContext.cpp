/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/DeleteNodesFromClusterContext.h"

namespace WaveNs
{

DeleteNodesFromClusterContext::DeleteNodesFromClusterContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : CreateClusterWithNodesContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps),
      m_isConfigurationChange                (false)
{
}
DeleteNodesFromClusterContext::DeleteNodesFromClusterContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : CreateClusterWithNodesContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps),
      m_isConfigurationChange                (false)
{
}

DeleteNodesFromClusterContext::~DeleteNodesFromClusterContext ()
{
}

void DeleteNodesFromClusterContext::addLocationId (const LocationId &locationId)
{
    addNewLocationId (locationId);
}

void DeleteNodesFromClusterContext::removeLocationId (const LocationId &locationId)
{
    removeNewLocationId (locationId);
}

UI32 DeleteNodesFromClusterContext::getNumberOfLocationIds ()
{
    return (getNumberOfNewLocationIds ());
}

LocationId DeleteNodesFromClusterContext::getLocationIdAt (const UI32 &i)
{
    return (getNewLocationIdAt (i));
}

bool DeleteNodesFromClusterContext::getIsConfigurationChange () const
{
    return m_isConfigurationChange;
}

void DeleteNodesFromClusterContext::setIsConfigurationChange (const bool isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

}
