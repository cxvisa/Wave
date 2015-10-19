/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveLinearSequencerContextForUpgradePhase.h"

namespace WaveNs
{

WaveLinearSequencerContextForUpgradePhase::WaveLinearSequencerContextForUpgradePhase (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
    m_schemaChangeInfo = NULL;    
}

WaveLinearSequencerContextForUpgradePhase::~WaveLinearSequencerContextForUpgradePhase ()
{
    if (m_schemaChangeInfo)
    {
        delete (m_schemaChangeInfo);
    }
}

OMSpecificSchemaChangeInfoForUpgrade* WaveLinearSequencerContextForUpgradePhase::getSchemaChangeInfo () const
{
    return (m_schemaChangeInfo);
}  

void WaveLinearSequencerContextForUpgradePhase::setSchemaChangeInfo (OMSpecificSchemaChangeInfoForUpgrade* pSchemaChangeInfo)
{
    m_schemaChangeInfo = pSchemaChangeInfo;
}

/*
vector<string> WaveLinearSequencerContextForUpgradePhase::getNewManagedObjects () const
{
    return (m_newManagedObjects);
}

void WaveLinearSequencerContextForUpgradePhase::setNewManagedObjects (const vector<string> &newManagedObjects)
{
    m_newManagedObjects = newManagedObjects;
}

vector<string> WaveLinearSequencerContextForUpgradePhase::getChangedManagedObjects () const
{
    return (m_changedManagedObjects);
}

void WaveLinearSequencerContextForUpgradePhase::setChangedManagedObjects (const vector<string> &changedManagedObjects)
{
    m_changedManagedObjects = changedManagedObjects;
}
*/
}
