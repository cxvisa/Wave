/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETOOLKIT_H
#define LIGHTHOUSETOOLKIT_H

#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class LightHouseToolKit
{
    private :
    protected :
    public :
        static string getLightHouseMulticastIpAddress ();
        static void   setLightHouseMulticastIpAddress (const string &lightHouseMulticastIpAddress);

        static SI32   getLightHouseMulticastPort      ();
        static void   setLightHouseMulticastPort      (const SI32 &lightHouseMulticastPort);

        // Now the data members

    private :
        static string s_lightHouseMulticastIpAddress;
        static SI32   s_lightHouseMulticastPort;

    protected :
    public :
};

}

#endif // LIGHTHOUSETOOLKIT_H
