/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "PortScanner.h"

#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemLimitsUtils.h"
#include "Framework/Types/UI32Range.h"
#include "Framework/Utils/FdUtils.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netdb.h>

namespace WaveNs
{

bool PortScanner::scanForIpPorts (const string &ipAddress, set<UI32> inputPorts, const UI32 &timeoutInMilliSeconds, set<UI32> &openPorts, set<UI32> &closedPorts, set<UI32> &timedOutPorts, set<UI32> &notTriedPorts)
{
    // Here is the high level flow for determining open tcp ports.
    // Currently this scanner support scanning TCP/IP ports via connect call.

    // We first do basic validations like IP Address validations etc.  A few more validations with respect to ports are TBD at this point.
    // Then we create enough sockets based on IP Address family.
    // We then try to connect all of those sockets using appropriate address family to the given ip address and each of the ports given in input.
    // We set the sockets to ASYNC mode before calling connect so that all of those connects can be done in parallel.
    // Then we examine various select states and classify the ports open/closed etc.,
    // Classifying for timed out ports (can be easily done below) and Not tried ports etc are TBD at this point.

    // TODO : Declare a ResourceEnum to return detailed status instead a simple boolean

    openPorts.clear     ();
    closedPorts.clear   ();
    timedOutPorts.clear ();

    struct in_addr  inetAddress;
    struct in6_addr inet6Address;

    bool isValid = IpVxAddress::isValidIpAddress (ipAddress);

    if (! isValid)
    {
        return (false);
    }

    IpVxAddress ipVxAddress (ipAddress);

    UI32 addressFamily = ipVxAddress.getAddressFamily();

    SI32 status = -1;

    switch (addressFamily)
    {
        case AF_INET :
            status = inet_pton (AF_INET, ipAddress.c_str (), &inetAddress);
            break;

        case AF_INET6 :
            status = inet_pton (AF_INET6, ipAddress.c_str (), &inet6Address);
    }

    if (1 != status)
    {
        return (false);
    }

    const SI32 numberOfInputPorts = inputPorts.size ();

    if (0 == numberOfInputPorts)
    {
        return (false);
    }

    // TODO : validate the ports given as input

    set<SI32> sockets;
    SI32      i        = 0;
    SI32      maxFd    = 0;

    for (i = 0; i < numberOfInputPorts; i++)
    {
        const SI32 socket = ::socket (addressFamily, SOCK_STREAM, 0);

        if (0 > socket)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "PortScanner::scanForIpV4TcpPorts : Errored out creating a socket.  Iteration %u, errno : %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            continue;
        }
        else
        {
            sockets.insert (socket);
        }
    }

    sockaddr_in  socketAddress;
    sockaddr_in6 socketAddress6;

    switch (addressFamily)
    {
        case AF_INET :
            socketAddress.sin_family = AF_INET;
            socketAddress.sin_addr.s_addr = inetAddress.s_addr;
            break;

        case AF_INET6 :
            socketAddress6.sin6_family = AF_INET6;
            socketAddress6.sin6_addr = inet6Address;
            break;
    }

    set<SI32>::const_iterator socketElement    = sockets.begin ();
    set<SI32>::const_iterator socketEndElement = sockets.end   ();

    while (socketEndElement != socketElement)
    {
        SI32 socketFlags = fcntl (*socketElement, F_GETFL, NULL);

        if (-1 == socketFlags)
        {
            ::close (*socketElement);

            sockets.erase (socketElement);

            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Obtaining flags for socket %d failed.", *socketElement);
        }
        else
        {
            socketFlags = fcntl (*socketElement, F_SETFL, socketFlags | O_NONBLOCK);

            if (-1 == socketFlags)
            {
                ::close (*socketElement);

                sockets.erase (socketElement);

                WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Setting flags for socket %d failed.", *socketElement);
            }
        }

        socketElement++;
    }

    socketElement = sockets.begin ();

    set<UI32>::const_iterator inputPortElement    = inputPorts.begin ();
    set<UI32>::const_iterator inputPortEndElement = inputPorts.end   ();

    struct timeval timeOut;
           fd_set  socketFdSet;

    timeOut.tv_sec = timeoutInMilliSeconds / 1000;
    timeOut.tv_usec = (timeoutInMilliSeconds % 1000) * 1000;

    FD_ZERO (&socketFdSet);

    map<SI32, UI32> socketToPortMap;

    while (socketEndElement != socketElement)
    {
        SI32 connectionStatus = -1;

        switch (addressFamily)
        {
            case AF_INET :
                socketAddress.sin_port = htons (*inputPortElement);
                connectionStatus = ::connect (*socketElement, (struct sockaddr *) &socketAddress, sizeof (socketAddress));
                break;

            case AF_INET6 :
                socketAddress6.sin6_port = htons (*inputPortElement);
                connectionStatus = ::connect (*socketElement, (struct sockaddr *) &socketAddress6, sizeof (socketAddress6));
                break;
        }

        if (0 == connectionStatus)
        {
            ::close (*socketElement);

            openPorts.insert (*inputPortElement);
        }
        else if (-1 == connectionStatus)
        {
            if (EINPROGRESS == errno)
            {
                FD_SET (*socketElement, &socketFdSet);

                if (maxFd < (*socketElement))
                {
                    maxFd = *socketElement;
                }

                socketToPortMap[*socketElement] = *inputPortElement;
            }
            else
            {
                ::close (*socketElement);

                closedPorts.insert (*inputPortElement);
            }
        }
        else
        {
            ::close (*socketElement);

            closedPorts.insert (*inputPortElement);

            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "Connect Failed for port %d with errno : %d : %s", *inputPortElement, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());
        }

        socketElement++;
        inputPortElement++;
    }

    fd_set socketFdSetToTryForInProgress;

    while (!(socketToPortMap.empty()))
    {
        FdUtils::fdCopy (&socketFdSet, &socketFdSetToTryForInProgress);

        SI32 maxFdToSelect = FdUtils::fdMax (&socketFdSetToTryForInProgress) + 1;
        SI32 selectStatus = select (maxFdToSelect, NULL, &socketFdSetToTryForInProgress, NULL, &timeOut);

        if (0 < selectStatus)
        {
            for (i = 0; i < maxFdToSelect; i++)
            {
                if (FD_ISSET(i, &socketFdSetToTryForInProgress))
                {
                    SI32 socketOptionValue = 0;
                    UI32 lengthOfSocketOptionValue = sizeof (socketOptionValue);

                    SI32 getSocketOptionStatus = getsockopt (i, SOL_SOCKET, SO_ERROR, (void *)(&socketOptionValue), &lengthOfSocketOptionValue);

                    if (0 == getSocketOptionStatus)
                    {
                        if (0 == socketOptionValue)
                        {
                            openPorts.insert(socketToPortMap[i]);
                        }
                        else
                        {
                            closedPorts.insert(socketToPortMap[i]);
                        }
                    }
                    else
                    {

                    }

                    ::close (i);
                    socketToPortMap.erase(i);
                    FD_CLR (i, &socketFdSet);
                }
            }
        }
        else if (0 == selectStatus)
        {
            break;
        }
        else
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }

    map<SI32, UI32>::const_iterator socketToPortMapElement    = socketToPortMap.begin ();
    map<SI32, UI32>::const_iterator socketToPortMapEndElement = socketToPortMap.end   ();

    while (socketToPortMapEndElement != socketToPortMapElement)
    {
        ::close (socketToPortMapElement->first);

        // TODO : Instead of always classifying as closed, determine appropriate classification based on how and where we exited from the above loop around select.

        timedOutPorts.insert (socketToPortMapElement->second);

        socketToPortMapElement++;
    }

    socketToPortMap.clear ();

    return (true);
}

ResourceId PortScanner::scanPorts (const PortScannerInputConfiguration &portScannerInputConfiguration, set<UI32> &allOpenPorts, set<UI32> &allClosedPorts, set<UI32> &allTimedOutPorts, set<UI32> &allNotTriedPorts)
{
          UI32   numberOfPortsToScanInABatch     = 1000; // Default value, will get reset below if possible.
          UI32   numberOfPortsToScanInABatchTemp = 0;

    const string ipAddress                       = portScannerInputConfiguration.getIpAddress             ();
    const UI32   timeoutInMilliSeconds           = portScannerInputConfiguration.getTimeoutInMilliSeconds ();

    bool batchSizeComputationStatus = FdUtils::getNumberOfAvailableFds (numberOfPortsToScanInABatchTemp);

    if (batchSizeComputationStatus)
    {
        numberOfPortsToScanInABatch = numberOfPortsToScanInABatchTemp;
    }

    tracePrintf (TRACE_LEVEL_DEBUG, true, false, "PortScanner::scanPorts : Batch Size : %u", numberOfPortsToScanInABatch);

    UI32Range inputPortRange    = portScannerInputConfiguration.getPortRange ();
    vector<UI32> allInputPorts;

    inputPortRange.getUI32RangeVector (allInputPorts);

    vector<UI32>::const_iterator element          = allInputPorts.begin ();
    vector<UI32>::const_iterator batchEndElement;
    vector<UI32>::const_iterator endElement       = allInputPorts.end   ();

    while (endElement != element)
    {
        set<UI32> inputPorts;
        set<UI32> openPorts;
        set<UI32> closedPorts;
        set<UI32> timedOutPorts;
        set<UI32> notTriedPorts;

        batchEndElement = element + numberOfPortsToScanInABatch < endElement ? element + numberOfPortsToScanInABatch : endElement;

        inputPorts.insert (element, batchEndElement);

        vector<UI32> inputPortsVector;

        inputPortsVector.insert (inputPortsVector.end (), inputPorts.begin (), inputPorts.end ());
        const string rangeString = UI32Range::getUI32RangeStringFromVector (inputPortsVector);

        tracePrintf (TRACE_LEVEL_DEBUG, true, false, "PortScanner::scanPorts : Processing Ports in Range : %s", rangeString.c_str ());


        bool scanStatus = PortScanner::scanForIpPorts (ipAddress, inputPorts, timeoutInMilliSeconds, openPorts, closedPorts, timedOutPorts, notTriedPorts);

        allOpenPorts.insert     (openPorts.begin     (), openPorts.end     ());
        allClosedPorts.insert   (closedPorts.begin   (), closedPorts.end   ());
        allTimedOutPorts.insert (timedOutPorts.begin (), timedOutPorts.end ());
        allNotTriedPorts.insert (notTriedPorts.begin (), notTriedPorts.end ());

        if (true == scanStatus)
        {
            tracePrintf (TRACE_LEVEL_DEBUG, true, false, "PortScanner::scanPorts : Currently open ports :");

            set<UI32>::const_iterator elementForOpenPorts    = openPorts.begin ();
            set<UI32>::const_iterator endElementForOpenPorts = openPorts.end   ();

            while (endElementForOpenPorts != elementForOpenPorts)
            {
                tracePrintf (TRACE_LEVEL_DEBUG, true, true, "%u", *elementForOpenPorts);

                elementForOpenPorts++;
            }
        }
        else
        {
            tracePrintf (TRACE_LEVEL_ERROR, true, false, "PortScanner::scanPorts : Could not scan for IPV4 tcp ports.");
        }

        element = batchEndElement;
    }

    return (0);
}

ResourceId PortScanner::scanPorts (const PortScannerInputConfiguration &portScannerInputConfiguration)
{
    set<UI32> allOpenPorts;
    set<UI32> allClosedPorts;
    set<UI32> allTimedOutPorts;
    set<UI32> allNotTriedPorts;

    ResourceId status = scanPorts (portScannerInputConfiguration, allOpenPorts, allClosedPorts, allTimedOutPorts, allNotTriedPorts);

    if (!status)
    {
        tracePrintf (TRACE_LEVEL_FATAL, true, false, "PortScanner::scanPorts : Port Scanning failed.");
    }

    tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScanner::scanPorts : Currently open ports : %u", allOpenPorts.size ());

    set<UI32>::const_iterator elementForAllOpenPorts    = allOpenPorts.begin ();
    set<UI32>::const_iterator endElementForAllOpenPorts = allOpenPorts.end   ();

    setservent (1);

    while (endElementForAllOpenPorts != elementForAllOpenPorts)
    {
        struct servent *pServiceEntry = getservbyport (htons ((int) (*elementForAllOpenPorts)), "tcp");

        tracePrintf (TRACE_LEVEL_INFO, true, true, "%5u %s", *elementForAllOpenPorts, pServiceEntry != NULL ? pServiceEntry->s_name : "Unknown");

        elementForAllOpenPorts++;
    }

    endservent ();

    tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScanner::scanPorts : Currently Closed ports    : %u", allClosedPorts.size   ());
    tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScanner::scanPorts : Currently Timed out ports : %u", allTimedOutPorts.size ());
    tracePrintf (TRACE_LEVEL_INFO, true, false, "PortScanner::scanPorts : Currently Not Tried ports : %u", allNotTriedPorts.size ());

    return (0);
}


}
