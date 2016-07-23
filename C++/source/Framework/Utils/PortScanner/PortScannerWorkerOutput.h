/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERWORKEROUTPUT_H
#define PORTSCANNERWORKEROUTPUT_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"

namespace WaveNs
{

class PortScannerWorkerOutput : public MapReduceWorkerResponseMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 PortScannerWorkerOutput ();
        virtual ~PortScannerWorkerOutput ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // PORTSCANNERWORKEROUTPUT_H

