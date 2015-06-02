
/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef CLUSTERMANAGEDOBJECT_H
#define CLUSTERMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Cluster/NodeManagedObject.h"
#include "Cluster/ClusterMessages.h"
#include <string>
#include <vector>


namespace WaveNs
{


class ClusterManagedObject : public  WaveManagedObject
{
    private :
    protected :
    public :
                            ClusterManagedObject        (WaveObjectManager *pWaveObjectManager);
                           ~ClusterManagedObject        ();

       static string        getClassName                ();

       void                 showStatistic               ();
       NodeManagedObject   *getSelfNode                 ();
       NodeManagedObject   *getPrimaryNode              ();
       UI32                 getNSecondaryNodes          ();
       void                 setNSecondaryNodes          (UI32 nSecondaryNodes);
       NodeManagedObject   *getSecondaryNode            (UI32 nodeIndex);
       void                 setSecondaryNode            (UI32 nodeIndex, NodeManagedObject &secondaryNode);
       void                 addSecondaryNode            (NodeManagedObject &secondaryNode);
       UI32                 getThisNodeRole             ();
//       UI32                 getClusterCreated ();
//       UI32                 getTimeout ();
//       UI32                 getNLostHeartBeatToNotify ();

    // Now the data members

    private :
        NodeManagedObject                       m_selfNode;
        NodeManagedObject                       m_primaryNode;
        UI32                                    m_nSecondaryNodes;
        vector<NodeManagedObject>               m_nodeList;
        UI32                                    m_clusterCreated;

    protected :
    public :
        friend class CentralClusterConfigObjectManager;
        friend class LocalClusterConfigObjectManager;
//        WaveObjectManager                       *m_pWaveObjectManager;
//        UI32                                    m_timeout;
//        UI32                                    m_nLostHeartBeatToNotify;


};


}
#endif //CLUSTERMANAGEDOBJECT_H

