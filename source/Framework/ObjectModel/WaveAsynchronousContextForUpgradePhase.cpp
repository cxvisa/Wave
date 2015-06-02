/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForUpgradePhase.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

FirmwareVersion::FirmwareVersion ()
{

}

FirmwareVersion::FirmwareVersion (const string &majorNumber, const string &minorNumber, const string &patchString, const string &description)
    :   m_majorNumber (majorNumber),
        m_minorNumber (minorNumber),
        m_patchString (patchString),
        m_description (description)
{

}

FirmwareVersion::~FirmwareVersion ()
{

}

bool FirmwareVersion::isSameVersion (const string &versionString)
{
    return (false);
}

WaveAsynchronousContextForUpgradePhase::WaveAsynchronousContextForUpgradePhase (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContextForBootPhases (pCaller, pCallback, pCallerContext)
{
}

WaveAsynchronousContextForUpgradePhase::~WaveAsynchronousContextForUpgradePhase ()
{
}

/*
vector<string> WaveAsynchronousContextForUpgradePhase::getNewManagedObjects () const
{
    return (m_newManagedObjects);
}

void WaveAsynchronousContextForUpgradePhase::setNewManagedObjects (const vector<string> &newManagedObjects)
{
    m_newManagedObjects = newManagedObjects;
}

vector<string> WaveAsynchronousContextForUpgradePhase::getChangedManagedObjects () const
{
    return (m_changedManagedObjects);
}

void WaveAsynchronousContextForUpgradePhase::setChangedManagedObjects (const vector<string> &changedManagedObjects)
{
    m_changedManagedObjects = changedManagedObjects;
}

bool WaveAsynchronousContextForUpgradePhase::checkFromVersionString (const string &versionString)
{
    return (m_fromVersion.isSameVersion (versionString));
}
*/

OMSpecificSchemaChangeInfoForUpgrade* WaveAsynchronousContextForUpgradePhase::getSchemaChangeInfo () const
{                          
    return (m_schemaChangeInfo);
}

void WaveAsynchronousContextForUpgradePhase::setSchemaChangeInfo (OMSpecificSchemaChangeInfoForUpgrade* pSchemaChangeInfo)
{   
    m_schemaChangeInfo = pSchemaChangeInfo;
}

bool WaveAsynchronousContextForUpgradePhase::checkToVersionString (const string &versionString)
{
    return (m_toVersion.isSameVersion (versionString));
}


}
