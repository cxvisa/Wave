/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/Test/PrismNativeTest1ServiceMessages.h"
#include "Framework/ServiceInterface/Test/PrismNativeTest1Service.h"

namespace WaveNs
{

PrismNativeTest1ServiceMessage1::PrismNativeTest1ServiceMessage1 ()
    : WaveMessage (PrismNativeTest1Service::getWaveServiceId (), WAVE_NATIVE_TEST1_SERVICE_MESSAGE1)
{
}

PrismNativeTest1ServiceMessage1::~PrismNativeTest1ServiceMessage1 ()
{
}

}
