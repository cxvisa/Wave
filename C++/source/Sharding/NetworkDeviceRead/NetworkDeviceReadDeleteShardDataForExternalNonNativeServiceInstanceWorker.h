/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEWORKER_H
#define NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext;
class NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage;

class NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker : public WaveWorker
{
    private :
        WaveMessage *createMessageInstance (const UI32 &operationCode);

        void deleteShardDataForExternalNonNativeServiceInstanceRequestHandler (NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage *pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceMessage);

        void deleteStep                                                       (NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext *pNetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext);

    protected :
    public :
                 NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceWorker ();

    // Now the Data Members

    private :

    protected :
    public :
};

}

#endif // NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCEWORKER_H
