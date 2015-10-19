/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/Test/WaveNativeTest1ServiceMessages.h"
#include "Framework/ServiceInterface/Test/WaveNativeTest1Service.h"

namespace WaveNs
{

WaveNativeTest1ServiceMessage1::WaveNativeTest1ServiceMessage1 ()
    : WaveMessage (WaveNativeTest1Service::getWaveServiceId (), WAVE_NATIVE_TEST1_SERVICE_MESSAGE1)
{
}

WaveNativeTest1ServiceMessage1::~WaveNativeTest1ServiceMessage1 ()
{
}

}
