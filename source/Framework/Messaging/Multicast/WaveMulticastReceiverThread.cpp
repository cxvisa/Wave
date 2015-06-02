/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Multicast/WaveMulticastReceiverThread.h"

namespace WaveNs
{

WaveMulticastReceiverThread::WaveMulticastReceiverThread ()
     : PrismPosixThread ()
{
}

WaveMulticastReceiverThread::~WaveMulticastReceiverThread ()
{
}

WaveThreadStatus WaveMulticastReceiverThread::start ()
{
    return (WAVE_THREAD_SUCCESS);
}

}
