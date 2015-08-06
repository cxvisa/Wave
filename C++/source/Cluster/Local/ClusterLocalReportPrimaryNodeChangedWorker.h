/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef CLUSTERLOCALREPORTPRIMARYNODECHANGEDWORKER_H
#define CLUSTERLOCALREPORTPRIMARYNODECHANGEDWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalReportPrimaryNodeChangedMessage;
class WaveLinearSequencerContext;
class WaveWorker;

///Class:
///ClusterLocalReportPrimaryNodeChangedWorker
/// 
///Description:
/// This Class is a worker in the ClusterLocalObjectManager
/// It handles the ClusterLocalReportPrimaryNodeChangedMessage received
/// from the F/w.It updates the specific status of the node to SECONDARY_CONNECTED_TO_CLUSTER

class ClusterLocalReportPrimaryNodeChangedWorker : public WaveWorker
{
    private :
        //Handler for the ClusterLocalReportPrimaryNodeChnagedMessage received from the F/W
        void primaryNodeChangedMessageHandler                    (ClusterLocalReportPrimaryNodeChangedMessage *pClusterLocalReportPrimaryNodeChangedMessage);
        //Update the node status in the WaveNode MO
        void updateWaveNodeManagedObjectStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
   
    protected :
    public :
                 ClusterLocalReportPrimaryNodeChangedWorker (ClusterLocalObjectManager *pClusterLocalObjetManager);
        virtual ~ClusterLocalReportPrimaryNodeChangedWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CLUSTERLOCALREPORTPRIMARYNODECHANGEDWORKER_H
