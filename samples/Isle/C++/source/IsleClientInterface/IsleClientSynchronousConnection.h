/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ISLECLIENTSYNCHRONOUSCONNECTION_H
#define ISLECLIENTSYNCHRONOUSCONNECTION_H

#include "ManagementInterface/ClientInterface/WaveClientSynchronousConnection.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "IsleResourceIdEnums.h"

#include <string>
#include <vector>

using namespace std;
using namespace WaveNs;

namespace IsleNs
{

class IsleClientSynchronousConnection : public WaveClientSynchronousConnection
{
    private :
    protected :
    public :
                            IsleClientSynchronousConnection (const string &isleClientName, const string &waveServerIpAddress, const UI32 &waveServerPort);
                            IsleClientSynchronousConnection ();
        virtual            ~IsleClientSynchronousConnection ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // ISLECLIENTSYNCHRONOUSCONNECTION_H
