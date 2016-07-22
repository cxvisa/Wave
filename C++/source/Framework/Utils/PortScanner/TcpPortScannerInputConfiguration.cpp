/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/TcpPortScannerInputConfiguration.h"
#include "Framework/Utils/TraceUtils.h"

#include <stdlib.h>

namespace WaveNs
{

TcpPortScannerInputConfiguration::TcpPortScannerInputConfiguration ()
    : m_ipAddress             ("127.0.0.1"),
      m_portRange             ("1-65535"),
      m_timeoutInMilliSeconds (3000),
      m_numberOfShards        (10)
{
}

TcpPortScannerInputConfiguration::~TcpPortScannerInputConfiguration ()
{
}

string TcpPortScannerInputConfiguration::getIpAddress () const
{
    return (m_ipAddress);
}

void TcpPortScannerInputConfiguration::setIpAddress (const string &ipAddress)
{
    m_ipAddress = ipAddress;
}

UI32 TcpPortScannerInputConfiguration::getNumberOfShards () const
{
    return (m_numberOfShards);
}

void TcpPortScannerInputConfiguration::setNumberOfShards (const UI32 &numberOfShards)
{
    m_numberOfShards = numberOfShards;
}

UI32Range TcpPortScannerInputConfiguration::getPortRange () const
{
    return (m_portRange);
}

void TcpPortScannerInputConfiguration::setPortRange (const UI32Range &portRange)
{
    m_portRange = portRange;
}

UI32 TcpPortScannerInputConfiguration::getTimeoutInMilliSeconds () const
{
    return (m_timeoutInMilliSeconds);
}

void TcpPortScannerInputConfiguration::setTimeoutInMilliSeconds (const UI32 &timeoutInMilliSeconds)
{
    m_timeoutInMilliSeconds = timeoutInMilliSeconds;
}

bool TcpPortScannerInputConfiguration::parseCommandLineInputs (const UI32 &numberOfInputArguments, const char * const inputArguments[])
{
    UI32 i= 0;

    for (i = 1; i < numberOfInputArguments; i++)
    {
        if (0 == (strcasecmp ("-ip", inputArguments[i])))
        {
            if (numberOfInputArguments > (i + 1))
            {
                bool isValid = IpVxAddress::isValidIpAddress (inputArguments[i + 1]);

                if (isValid)
                {
                    setIpAddress (inputArguments[i + 1]);
                }
                else
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, true, "Invalid IP Address.");

                    printHelp (inputArguments[0]);

                    return (false);
                }
            }
            else
            {
                printHelp (inputArguments[0]);

                return (false);
            }
        }
        else if (0 == (strcasecmp ("-p", inputArguments[i])))
        {
            if (numberOfInputArguments > (i + 1))
            {
                const string inputPortRangeString = inputArguments[i + 1];
                const bool   isValid              = UI32Range::isAValidString (inputPortRangeString);

                if (isValid)
                {
                    setPortRange (inputPortRangeString);
                }
                else
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, true, "Invalid port range.");

                    printHelp (inputArguments[0]);

                    return (false);
                }
            }
            else
            {
                printHelp (inputArguments[0]);

                return (false);
            }
        }
        else if (0 == (strcasecmp ("-t", inputArguments[i])))
        {
            if (numberOfInputArguments > (i + 1))
            {
                char *pLocationAfterValidDigits;

                long value = strtol (inputArguments[i + 1], &pLocationAfterValidDigits, 10);

                if (((inputArguments[i + 1]) == pLocationAfterValidDigits) || (value < 0))
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, true, "Invalid timeout.");

                    printHelp (inputArguments[0]);

                    return (false);
                }
                else
                {
                    setTimeoutInMilliSeconds (value);
                }
            }
            else
            {
                printHelp (inputArguments[0]);

                return (false);
            }
        }
        else if (0 == (strcasecmp ("-ns", inputArguments[i])))
        {
            if (numberOfInputArguments > (i + 1))
            {
                char *pLocationAfterValidDigits = NULL;

                long value = strtol (inputArguments[i + 1], &pLocationAfterValidDigits, 10);

                if (((inputArguments[i + 1]) == pLocationAfterValidDigits) || (value < 0))
                {
                    WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, true, "Invalid number of shards.");

                    printHelp (inputArguments[0]);

                    return (false);
                }

                setNumberOfShards (value);
            }
            else
            {
                printHelp (inputArguments[0]);

                return (false);
            }
        }
    }

    return (true);
}

void TcpPortScannerInputConfiguration::printHelp (const char * const programName)
{
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE:\r\n%s [-ip <IPV4/IPV6 address>] [-p <Comma Separated Port Range>] [-t <Timeout in Milli Seconds>] [-ns <Number Of Shards>]", programName);
}

}

