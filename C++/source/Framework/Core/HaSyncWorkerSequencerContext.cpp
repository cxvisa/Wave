/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Core/HaSyncWorkerSequencerContext.h"

namespace WaveNs
{

StartHaSyncDumpContext::StartHaSyncDumpContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps), 
      m_standbyMessage (NULL), 
      m_haVersion (0),
      m_isDbSyncRequired (false),
      m_isDbResumeRequired (false), 
      m_contextInfo (0),
      m_haPeerIp    (""),
      m_haPeerPort  (0)
{
}

StartHaSyncDumpContext::StartHaSyncDumpContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps), 
      m_standbyMessage (NULL), 
      m_haVersion (0),
      m_isDbSyncRequired (false),
      m_isDbResumeRequired (false), 
      m_contextInfo (0),
      m_haPeerIp    (""),
      m_haPeerPort  (0)
{
}

StartHaSyncDumpContext::~StartHaSyncDumpContext ()
{
}

vector<WaveServiceId> &StartHaSyncDumpContext::getWaveServiceIdsToCommunicate ()
{
    return (m_waveServiceIdsToCommunicate);
}

vector<WaveServiceId> &StartHaSyncDumpContext::getWaveServiceIdsVector ()
{
    return (m_waveServiceIdsVector);
}

void StartHaSyncDumpContext::addValidationDetailsForService (const WaveServiceId &waveServiceId, void *pValidationDetials, const UI32 size)
{
    m_waveServiceIdsVector.push_back        (waveServiceId);
    m_validationDetailsVector.push_back      (pValidationDetials);
    m_validationDetailsSizesVector.push_back (size);
}

vector<void *> &StartHaSyncDumpContext::getValidationDetailsVector ()
{
    return (m_validationDetailsVector);
}

vector<UI32> &StartHaSyncDumpContext::getValidationDetailsSizesVector ()
{
    return (m_validationDetailsSizesVector);
}

void StartHaSyncDumpContext::addValidationResultsForService (const WaveServiceId &waveServiceId, void *const &pValidationResults, const UI32 &validationResultsSize)
{
    string uniqueIdString = string ("service ") + waveServiceId;
    m_validationResultsVector[uniqueIdString]      = pValidationResults;
    m_validationResultsSizesVector[uniqueIdString] = validationResultsSize;
}

void StartHaSyncDumpContext::getValidationResultsForService (const WaveServiceId &waveServiceId, void *&pValidationResults, UI32 &validationResultsSize)
{
    string uniqueIdString = string ("service ") + waveServiceId;

    pValidationResults    = NULL;
    validationResultsSize = 0;

    map<string, void *>::iterator validationResultsElement = m_validationResultsVector.find (uniqueIdString);
    map<string, void *>::iterator validationResultsEnd     = m_validationResultsVector.end ();

    if (validationResultsElement != validationResultsEnd)
    {
        pValidationResults = validationResultsElement->second;
    }
    else
    {
        return;
    }

    map<string, UI32>::iterator validationResultsSizeElement = m_validationResultsSizesVector.find (uniqueIdString);
    map<string, UI32>::iterator validationResultsSizeEnd     = m_validationResultsSizesVector.end ();

    if (validationResultsSizeElement != validationResultsSizeEnd)
    {
        validationResultsSize = validationResultsSizeElement->second;
    }
    else
    {
        // We found the validation results but could not find the size of the validation results.  This must not happen.
        waveAssert (false, __FILE__, __LINE__);
    }
}

void StartHaSyncDumpContext::setStandbyMessage (WaveMessage *standbyMessage)
{
    m_standbyMessage = standbyMessage;
}

WaveMessage * StartHaSyncDumpContext::getStandbyMessage () 
{
    return m_standbyMessage;
}

void StartHaSyncDumpContext::setHaVersion (const UI32 &haVersion)
{
    m_haVersion = haVersion;
}

UI32 StartHaSyncDumpContext::getHaVersion () 
{
    return m_haVersion;
}

void StartHaSyncDumpContext::setIsDbSyncRequired (const bool &isDbSyncRequired)
{
    m_isDbSyncRequired = isDbSyncRequired;
}

bool StartHaSyncDumpContext::getIsDbSyncRequired ()
{
    return (m_isDbSyncRequired);
}

void StartHaSyncDumpContext::setIsDbResumeRequired (const bool &isDbResumeRequired)
{
    m_isDbResumeRequired = isDbResumeRequired;
}

bool StartHaSyncDumpContext::getIsDbResumeRequired ()
{
    return (m_isDbResumeRequired);
}

UI32 StartHaSyncDumpContext::getContextInfo ()
{
      return (m_contextInfo);
}

void StartHaSyncDumpContext::setContextInfo (const UI32 &contextInfo)
{
    m_contextInfo = contextInfo;
}

void StartHaSyncDumpContext::setHaPeerIp (const string& ip)
{
    m_haPeerIp = ip;
}
    
string StartHaSyncDumpContext::getHaPeerIp () const
{
    return (m_haPeerIp);
}

void StartHaSyncDumpContext::setHaPeerPort (const SI32& port)
{
    m_haPeerPort = port;
}

SI32 StartHaSyncDumpContext::getHaPeerPort () const
{
    return (m_haPeerPort);
}


ReceiveHaSyncDumpContext::ReceiveHaSyncDumpContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_isDbSyncRequired (false),
      m_contextInfo (0)
{
}

ReceiveHaSyncDumpContext::ReceiveHaSyncDumpContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement,WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_isDbSyncRequired (false),
      m_contextInfo (0)
{
}

ReceiveHaSyncDumpContext::~ReceiveHaSyncDumpContext ()
{
}

void ReceiveHaSyncDumpContext::setIsDbSyncRequired (const bool &isDbSyncRequired)
{
    m_isDbSyncRequired = isDbSyncRequired;
}

bool ReceiveHaSyncDumpContext::getIsDbSyncRequired ()
{
    return (m_isDbSyncRequired);
}

UI32 ReceiveHaSyncDumpContext::getContextInfo ()
{
      return (m_contextInfo);
}

void ReceiveHaSyncDumpContext::setContextInfo (const UI32 &contextInfo)
{
    m_contextInfo = contextInfo;
}

void ReceiveHaSyncDumpContext::setHaPeerPort (const SI32& port)
{
    m_haPeerPort = port;
}

SI32 ReceiveHaSyncDumpContext::getHaPeerPort () const
{
    return (m_haPeerPort);
}

void ReceiveHaSyncDumpContext::setHaPeerIp (const string& ip)
{       
    m_haPeerIp = ip;
}       
    
string ReceiveHaSyncDumpContext::getHaPeerIp () const
{   
    return (m_haPeerIp);
}   

}
