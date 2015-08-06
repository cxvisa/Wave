/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TRACETESTCONTEXT_H
#define TRACETESTCONTEXT_H


#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Trace/TraceTypes.h"
#include <vector>

namespace WaveNs
{

class TraceTestContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                               TraceTestContext             (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual               ~TraceTestContext             ();
                void           clearTraceClientsInformation ();
                UI32           getNumberOfTraceClients      ();
                TraceClientId  getTraceClientIdAt           (const UI32 &i);
                TraceLevel     getTraceLevelAt              (const UI32 &i);
                void           addTraceClientInformation    (const TraceClientId &traceClientId, const TraceLevel &traceLevel);

                void           setTraceLevelForAClient      (const TraceLevel &traceLevelForAClient);
                TraceLevel     getTraceLevelForAClient      ();

    // Now the data members

    private :
        vector<TraceClientId> m_traceClientIdsVector;
        vector<TraceLevel>    m_traceLevelsVector;

        TraceLevel            m_traceLevelForAClient;

    protected :
    public :
};

}

#endif // TRACETESTCONTEXT_H
