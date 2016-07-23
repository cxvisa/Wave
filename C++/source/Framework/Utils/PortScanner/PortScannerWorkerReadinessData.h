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
        virtual      ~PortScannerWorkerReadinessData ();

                UI32  getNumberOfPortsToScanFor     () const;
                void  setNumberOfPortsToScanFor     (const UI32 &numberOfPortsToScanFor);

        // Now the data members

    private :
        UI32 m_numberOfPortsToScanFor;

    protected :
    public :
};
}

#endif // PORTSCANNERREADINESSDATA_H
