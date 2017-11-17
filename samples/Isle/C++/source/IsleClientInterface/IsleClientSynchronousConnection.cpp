/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleClientInterface/IsleClientSynchronousConnection.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveClientTransportObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "WaveResourceIdEnums.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

namespace IsleNs
{

IsleClientSynchronousConnection::IsleClientSynchronousConnection (const string &isleClientName, const string &waveServerIpAddress, const UI32 &waveServerPort)
    : WaveClientSynchronousConnection (isleClientName, waveServerIpAddress, waveServerPort)
{
}

IsleClientSynchronousConnection::IsleClientSynchronousConnection ()
    : WaveClientSynchronousConnection ()
{
}

IsleClientSynchronousConnection::~IsleClientSynchronousConnection ()
{
}

}
