/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef CLUSTERLOCALGETOBJECTIDWORKER_H
#define CLUSTERLOCALGETOBJECTIDWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalGetSlotObjectIdMessage;
class ClusterLocalGetLocationObjectIdMessage;
class ClusterLocalGetSlotNumberMessage; 
class ClusterLocalGetLocationIdMessage;
class WaveWorker;
class ClusterLocalWaveSlotManagementWorker;

class ClusterLocalGetObjectIdWorker: public WaveWorker
{
    private :
                void 	    getSlotObjectIdMessageHandler       (ClusterLocalGetSlotObjectIdMessage *pClusterLocalGetSlotObjectIdMessage);
                void        getLocationObjectIdMessageHandler   (ClusterLocalGetLocationObjectIdMessage *pClusterLocalGetLocationObjectIdMessage);
                void 	    getSlotNumberMessageHandler         (ClusterLocalGetSlotNumberMessage *pClusterLocalGetSlotNumberMessage);
                void        getLocationIdMessageHandler         (ClusterLocalGetLocationIdMessage *pClusterLocalGetLocationIdMessage);
                ObjectId    getObjectIdForLocation              (LocationId locationId);
                    
    protected :
    public :
                            ClusterLocalGetObjectIdWorker       (ClusterLocalObjectManager *pClusterLocalObjectManager);
        virtual            ~ClusterLocalGetObjectIdWorker       ();

    // Now the data members

    private :
    protected :
    public :
		friend	class ClusterLocalWaveSlotManagementWorker;
		
};

}

#endif //CLUSTERLOCALSETHAROLEWORKER_H 
