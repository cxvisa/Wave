/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Sajad Bashir Qadri                                           *
 ***************************************************************************/

#ifndef WAVE_SYSTEM_MANAGEMENT_LOGGER_H_
#define WAVE_SYSTEM_MANAGEMENT_LOGGER_H_

#include <string>
#include <map>
#include <vector>

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveSystemManagementLogger
{
  public:
                      WaveSystemManagementLogger  (TraceClientId traceClientId);
                      WaveSystemManagementLogger  (TraceClientId traceClientId, string prefixString);

    virtual           ~WaveSystemManagementLogger ();

            void      log     (const TraceLevel traceLevel, const string label, const vector<string>& attributeUserTags);
            void      log     (const TraceLevel traceLevel, const string label, const vector<UI32>& attributeUserTags);
            void      log     (const TraceLevel traceLevel, const string label, const map<string, string> input);

            void      debug   (const string label, const vector<string>& attributeUserTags);
            void      debug   (const string label, const vector<UI32>& attributeUserTags);
            void      debug   (const string label, const map<string, string> input);

            void      debug   (const string stringToTrace);
            void      info    (const string stringToTrace);
            void      error   (const string stringToTrace);

            bool      isDevelEnabled    ();
            bool      isDebugEnabled    ();
            bool      isInfoEnabled     ();

            TraceClientId     getTraceClientId();

  protected:
  private:
            bool      skipGate        (const TraceLevel traceLevel);
            void      traceDirectly   (const TraceLevel traceLevel, const string stringToTrace);

  // Member variable now
  private:
    TraceClientId           m_traceClientId;
    string                  m_prefixString;
};

}

#endif /* WAVE_SYSTEM_MANAGEMENT_LOGGER_H_ */
