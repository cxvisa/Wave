/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/AddExternalNonNativeServiceInstanceContext.h"

namespace WaveNs
{

AddExternalNonNativeServiceInstanceContext::AddExternalNonNativeServiceInstanceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

AddExternalNonNativeServiceInstanceContext::~AddExternalNonNativeServiceInstanceContext ()
{
}

const string &AddExternalNonNativeServiceInstanceContext::getApplicationName () const
{
    return (m_applicationName);
}

void AddExternalNonNativeServiceInstanceContext::setApplicationName (const string &applicationName)
{
    m_applicationName = applicationName;
}

const vector<string> &AddExternalNonNativeServiceInstanceContext::getApplicationInstanceNames () const
{
    return (m_applicationInstanceNames);
}

void AddExternalNonNativeServiceInstanceContext::setApplicationInstanceNames (const vector<string> &applicationInstanceNames)
{
    m_applicationInstanceNames = applicationInstanceNames;
}

const ObjectId &AddExternalNonNativeServiceInstanceContext::getApplicationObjectId () const
{
    return (m_applicationObjectId);
}

void AddExternalNonNativeServiceInstanceContext::setApplicationObjectId (const ObjectId &applicationObjectId)
{
    m_applicationObjectId = applicationObjectId;
}

}
