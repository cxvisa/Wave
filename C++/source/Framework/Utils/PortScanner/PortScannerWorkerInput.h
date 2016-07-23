/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERWORKERINPUT_H
#define PORTSCANNERWORKERINPUT_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"

namespace WaveNs
{

class PortScannerWorkerInput : public MapReduceManagerDelegateMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 PortScannerWorkerInput ();
        virtual ~PortScannerWorkerInput ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // PORTSCANNERWORKERINPUT_H
