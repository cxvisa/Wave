/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMULTICASTRECEIVERTHREAD_H
#define WAVEMULTICASTRECEIVERTHREAD_H

#include "Framework/MultiThreading/PrismPosixThread.h"

namespace WaveNs
{

class WaveMulticastReceiverThread : public PrismPosixThread
{
    private :
                                 WaveMulticastReceiverThread ();

        virtual WaveThreadStatus start                       ();

    protected :
    public :
        virtual ~WaveMulticastReceiverThread ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMULTICASTRECEIVERTHREAD_H
