/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/Test/PrismNativeTest1Service.h"
#include "Framework/ServiceInterface/Test/PrismNativeTest1ServiceMessages.h"

namespace WaveNs
{

PrismNativeTest1Service::PrismNativeTest1Service ()
    : WaveObjectManager ("PrismNativeTest1Service")
{
   addOperationMap (WAVE_NATIVE_TEST1_SERVICE_MESSAGE1, reinterpret_cast<PrismMessageHandler> (&PrismNativeTest1Service::prismNativeTest1ServiceMessage1Handler));
}

PrismNativeTest1Service::~PrismNativeTest1Service ()
{
}

PrismNativeTest1Service *PrismNativeTest1Service::getInstance ()
{
    static PrismNativeTest1Service *pPrismNativeTest1Service = NULL;

    if (NULL == pPrismNativeTest1Service)
    {
        pPrismNativeTest1Service = new PrismNativeTest1Service ();
        WaveNs::prismAssert (NULL != pPrismNativeTest1Service, __FILE__, __LINE__);
    }

    return (pPrismNativeTest1Service);
}

PrismServiceId PrismNativeTest1Service::getPrismServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void PrismNativeTest1Service::prismNativeTest1ServiceMessage1Handler (PrismNativeTest1ServiceMessage1 *pMsg)
{
    trace (TRACE_LEVEL_DEVEL , "Prism Native Test1 Messge Received");

    static UI32 numberOfReceivedMessagesSoFar = 0;

    numberOfReceivedMessagesSoFar++;

    if (0 == (numberOfReceivedMessagesSoFar % 1000))
    {
        cout << "PrismNativeTest1Service::prismNativeTest1ServiceMessage1Handler : Received " <<  numberOfReceivedMessagesSoFar << " Messages. \r";
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
