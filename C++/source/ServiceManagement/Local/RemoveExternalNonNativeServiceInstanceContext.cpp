/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Local/RemoveExternalNonNativeServiceInstanceContext.h"

namespace WaveNs
{

RemoveExternalNonNativeServiceInstanceContext::RemoveExternalNonNativeServiceInstanceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

RemoveExternalNonNativeServiceInstanceContext::~RemoveExternalNonNativeServiceInstanceContext ()
{
}

const string &RemoveExternalNonNativeServiceInstanceContext::getApplicationName () const
{
    return (m_applicationName);
}

void RemoveExternalNonNativeServiceInstanceContext::setApplicationName (const string &applicationName)
{
    m_applicationName = applicationName;
}

const vector<string> &RemoveExternalNonNativeServiceInstanceContext::getApplicationInstanceNames () const
{
    return (m_applicationInstanceNames);
}

void RemoveExternalNonNativeServiceInstanceContext::setApplicationInstanceNames (const vector<string> &applicationInstanceNames)
{
    m_applicationInstanceNames = applicationInstanceNames;
}

const ObjectId &RemoveExternalNonNativeServiceInstanceContext::getApplicationObjectId () const
{
    return (m_applicationObjectId);
}

void RemoveExternalNonNativeServiceInstanceContext::setApplicationObjectId (const ObjectId &applicationObjectId)
{
    m_applicationObjectId = applicationObjectId;
}

}
