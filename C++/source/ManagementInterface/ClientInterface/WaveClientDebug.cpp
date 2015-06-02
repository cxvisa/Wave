/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ManagementInterface/ClientInterface/WaveClientDebug.h"
#include "ManagementInterface/ClientInterface/WaveClientSynchronousConnection.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Shell/ShellDebug.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"

#include <map>

using namespace std;

namespace WaveNs
{

map<string, WaveClientSynchronousConnection *>  s_serversMap;

WaveClientDebug::WaveClientDebug ()
{
}

WaveClientDebug::~WaveClientDebug ()
{
}

UI32 WaveClientDebug::debugConnect (UI32 argc, vector<string> argv)
{
    if (argc != 3)
    {
        return (SHELL_OK);
    }

    string serverIpAddress = argv[1];
    UI32   serverPort      = atoi (argv[2].c_str ());
    string uniqueString    = FrameworkToolKit::getUniqueString (serverIpAddress, serverPort);
    WaveConnectionStatus   connectionstatus = WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER;

    WaveClientSynchronousConnection *pWcsc = s_serversMap[uniqueString];

    if (NULL != pWcsc)
    {
        trace (TRACE_LEVEL_ERROR, "WaveClientDebug::debugConnect : Already connected to this server.");
    }
    else
    {
        pWcsc = new WaveClientSynchronousConnection (uniqueString, serverIpAddress, serverPort);

        prismAssert (NULL != pWcsc, __FILE__, __LINE__);

        connectionstatus = pWcsc->connect ();
        if (WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER == connectionstatus)
        {
            s_serversMap[uniqueString] = pWcsc;
        }
        else
        {
            delete pWcsc;
        }
    }

    return (SHELL_OK);
}

UI32 WaveClientDebug::debugClose (UI32 argc, vector<string> argv)
{
    if (argc != 3)
    {
        return (SHELL_OK);
    }

    string serverIpAddress = argv[1];
    UI32   serverPort      = atoi (argv[2].c_str ());
    string uniqueString    = FrameworkToolKit::getUniqueString (serverIpAddress, serverPort);

    WaveClientSynchronousConnection *pWcsc = s_serversMap[uniqueString];

    if (NULL == pWcsc)
    {
        trace (TRACE_LEVEL_ERROR, "WaveClientDebug::debugConnect : Not connected to this server.");
    }
    else
    {
        prismAssert (NULL != pWcsc, __FILE__, __LINE__);

        pWcsc->close ();

        s_serversMap.erase (uniqueString);

        delete pWcsc;
    }

    return (SHELL_OK);
}

}
