/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                                   *
 ***************************************************************************/

#ifndef CLUSTERLOCALSETHAROLEWORKER_H
#define CLUSTERLOCALSETHAROLEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalSetHaRoleMessage;
class WaveLinearSequencerContext;
class WaveWorker;

class ClusterLocalSetHaRoleWorker : public WaveWorker
{
    private :
        void setHaRoleMessageHandler                           (ClusterLocalSetHaRoleMessage* pClusterLocalSetHaRoleMessage);

        void updateWaveHaNodeManagedObjectStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                    
    protected :
    public :
                  ClusterLocalSetHaRoleWorker(ClusterLocalObjectManager *pClusterLocalObjetManager);
        virtual ~ClusterLocalSetHaRoleWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif //CLUSTERLOCALSETHAROLEWORKER_H 
