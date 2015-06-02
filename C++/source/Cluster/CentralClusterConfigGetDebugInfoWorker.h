/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef CENTRALCLUSTERCONFIGGETDEBUGINFOWORKER_H
#define CENTRALCLUSTERCONFIGGETDEBUGINFOWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{
class CentralClusterConfigObjectManager;
class ClusterConfigObjectManagerGetClusterInfoMessage;

///Class:
///CentralClusterConfigGetDebugInfoWorker
/// 
///Description:
/// This Class is a worker in the CentralClusterConfigObjectManager
/// that handles the GetClusterInfoMsg.It receives the message and 
/// packs the Principal and Secondary Node information obtained 
/// from PrismCluster and WaveNode objects

class  CentralClusterConfigGetDebugInfoWorker: public WaveWorker
{

private :        

                  CentralClusterConfigGetDebugInfoWorker   (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager);
    PrismMessage *createMessageInstance                    (const UI32 &operationCode);

    //Called by the framework when it receives a ClusterConfigObjectManagerGetClusterInfoMessage
    void          getDebugInfoHandler                      (ClusterConfigObjectManagerGetClusterInfoMessage 
							    *pClusterObjectManagerGetClusterInfoMessage);
    //Steps in the processing of the message
    void          getPrincipalNodeInfoStep                  (PrismLinearSequencerContext *pPrismLinearSequencerContext);
    void          getSecondaryNodesInfoStep                  (PrismLinearSequencerContext *pPrismLinearSequencerContext);

protected :

        ~CentralClusterConfigGetDebugInfoWorker();

    // Now the data members

private :
protected :
public :

    friend class CentralClusterConfigObjectManager;

};

}

#endif // CENTRALCLUSTERCONFIGGETDEBUGINFOWORKER_H
