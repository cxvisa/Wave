/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/Test/WaveNativeTest1Service.h"
#include "Framework/ServiceInterface/Test/WaveNativeTest1ServiceMessages.h"

namespace WaveNs
{

WaveNativeTest1Service::WaveNativeTest1Service ()
    : WaveObjectManager ("WaveNativeTest1Service")
{
   addOperationMap (WAVE_NATIVE_TEST1_SERVICE_MESSAGE1, reinterpret_cast<WaveMessageHandler> (&WaveNativeTest1Service::prismNativeTest1ServiceMessage1Handler));
}

WaveNativeTest1Service::~WaveNativeTest1Service ()
{
}

WaveNativeTest1Service *WaveNativeTest1Service::getInstance ()
{
    static WaveNativeTest1Service *pWaveNativeTest1Service = NULL;

    if (NULL == pWaveNativeTest1Service)
    {
        pWaveNativeTest1Service = new WaveNativeTest1Service ();
        WaveNs::waveAssert (NULL != pWaveNativeTest1Service, __FILE__, __LINE__);
    }

    return (pWaveNativeTest1Service);
}

WaveServiceId WaveNativeTest1Service::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void WaveNativeTest1Service::prismNativeTest1ServiceMessage1Handler (WaveNativeTest1ServiceMessage1 *pMsg)
{
    trace (TRACE_LEVEL_DEVEL , "Wave Native Test1 Messge Received");

    static UI32 numberOfReceivedMessagesSoFar = 0;

    numberOfReceivedMessagesSoFar++;

    if (0 == (numberOfReceivedMessagesSoFar % 1000))
    {
        cout << "WaveNativeTest1Service::prismNativeTest1ServiceMessage1Handler : Received " <<  numberOfReceivedMessagesSoFar << " Messages. \r";
        fflush (stdout);
    }

    if (100000 == numberOfReceivedMessagesSoFar)
    {
        numberOfReceivedMessagesSoFar = 0;
    }

    pMsg->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMsg);
}

}
