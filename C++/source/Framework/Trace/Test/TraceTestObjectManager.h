/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TRACETESTOBJECTMANAGER_H
#define TRACETESTOBJECTMANAGER_H

#include "Framework/Trace/Test/TraceTestContext.h"
#include "Regression/WaveTestObjectManager.h"

namespace WaveNs
{

class TraceTestObjectManager : public WaveTestObjectManager
{
    private :
             TraceTestObjectManager             ();

        void testRequestHandler                 (RegressionTestMessage *pMessage);
        void clearTraceClientsInformationStep   (TraceTestContext *pTraceTestContext);
        void getTraceClientsInformationStep     (TraceTestContext *pTraceTestContext);
        void displayTraceClientsInformationStep (TraceTestContext *pTraceTestContext);
        void getTraceClientTraceLevelStep       (TraceTestContext *pTraceTestContext);
        void setTraceClientTraceLevelStep       (TraceTestContext *pTraceTestContext);
        void resetTraceClientTraceLevelStep     (TraceTestContext *pTraceTestContext);

    protected :
    public :
        virtual                       ~TraceTestObjectManager ();
        static TraceTestObjectManager *getInstance            ();
        static WaveServiceId          getWaveServiceId      ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // TRACETESTOBJECTMANAGER_H
