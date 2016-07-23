/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERREADINESSDATA_H
#define PORTSCANNERREADINESSDATA_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerReadinessMessage.h"

namespace WaveNs
{

class PortScannerWorkerReadinessData : public MapReduceWorkerReadinessMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 PortScannerWorkerReadinessData ();
        virtual ~PortScannerWorkerReadinessData ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // PORTSCANNERREADINESSDATA_H
