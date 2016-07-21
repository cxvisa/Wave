/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PortScanner/TcpPortScanner.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemLimitsUtils.h"
#include "Framework/Types/UI32Range.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>

namespace WaveNs
{

bool TcpPortScanner::scanForIpV4TcpPorts (const string &ipV4Address, set<UI32> inputPorts, set<UI32> &openPorts, set<UI32> &closedPorts, set<UI32> &timedOutPorts, set<UI32> &notTriedPorts)
{
    // TODO : Declare a ResourceEnum to return detailed status instead a simple boolean

    openPorts.clear     ();
    closedPorts.clear   ();
    timedOutPorts.clear ();

    struct in_addr inetAddress;

    SI32 status = inet_aton (ipV4Address.c_str (), &inetAddress);

    if (0 == status)
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
        const SI32 socket = ::socket (AF_INET, SOCK_STREAM, 0);

        if (0 > socket)
        {
            WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "TcpPortScanner::scanForIpV4TcpPorts : Errored out creating a socket.  Iteration %u, errno : %d, %s", i, errno, (SystemErrorUtils::getErrorStringForErrorNumber (errno)).c_str ());

            continue;
        }
        else
        {
            sockets.insert (socket);
        }
    }

    sockaddr_in socketAddress;

    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = inetAddress.s_addr;

    set<SI32>::const_iterator socketElement    = sockets.begin ();
    set<SI32>::const_iterator socketEndElement = sockets.end   ();

    while (socketEndElement != socketElement)
    {
        SI32 socketFlags = fcntl (*socketElement, F_GETFL, NULL);

        if (-1 == socketFlags)
        {
            ::close (*socketElement);

            sockets.erase (socketElement);
        }
        else
        {
            socketFlags = fcntl (*socketElement, F_SETFL, socketFlags | O_NONBLOCK);

            if (-1 == socketFlags)
            {
                ::close (*socketElement);

                sockets.erase (socketElement);
            }
        }

        socketElement++;
    }

    socketElement = sockets.begin ();

    set<UI32>::const_iterator inputPortElement    = inputPorts.begin ();
    set<UI32>::const_iterator inputPortEndElement = inputPorts.end   ();

    struct timeval timeOut;
           fd_set  socketFdSet;

    timeOut.tv_sec = 3;
    timeOut.tv_usec = 0;

    FD_ZERO (&socketFdSet);

    map<SI32, UI32> socketToPortMap;

    while (socketEndElement != socketElement)
    {
        socketAddress.sin_port = htons (*inputPortElement);

        SI32 connectionStatus = ::connect (*socketElement, (struct sockaddr *) &socketAddress, sizeof (socketAddress));

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
        }

        socketElement++;
        inputPortElement++;
    }

    fd_set socketFdSetToTryForInProgress;

    while (!(socketToPortMap.empty()))
    {
        fdCopy (&socketFdSet, &socketFdSetToTryForInProgress);

        SI32 maxFdToSelect = fdMax (&socketFdSetToTryForInProgress) + 1;
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

        closedPorts.insert (socketToPortMapElement->second);

        socketToPortMapElement++;
    }

    socketToPortMap.clear ();

    return (true);
}

void TcpPortScanner::fdCopy (fd_set *pSource, fd_set *pDestination)
{
    SI32 i = 0;

    FD_ZERO (pDestination);

    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (FD_ISSET(i, pSource))
        {
            FD_SET (i, pDestination);
        }
    }
}

SI32 TcpPortScanner::fdMax (fd_set *pSource)
{
    SI32 i = 0;

    for (i = FD_SETSIZE - 1; i >= 0; i--)
    {
        if (FD_ISSET(i, pSource))
        {
            return (i);
        }
    }

    return (-1);
}

ResourceId TcpPortScanner::scanPorts (vector<string> argv)
{
    const UI32   numberOfArguments = argv.size ();
          string ipAddress         = "127.0.0.1";
          SI32   startPort         = 1;
          SI32   endPort           = 65535;

    if (numberOfArguments >= 1)
    {
        ipAddress = argv[0];
    }

    if (numberOfArguments >= 2)
    {
        startPort = atoi ((argv[1]).c_str ());
    }

    if (numberOfArguments >= 3)
    {
        endPort = atoi ((argv[2]).c_str ());
    }

    UI32 softLimit = 0;
    UI32 hardLimit = 0;

    bool status = SystemLimitsUtils::getMaxNumberOfOpenFiles (softLimit, hardLimit);

    if (true == status)
    {
        tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Soft : %u, Hard : %u", softLimit, hardLimit);
    }
    else
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "TcpPortScanner::scanPorts : Could not obtain System Limits for maximum number of open files.");
    }

    vector<UI32> fileDescriptorsCurrentlyInUse;

    status = SystemLimitsUtils::getFileDescriptorsCurrentlyInUse (fileDescriptorsCurrentlyInUse);

    if (true == status)
    {
        tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Currently In Use File Descriptors :");

        vector<UI32>::const_iterator element    = fileDescriptorsCurrentlyInUse.begin ();
        vector<UI32>::const_iterator endElement = fileDescriptorsCurrentlyInUse.end   ();

        while (endElement != element)
        {
            tracePrintf (TRACE_LEVEL_INFO, true, true, "%u", *element);

            element++;
        }
    }
    else
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "TcpPortScanner::scanPorts : Could not obtain currently in use file descriptors.");
    }

    set<UI32> allOpenPorts;
    set<UI32> allClosedPorts;
    set<UI32> allTimedOutPorts;
    set<UI32> allNotTriedPorts;

    for (SI32 i = startPort; i <= endPort; i += 1000)
    {
        set<UI32> inputPorts;
        set<UI32> openPorts;
        set<UI32> closedPorts;
        set<UI32> timedOutPorts;
        set<UI32> notTriedPorts;

        UI32Range inputPortRange (i, i + 999 < endPort ? i + 999 : endPort);

        vector<UI32> inputPortRangeIntegers;

        inputPortRange.getUI32RangeVector (inputPortRangeIntegers);

        inputPorts.insert (inputPortRangeIntegers.begin (), inputPortRangeIntegers.end ());

        tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Processing Ports in Range : %s", (inputPortRange.toString ()).c_str ());


        status = TcpPortScanner::scanForIpV4TcpPorts (ipAddress, inputPorts, openPorts, closedPorts, timedOutPorts, notTriedPorts);

        allOpenPorts.insert     (openPorts.begin     (), openPorts.end     ());
        allClosedPorts.insert   (closedPorts.begin   (), closedPorts.end   ());
        allTimedOutPorts.insert (timedOutPorts.begin (), timedOutPorts.end ());
        allNotTriedPorts.insert (notTriedPorts.begin (), notTriedPorts.end ());

        if (true == status)
        {
            tracePrintf (TRACE_LEVEL_DEBUG, true, false, "TcpPortScanner::scanPorts : Currently open ports :");

            set<UI32>::const_iterator element    = openPorts.begin ();
            set<UI32>::const_iterator endElement = openPorts.end   ();

            while (endElement != element)
            {
                tracePrintf (TRACE_LEVEL_DEBUG, true, true, "%u", *element);

                element++;
            }
        }
        else
        {
            tracePrintf (TRACE_LEVEL_ERROR, true, false, "TcpPortScanner::scanPorts : Could not scan for IPV4 tcp ports.");
        }
    }

    tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Currently open ports : %u", allOpenPorts.size ());

    set<UI32>::const_iterator element    = allOpenPorts.begin ();
    set<UI32>::const_iterator endElement = allOpenPorts.end   ();

    while (endElement != element)
    {
        tracePrintf (TRACE_LEVEL_INFO, true, true, "%u", *element);

        element++;
    }

    tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Currently Closed ports    : %u", allClosedPorts.size   ());
    tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Currently Timed out ports : %u", allTimedOutPorts.size ());
    tracePrintf (TRACE_LEVEL_INFO, true, false, "TcpPortScanner::scanPorts : Currently Not Tried ports : %u", allNotTriedPorts.size ());

    return (0);
}


}
