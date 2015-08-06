/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/DistributedLog/Test/DistributedLogTestContext.h"

namespace WaveNs
{

DistributedLogTestContext::DistributedLogTestContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
    m_originalMaxAllowedLogEntries  (0),
    m_currentMaxAllowedLogEntries   (0),
    m_firstLogId                    (0),
    m_nextLogId                     (0),
    m_waveServiceId              (0),
    m_numberOfFailures              (0)
{
}

DistributedLogTestContext::~DistributedLogTestContext ()
{
}

UI64 DistributedLogTestContext::getOriginalMaxAllowedLogEntries () const
{
    return (m_originalMaxAllowedLogEntries);
}

void DistributedLogTestContext::setOriginalMaxAllowedLogEntries (const UI64 &originalMaxAllowedLogEntries)
{
    m_originalMaxAllowedLogEntries = originalMaxAllowedLogEntries;
}

UI64 DistributedLogTestContext::getCurrentMaxAllowedLogEntries () const
{
    return (m_currentMaxAllowedLogEntries);
}

void DistributedLogTestContext::setCurrentMaxAllowedLogEntries (const UI64 &currentMaxAllowedLogEntries)
{
    m_currentMaxAllowedLogEntries = currentMaxAllowedLogEntries;
}

UI64 DistributedLogTestContext::getFirstLogId () const
{
    return (m_firstLogId);
}

void DistributedLogTestContext::setFirstLogId (const UI64 &firstLogId)
{
    m_firstLogId = firstLogId;
}

UI64 DistributedLogTestContext::getNextLogId () const
{
    return (m_nextLogId);
}

void DistributedLogTestContext::setNextLogId (const UI64 &nextLogId)
{
    m_nextLogId = nextLogId;
}

WaveServiceId DistributedLogTestContext::getWaveServiceId () const
{
    return (m_waveServiceId);
}

void DistributedLogTestContext::setWaveServiceId (const WaveServiceId &prismServiceId)
{
    m_waveServiceId = prismServiceId;
}

ObjectId DistributedLogTestContext::getManagedObjectId () const
{
    return (m_managedObjectId);
}

void DistributedLogTestContext::setManagedObjectId (const ObjectId &managedObjectId)
{
    m_managedObjectId = managedObjectId;
}

UI32 DistributedLogTestContext::getNumberOfFailures () const
{
    return (m_numberOfFailures);
}

void DistributedLogTestContext::setNumberOfFailures (UI32 numberOfFailures)
{
    m_numberOfFailures = numberOfFailures;
}

void DistributedLogTestContext::incrementNumberOfFailures ()
{
    m_numberOfFailures += 1;
}

}
