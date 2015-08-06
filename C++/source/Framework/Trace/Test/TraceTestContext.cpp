/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Trace/Test/TraceTestContext.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

TraceTestContext::TraceTestContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
    m_traceLevelForAClient (TRACE_LEVEL_INFO)
{
}

TraceTestContext::~TraceTestContext ()
{
}

void TraceTestContext::clearTraceClientsInformation ()
{
    m_traceClientIdsVector.clear ();
    m_traceLevelsVector.clear ();
}

UI32 TraceTestContext::getNumberOfTraceClients ()
{
    UI32 numberOfClientIds = m_traceClientIdsVector.size ();
    UI32 numberOfLevels    = m_traceLevelsVector.size ();

    prismAssert (numberOfClientIds == numberOfLevels, __FILE__, __LINE__);

    return (numberOfClientIds);
}

TraceClientId TraceTestContext::getTraceClientIdAt (const UI32 &i)
{
    UI32 numberOfTraceClients = getNumberOfTraceClients ();

    prismAssert (i < numberOfTraceClients, __FILE__, __LINE__);

    return (m_traceClientIdsVector[i]);
}

TraceLevel TraceTestContext::getTraceLevelAt (const UI32 &i)
{
    UI32 numberOfTraceClients = getNumberOfTraceClients ();

    prismAssert (i < numberOfTraceClients, __FILE__, __LINE__);

    return (m_traceLevelsVector[i]);
}

void TraceTestContext::addTraceClientInformation (const TraceClientId &traceClientId, const TraceLevel &traceLevel)
{
    m_traceClientIdsVector.push_back (traceClientId);
    m_traceLevelsVector.push_back (traceLevel);
}

void TraceTestContext::setTraceLevelForAClient (const TraceLevel &traceLevelForAClient)
{
    m_traceLevelForAClient = traceLevelForAClient;
}

TraceLevel TraceTestContext::getTraceLevelForAClient ()
{
    return (m_traceLevelForAClient);
}

}
