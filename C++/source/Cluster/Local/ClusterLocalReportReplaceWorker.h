/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef CLUSTERLOCALREPORTREPLACEWORKER_H
#define CLUSTERLOCALREPORTREPLACEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalReportReplaceMessage;
class PrismLinearSequencerContext;
class WaveWorker;

///Class:
///ClusterLocalReportReplaceWorker
/// 
///Description:
/// This Class is a worker in the ClusterLocalObjectManager
/// It handles the ClusterLocalReportPrimaryNodeChangedMessage received

class ClusterLocalReportReplaceWorker : public WaveWorker
{
    private :
        //Handler for the ClusterLocalReportPrimaryNodeChnagedMessage received from the F/W
        void replaceMessageHandler                    (ClusterLocalReportReplaceMessage *pClusterLocalReportReplaceMessage);
        //Update the node status in the WaveNode MO
        void updateWaveNodeManagedObjectStep                     (PrismLinearSequencerContext *pPrismLinearSequencerContext);
   
    protected :
    public :
                 ClusterLocalReportReplaceWorker (ClusterLocalObjectManager *pClusterLocalObjetManager);
        virtual ~ClusterLocalReportReplaceWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CLUSTERLOCALREPORTREPLACEWORKER_H
