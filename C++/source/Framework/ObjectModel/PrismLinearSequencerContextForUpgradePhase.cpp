/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/PrismLinearSequencerContextForUpgradePhase.h"

namespace WaveNs
{

PrismLinearSequencerContextForUpgradePhase::PrismLinearSequencerContextForUpgradePhase (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
{
    m_schemaChangeInfo = NULL;    
}

PrismLinearSequencerContextForUpgradePhase::~PrismLinearSequencerContextForUpgradePhase ()
{
    if (m_schemaChangeInfo)
    {
        delete (m_schemaChangeInfo);
    }
}

OMSpecificSchemaChangeInfoForUpgrade* PrismLinearSequencerContextForUpgradePhase::getSchemaChangeInfo () const
{
    return (m_schemaChangeInfo);
}  

void PrismLinearSequencerContextForUpgradePhase::setSchemaChangeInfo (OMSpecificSchemaChangeInfoForUpgrade* pSchemaChangeInfo)
{
    m_schemaChangeInfo = pSchemaChangeInfo;
}

/*
vector<string> PrismLinearSequencerContextForUpgradePhase::getNewManagedObjects () const
{
    return (m_newManagedObjects);
}

void PrismLinearSequencerContextForUpgradePhase::setNewManagedObjects (const vector<string> &newManagedObjects)
{
    m_newManagedObjects = newManagedObjects;
}

vector<string> PrismLinearSequencerContextForUpgradePhase::getChangedManagedObjects () const
{
    return (m_changedManagedObjects);
}

void PrismLinearSequencerContextForUpgradePhase::setChangedManagedObjects (const vector<string> &changedManagedObjects)
{
    m_changedManagedObjects = changedManagedObjects;
}
*/
}
