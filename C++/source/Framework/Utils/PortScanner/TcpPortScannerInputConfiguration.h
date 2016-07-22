/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TCPPORTSCANNERINPUTCONFIGURATION_H
#define TCPPORTSCANNERINPUTCONFIGURATION_H

#include "Framework/Types/Types.h"
#include "Framework/Types/UI32Range.h"
#include <string>

using namespace std;

namespace WaveNs
{

class TcpPortScannerInputConfiguration
{
    private :
        static void printHelp (const char * const programName);

    protected :
    public :
                           TcpPortScannerInputConfiguration ();
        virtual           ~TcpPortScannerInputConfiguration ();

                string     getIpAddress                     () const;
                void       setIpAddress                     (const string &ipAddress);

                UI32       getNumberOfShards                () const;
                void       setNumberOfShards                (const UI32 &numberOfShards);

                UI32Range  getPortRange                     () const;
                void       setPortRange                     (const UI32Range &portRange);

                UI32       getTimeoutInMilliSeconds         () const;
                void       setTimeoutInMilliSeconds         (const UI32 &timeoutInMilliSeconds);

                bool       parseCommandLineInputs (const UI32 &numberOfInputArguments, const char * const inputArguments[]);

        // Now the data members

    private :
        string    m_ipAddress;
        UI32Range m_portRange;
        UI32      m_timeoutInMilliSeconds;
        UI32      m_numberOfShards;

    protected :
    public :
};

}

#endif // TCPPORTSCANNERINPUTCONFIGURATION_H
