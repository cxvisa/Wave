/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCECONTEXT_H
#define NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCECONTEXT_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~NetworkDeviceReadDeleteShardDataForExternalNonNativeServiceInstanceContext ();

        vector<ObjectId> getServiceInstanceObjectIds () const;
        void             setServiceInstanceObjectIds (const vector<ObjectId> &serviceInstanceObjectIds);

    // Now the Data Members

    private :
        vector<ObjectId> m_serviceInstanceObjectIds;

    protected :
    public :
};

}

#endif // NETWORKDEVICEREADDELETESHARDDATAFOREXTERNALNONNATIVESERVICEINSTANCECONTEXT_H
