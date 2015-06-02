/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Sajad Bashir Qadri                                           *
 ***************************************************************************/
#include <sstream>

#include "Framework/Trace/TraceObjectManager.h"
#include "SystemManagement/WaveSystemManagementLogger.h"

#include "WaveResourceIdEnums.h"

namespace WaveNs
{

WaveSystemManagementLogger::WaveSystemManagementLogger(TraceClientId traceClientId)
  : m_traceClientId (traceClientId)
{
}

WaveSystemManagementLogger::WaveSystemManagementLogger(TraceClientId traceClientId, string prefixString)
  : m_traceClientId (traceClientId),
    m_prefixString (prefixString)
{
}

WaveSystemManagementLogger::~WaveSystemManagementLogger()
{
}

/**
 * Log a vector of UI32's, if the current trace level is lower than the specified level.
 */
void WaveSystemManagementLogger::log (const TraceLevel traceLevel, const string label, const vector<UI32>& inputVector)
{
  if (skipGate(traceLevel))
  {
    return;
  }

  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << m_prefixString << label << "[";

  vector<UI32>::const_iterator it = inputVector.begin();
  if (it != inputVector.end())
  {
    ss << *it;
    it++;
  }

  for (; it != inputVector.end(); it++)
  {
    ss << ", " << *it;
  }

  ss << "]";

  traceDirectly (traceLevel, ss.str());
}

/**
 * Log a vector of strings, if the current trace level is lower than the specified level.
 */
void WaveSystemManagementLogger::log (const TraceLevel traceLevel, const string label, const vector<string>& inputVector)
{
  if (skipGate(traceLevel))
  {
    return;
  }

  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << m_prefixString << label << "[";
  vector<string>::const_iterator it = inputVector.begin();

  if (it != inputVector.end())
  {
    ss << *it;
    it++;
  }

  for (; it != inputVector.end(); it++)
  {
    ss << ", " << *it;
  }

  ss << "]";

  traceDirectly (traceLevel, ss.str());
}

/**
 * Log a map of strings, if the current trace level is lower than the specified level.
 */
void WaveSystemManagementLogger::log (const TraceLevel traceLevel, const string label, const map<string, string> input)
{
  if (skipGate(traceLevel))
  {
    return;
  }

  std::stringstream ss (std::stringstream::in | std::stringstream::out);
  ss << m_prefixString << label << "[";

  map<string, string>::const_iterator it = input.begin();
  if (it != input.end())
  {
    ss << it->first << "=" << it->second;
    it++;
  }

  for (; it != input.end(); it++)
  {
    ss << ", " << it->first << "=" << it->second;
  }

  ss << "]";
  traceDirectly(traceLevel, ss.str());
}

/**
 * Log a vector of UI32's, if the current trace level is debug or lower.
 */
void WaveSystemManagementLogger::debug (const string label, const vector<UI32>& inputVector)
{
  log (TRACE_LEVEL_DEBUG, label, inputVector);
}

/**
 * Logs a vector of strings, if the current trace level is debug or lower.
 */
void WaveSystemManagementLogger::debug (const string label, const vector<string>& inputVector)
{
  log (TRACE_LEVEL_DEBUG, label, inputVector);
}

/**
 * Log a map of strings, if the current trace level is debug or lower.
 */
void WaveSystemManagementLogger::debug (const string label, const map<string, string> input)
{
  log (TRACE_LEVEL_DEBUG, label, input);
}

/**
 * Log a simple string, if the current trace level is debug or lower.
 */
void WaveSystemManagementLogger::debug (const string stringToTrace)
{
  traceDirectly (TRACE_LEVEL_DEBUG, stringToTrace);
}

/**
 * Log a simple string, if the current trace level is debug or lower.
 */
void WaveSystemManagementLogger::info (const string stringToTrace)
{
  traceDirectly (TRACE_LEVEL_INFO, stringToTrace);
}

/**
 * Log a simple string, if the current trace level is debug or lower.
 */
void WaveSystemManagementLogger::error (const string stringToTrace)
{
  traceDirectly (TRACE_LEVEL_ERROR, stringToTrace);
}

bool WaveSystemManagementLogger::isDevelEnabled ()
{
  return TraceObjectManager::isTracingRequired(TRACE_LEVEL_DEVEL, m_traceClientId);
}

bool WaveSystemManagementLogger::isDebugEnabled ()
{
  return TraceObjectManager::isTracingRequired(TRACE_LEVEL_DEBUG, m_traceClientId);
}

bool WaveSystemManagementLogger::isInfoEnabled ()
{
  return TraceObjectManager::isTracingRequired(TRACE_LEVEL_INFO, m_traceClientId);
}

/**
 * Return trace client id for this logger.
 */
TraceClientId WaveSystemManagementLogger::getTraceClientId ()
{
  return m_traceClientId;
}

// START: private function definitions

bool WaveSystemManagementLogger::skipGate (const TraceLevel traceLevel) {
  return (! TraceObjectManager::isTracingRequired(traceLevel, m_traceClientId));
}

void WaveSystemManagementLogger::traceDirectly (const TraceLevel traceLevel, const string stringToTrace) {
  TraceObjectManager::traceDirectly (m_traceClientId, traceLevel, stringToTrace, true, false);
}

// END: private function definitions

}
