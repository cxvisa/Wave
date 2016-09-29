/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "PortScannerInputConfiguration.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FdUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceManagerDelegateMessage.h"
#include "Framework/Utils/PortScanner/PortScannerWorkerReadinessData.h"

#include <stdlib.h>

#include "Framework/Utils/PortScanner/PortScannerWorkerInput.h"
namespace WaveNs
{

PortScannerInputConfiguration::PortScannerInputConfiguration ()
    : MapReduceInputConfiguration (100),
      m_ipAddress             ("127.0.0.1"),
      m_portRange             ("1-65535"),
      m_timeoutInMilliSeconds (3000),
      m_currentIndex          (0)
{
    m_portRange.getUI32RangeVector(m_expandedPortRange);
    m_currentIndex = 0;

    setTimeoutInMilliSecondsForManager (2 * m_timeoutInMilliSeconds);
}

PortScannerInputConfiguration::~PortScannerInputConfiguration ()
{
    setPortRange (m_portRange);
}

string PortScannerInputConfiguration::getIpAddress () const
{
    return (m_ipAddress);
}

void PortScannerInputConfiguration::setIpAddress (const string &ipAddress)
{
    m_ipAddress = ipAddress;
}

UI32Range PortScannerInputConfiguration::getPortRange () const
{
    return (m_portRange);
}

void PortScannerInputConfiguration::setPortRange (const UI32Range &portRange)
{
    m_portRange = portRange;

    m_portRange.getUI32RangeVector (m_expandedPortRange);
    m_currentIndex = 0;
}

UI32 PortScannerInputConfiguration::getTimeoutInMilliSeconds () const
{
    return (m_timeoutInMilliSeconds);
}

void PortScannerInputConfiguration::setTimeoutInMilliSeconds (const UI32 &timeoutInMilliSeconds)
{
    m_timeoutInMilliSeconds = timeoutInMilliSeconds;

    setTimeoutInMilliSecondsForManager (2 * m_timeoutInMilliSeconds);
}

bool PortScannerInputConfiguration::parseCommandLineInputs (const UI32 &numberOfInputArguments, const char * const inputArguments[])
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

                setMaximumNumberOfPartitions (value);
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

void PortScannerInputConfiguration::printHelp (const char * const programName)
{
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE:\r\n%s [-ip <IPV4/IPV6 address>] [-p <Comma Separated Port Range>] [-t <Timeout in Milli Seconds>] [-ns <Number Of Parallel Shards>]", programName);
}

UI32 PortScannerInputConfiguration::computeMaximumNumberOfPartitionsRequired () const
{
    UI32 availableFileDescriptorsSize = 0;

    bool status = FdUtils::getNumberOfAvailableFds (availableFileDescriptorsSize);

    if ((! status) || (0 == availableFileDescriptorsSize))
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "PortScannerInputConfiguration::computeMaximumNumberOfPartitionsRequired : Number of available File Descriptors could not be computed.");

        return (0);
    }

    const UI32Range    inputPortRange = getPortRange ();
          vector<UI32> allInputPorts;

    inputPortRange.getUI32RangeVector (allInputPorts);

    const UI32 numberOfInputPorts = allInputPorts.size ();

    return ((numberOfInputPorts + (availableFileDescriptorsSize - 1)) / availableFileDescriptorsSize);
}

MapReduceManagerDelegateMessage *PortScannerInputConfiguration::getNextWork (MapReduceWorkerReadinessMessage *pMapReduceWorkerReadinessMessage)
{
    PortScannerWorkerReadinessData *pPortScannerWorkerReadinessData = dynamic_cast<PortScannerWorkerReadinessData *> (pMapReduceWorkerReadinessMessage);

    if (NULL == pPortScannerWorkerReadinessData)
    {
        waveAssert (false, __FILE__, __LINE__);
        return (NULL);
    }

    const UI32 numberOfPortsToScanFor = pPortScannerWorkerReadinessData->getNumberOfPortsToScanFor ();
    const UI32 numberOfInputPorts     = m_expandedPortRange.size ();

    if (numberOfInputPorts <= m_currentIndex)
    {
        return (NULL);
    }

    UI32 endIndex = m_currentIndex + numberOfPortsToScanFor - 1;

    if (numberOfInputPorts <= endIndex)
    {
        endIndex = numberOfInputPorts - 1;
    }

    PortScannerWorkerInput *pPortScannerWorkerInput = new PortScannerWorkerInput ();

    waveAssert (NULL != pPortScannerWorkerInput, __FILE__, __LINE__);

    vector<UI32> currentItertionPorts;
    UI32         i                     = 0;

    for (i = m_currentIndex; i <= endIndex; i++)
    {
        currentItertionPorts.push_back (m_expandedPortRange[i]);
    }

    m_currentIndex = endIndex + 1;

    UI32Range currentIterationPortRange (currentItertionPorts);

    pPortScannerWorkerInput->setIpAddress             (m_ipAddress);
    pPortScannerWorkerInput->setPortRange             (currentIterationPortRange);
    pPortScannerWorkerInput->setTimeoutInMilliSeconds (m_timeoutInMilliSeconds);

    return (pPortScannerWorkerInput);
}

}

