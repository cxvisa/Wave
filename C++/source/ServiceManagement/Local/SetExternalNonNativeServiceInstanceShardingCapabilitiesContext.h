/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESCONTEXT_H
#define SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class SetExternalNonNativeServiceInstanceShardingCapabilitiesContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                    SetExternalNonNativeServiceInstanceShardingCapabilitiesContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                    ~SetExternalNonNativeServiceInstanceShardingCapabilitiesContext ();

                string              getApplicationName          () const;
                void                setApplicationName          (const string &applicationName);

                string              getApplicationInstanceName  () const;
                void                setApplicationInstanceName  (const string &applicationInstanceName);

                vector<ResourceId>  getShardingCapabilities     () const;
                void                setShardingCapabilities     (const vector<ResourceId> shardingCapabilities);

    // Now the Data Members

    private :
        string             m_applicationName;
        string             m_applicationInstanceName;
        vector<ResourceId> m_shardingCapabilities;

    protected :
    public :
};

}

#endif // SETEXTERNALNONNATIVESERVICEINSTANCESHARDINGCAPABILITIESCONTEXT_H
