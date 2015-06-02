/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef TRACECLIENTMAP_H
#define TRACECLIENTMAP_H

#include "Framework/Types/Types.h"
#include "Framework/Trace/TraceTypes.h"
#include "Framework/Utils/PrismMutex.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class TraceClientMap
{
    private :
    protected :
    public :
                      TraceClientMap      ();

        bool          isAKnownClient      (TraceClientId traceClientId);
        bool          isAKnownClient      (const string &traceClientName);
        TraceClientId addClient           (TraceLevel tracelevel, const string &traceClientName);
        void          removeClient        (const string &traceClientName);
        bool          setClientLevel      (TraceClientId traceClientId, TraceLevel tracelevel);
        TraceLevel    getClientLevel      (TraceClientId traceClientId);
        void          getClientsAndLevels (vector<TraceClientId> &traceClientIdsVector, vector<TraceLevel> &traceLevelsVector);
        string        getTraceClientName  (const TraceClientId &traceClientId);

    // Now the data members

    private :
        map<TraceClientId, TraceLevel> m_traceClientsAndLevels;
        map<TraceClientId, string>     m_traceClientsAndNames;
        TraceClientId                  m_nextAvailableTraceClientId;

        PrismMutex                     m_traceClientMapMutex;

    protected :
    public :
};

}

#endif // TRACECLIENTMAP_H
