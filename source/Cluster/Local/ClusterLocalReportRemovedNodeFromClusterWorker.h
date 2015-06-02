/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef CLUSTERLOCALREPORTREMOVEDNODEFROMCLUSTERWORKER_H
#define CLUSTERLOCALREPORTREMOVEDNODEFROMCLUSTERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalReportRemovedNodeFromClusterMessage;
class PrismLinearSequencerContext;
class WaveWorker;

///Class:
///ClusterLocalReportRemovedNodeFromClusterWorker
/// 
///Description:
/// This Class is a worker in the ClusterLocalObjectManager
/// It handles the ClusterLocalReportRemovedNodeFromClusterMessage received
/// from the F/w.It updates the specific status of the node to STAND_ALONE

class ClusterLocalReportRemovedNodeFromClusterWorker : public WaveWorker
{
    private :
        //Handler for the ClusterLocalReportRemovedNodeFromClusterMessage received from the F/W
        void nodeRemovedMessageHandler                           (ClusterLocalReportRemovedNodeFromClusterMessage* pClusterLocalReportRemovedNodeFromClusterMessage);

        //Update the node status in the WaveNode MO
        void updateWaveNodeManagedObjectStep                     (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                    
    protected :
    public :
                  ClusterLocalReportRemovedNodeFromClusterWorker(ClusterLocalObjectManager *pClusterLocalObjetManager);
        virtual ~ClusterLocalReportRemovedNodeFromClusterWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif //LUSTERLOCALREPORTREMOVEDNODEFROMCLUSTERWORKER_H 
