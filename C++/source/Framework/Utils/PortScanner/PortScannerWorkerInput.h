/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERWORKERINPUT_H
#define PORTSCANNERWORKERINPUT_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"
#include "Framework/Types/Types.h"
#include "Framework/Types/UI32Range.h"

#include <string>

namespace WaveNs
{

class PortScannerWorkerInput : public MapReduceManagerDelegateMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                           PortScannerWorkerInput   ();
        virtual           ~PortScannerWorkerInput   ();

                string     getIpAddress             () const;
                void       setIpAddress             (const string &ipAddress);

                UI32Range  getPortRange             () const;
                void       setPortRange             (const UI32Range &portRange);

                UI32       getTimeoutInMilliSeconds () const;
                void       setTimeoutInMilliSeconds (const UI32 &timeoutInMilliSeconds);

        // Now the data members

    private :
        string    m_ipAddress;
        UI32Range m_portRange;
        UI32      m_timeoutInMilliSeconds;

    protected :
    public :
};
}

#endif // PORTSCANNERWORKERINPUT_H
