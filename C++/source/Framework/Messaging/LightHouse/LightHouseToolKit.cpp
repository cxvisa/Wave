/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightHouseToolKit.h"

namespace WaveNs
{

string LightHouseToolKit::s_lightHouseMulticastIpAddress = "239.255.23.16";
SI32   LightHouseToolKit::s_lightHouseMulticastPort      = 5011;

string LightHouseToolKit::getLightHouseMulticastIpAddress ()
{
    return (s_lightHouseMulticastIpAddress);
}

void LightHouseToolKit::setLightHouseMulticastIpAddress (const string &lightHouseMulticastIpAddress)
{
    s_lightHouseMulticastIpAddress = lightHouseMulticastIpAddress;
}

SI32 LightHouseToolKit::getLightHouseMulticastPort ()
{
    return (s_lightHouseMulticastPort);
}

void LightHouseToolKit::setLightHouseMulticastPort (const SI32 &LightHouseMulticastPort)
{
    s_lightHouseMulticastPort = LightHouseMulticastPort;
}

}
