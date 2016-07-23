/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TCPPORTSCANNERINPUTCONFIGURATION_H
#define TCPPORTSCANNERINPUTCONFIGURATION_H

#include "Framework/Types/Types.h"
#include "Framework/Types/UI32Range.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceInputConfiguration.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PortScannerInputConfiguration : public MapReduceInputConfiguration
{
    private :
        static void printHelp (const char * const programName);

    protected :
    public :
                           PortScannerInputConfiguration         ();
        virtual           ~PortScannerInputConfiguration         ();

                string     getIpAddress                             () const;
                void       setIpAddress                             (const string &ipAddress);

                UI32Range  getPortRange                             () const;
                void       setPortRange                             (const UI32Range &portRange);

                UI32       getTimeoutInMilliSeconds                 () const;
                void       setTimeoutInMilliSeconds                 (const UI32 &timeoutInMilliSeconds);

                bool       parseCommandLineInputs                   (const UI32 &numberOfInputArguments, const char * const inputArguments[]);

        virtual UI32       computeMaximumNumberOfPartitionsRequired () const;

        // Now the data members

    private :
        string    m_ipAddress;
        UI32Range m_portRange;
        UI32      m_timeoutInMilliSeconds;

    protected :
    public :
};

}

#endif // TCPPORTSCANNERINPUTCONFIGURATION_H
