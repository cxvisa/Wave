/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESWORKER_H
#define SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

using namespace WaveNs;

namespace WaveNs
{

class SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage;
class SetExternalNonNativeServiceInstanceShardingCapabilitiesContext;

class SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker : public WaveWorker
{
    private :
        void setExternalNonNativeServiceInstanceShardingCapabilitiesRequestHandler (SetExternalNonNativeServiceInstanceShardingCapabilitiesMessage *pSetExternalNonNativeServiceInstanceShardingCapabilitiesMessage);
        void validateStep                                                          (SetExternalNonNativeServiceInstanceShardingCapabilitiesContext *pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext);
        void setStep                                                               (SetExternalNonNativeServiceInstanceShardingCapabilitiesContext *pSetExternalNonNativeServiceInstanceShardingCapabilitiesContext);

    protected :
    public :
                 SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESWORKER_H
