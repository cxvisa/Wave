/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERLOCALSETTHISNODEIPADDRESSWORKER_H
#define CLUSTERLOCALSETTHISNODEIPADDRESSWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalSetThisNodeIpAddressMessage;
class PrismLinearSequencerContext;

class ClusterLocalSetThisNodeIpAddressWorker : public WaveWorker
{
    private :
        void setThisNodeIpAddressMessageHandler                        (ClusterLocalSetThisNodeIpAddressMessage *pClusterLocalSetThisNodeIpAddressMessage);
        void setThisNodeIpAddressValidateStep                          (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void setThisNodeIpAddressUpdatePrismFrameworkObjectManagerStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void setThisNodeIpAddressUpdateThisWaveNodeStep                (PrismLinearSequencerContext *pPrismLinearSequencerContext);

    protected :
    public :
                 ClusterLocalSetThisNodeIpAddressWorker (ClusterLocalObjectManager *pClusterLocalObjetManager);
        virtual ~ClusterLocalSetThisNodeIpAddressWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CLUSTERLOCALSETTHISNODEIPADDRESSWORKER_H
