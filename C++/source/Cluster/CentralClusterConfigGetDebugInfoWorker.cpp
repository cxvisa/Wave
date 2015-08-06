/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#include "CentralClusterConfigGetDebugInfoWorker.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/ClusterMessages.h"
#include "Cluster/ClusterTypes.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Cluster/PrismCluster.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"

namespace WaveNs
{

/// Name
/// CentralClusterConfigGetDebugInfoWorker()
/// Description
/// Constructor
/// Input
/// pCentralClusterConfigObjectManager : pointer to owner configManager
/// Output
/// None
/// Return
/// None

CentralClusterConfigGetDebugInfoWorker::
CentralClusterConfigGetDebugInfoWorker(CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager)
:WaveWorker(pCentralClusterConfigObjectManager)
{
    addOperationMap(CLUSTER_GET_DEBUGINFO, reinterpret_cast<WaveMessageHandler> 
		    (&CentralClusterConfigGetDebugInfoWorker::getDebugInfoHandler));
}

/// Name
/// ~CentralClusterConfigGetDebugInfoWorker()
/// Description
/// Destructor
/// Input
/// 
/// Output
/// 
/// Return
/// 

CentralClusterConfigGetDebugInfoWorker::
~CentralClusterConfigGetDebugInfoWorker()
{
}

/// Name
/// createMessageInstance
/// Description
/// Creates the ClusterConfigObjectManagerGetClusterInfoMessage
/// Input
/// opcode
/// Output
/// pointer to message
/// Return
/// none

WaveMessage *CentralClusterConfigGetDebugInfoWorker::createMessageInstance(const UI32 & operationCode)
{
  WaveMessage *pWaveMessage = 0;

  switch(operationCode) {
  case CLUSTER_GET_DEBUGINFO:
      pWaveMessage = new ClusterConfigObjectManagerGetClusterInfoMessage();
      break;
  default:
      pWaveMessage = 0;
      break;
  }
  return pWaveMessage;
}
/// Name
/// getDebugInfoHandler
/// Description
/// Called by the framework when it receives a ClusterConfigObjectManagerGetClusterInfoMessage.
/// It composes the steps to process the message and then starts processing by creating 
/// and invoking the context.
/// Input
/// ClusterConfigObjectManagerGetClusterInfoMessage
/// Output
/// none
/// Return
/// none

void CentralClusterConfigGetDebugInfoWorker::getDebugInfoHandler(ClusterConfigObjectManagerGetClusterInfoMessage 
							    *pClusterObjectManagerGetClusterInfoMsg)
{
  trace(TRACE_LEVEL_DEBUG,"getDebugInfoHandler Called");
  PrismLinearSequencerStep sequencerSteps[] = 
  {

      reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigGetDebugInfoWorker::getPrincipalNodeInfoStep),
      reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigGetDebugInfoWorker::getSecondaryNodesInfoStep),
      reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigGetDebugInfoWorker::prismLinearSequencerSucceededStep),
      reinterpret_cast<PrismLinearSequencerStep> (&CentralClusterConfigGetDebugInfoWorker::prismLinearSequencerFailedStep)
  };

  //Note that this is freed in SequencerSucceeded step inside the framework code
  WaveLinearSequencerContext* pWaveLinearSequencerContext = new WaveLinearSequencerContext(pClusterObjectManagerGetClusterInfoMsg,
								 this,
								 sequencerSteps,
								 sizeof(sequencerSteps)/sizeof(sequencerSteps[0]));  
  pWaveLinearSequencerContext->holdAll();
  pWaveLinearSequencerContext->start();

  return;
}

/// Name
/// getPrincipalNodeInfoStep
/// Description
/// packs  primary node information into ClusterConfigObjectManagerGetClusterInfoMessage
/// Input
/// WaveLinearSequencerContext : Used by the f/w
/// Output
/// none
/// Return
/// none
void CentralClusterConfigGetDebugInfoWorker::getPrincipalNodeInfoStep(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
     trace (TRACE_LEVEL_DEVEL, 
	    " CentralClusterConfigGetDebugInfoWorker::getPrincipalNodeInfoStep:Begin");

     ClusterConfigObjectManagerGetClusterInfoMessage* pClusterObjectManagerGetClusterInfoMsg =dynamic_cast<ClusterConfigObjectManagerGetClusterInfoMessage*>(pWaveLinearSequencerContext->getPWaveMessage());

      waveAssert(pClusterObjectManagerGetClusterInfoMsg!=0,__FILE__,__LINE__);

     //pointer to the cluster MO. Note that this vector will have only one element 
     //because the node is part of only one cluster.
     vector<WaveManagedObject *> *pResults = querySynchronously (PrismCluster::getClassName ());
     waveAssert (NULL != pResults, __FILE__, __LINE__);
     if (NULL == pResults)
     {         
	 trace(TRACE_LEVEL_INFO ,"MO for cluster not found");
	 pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
	 return;
     }

     UI32 numberOfResults = pResults->size ();

     //Make sure that there is only one cluster
     if (numberOfResults>1)
     {
	 trace (TRACE_LEVEL_FATAL, string ("CentralClusterConfigGetDebugInfoWorker::getPrincipalNodeInfoStep : There can only be one cluster in the system.  Some thing went wrong.  We obtained ") + numberOfResults + string (" of clusters"));
	 waveAssert (false, __FILE__, __LINE__);

         WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
	 pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
	 return;
     }

     //the vector should have one element for cluster MO
     if (0== numberOfResults)
     {
	 trace (TRACE_LEVEL_DEBUG, " CentralClusterConfigGetDebugInfoWorker::getPrincipalNodeInfoStep: There is no Cluster Created");
	 pClusterObjectManagerGetClusterInfoMsg->setClusterCreated(0);
         WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
	 pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
	 return;
     }

     //Pointer to cluster MO
     PrismCluster* pPrismCluster = (dynamic_cast<PrismCluster *> ((*pResults)[0]));

     waveAssert(NULL != pPrismCluster,__FILE__,__LINE__);

     //Cluster related info
     pClusterObjectManagerGetClusterInfoMsg->setClusterCreated(true);

     //IP
     string nodeIpAddress   = pPrismCluster->getPrimaryIpAddress();
     pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodeIpAddress(nodeIpAddress);

     //Port
     UI32 nodePort = pPrismCluster->getPrimaryPort();
     pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodePort(nodePort);

     //LocationId
     LocationId nodeLocationId = pPrismCluster->getPrimaryLocationId();
     pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodeLocationId(nodeLocationId);

     //Generic Status
     pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodeGenericStatus
	 (pPrismCluster->getGenericStatus());

     //Specific Status
     pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodeSpecificStatus
	 (pPrismCluster->getSpecificStatus());

     //Number of secondary nodes
     UI32 numSecondaryNodes = pPrismCluster->getSecondaryNodes().size();
     pClusterObjectManagerGetClusterInfoMsg->setNSecondaryNodes(numSecondaryNodes);

     tracePrintf (TRACE_LEVEL_DEVEL, 
	    " CentralClusterConfigGetDebugInfoWorker::getPrincipalNodesInfoStep:number of secondary nodes: %d",numSecondaryNodes);

     //pResults points to vector created as a
     //result of the query to the database. So it is being
     // released.

     //Release the memory pointed to by pResults
     WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
     trace (TRACE_LEVEL_DEVEL, 
	    " CentralClusterConfigGetDebugInfoWorker::getPrincipalNodesInfoStep:End");

     pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
     return;
}

/// Name
/// getSecondaryNodeInfoStep
/// Description
/// packs  secondary node information into ClusterConfigObjectManagerGetClusterInfoMessage
/// Input
/// WaveLinearSequencerContext : Used by the f/w
/// Output
/// none
/// Return
/// none

void CentralClusterConfigGetDebugInfoWorker::getSecondaryNodesInfoStep(WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
     trace (TRACE_LEVEL_DEVEL, 
	    " CentralClusterConfigGetDebugInfoWorker::getSecondaryNodesInfoStep:Begin");

     ClusterConfigObjectManagerGetClusterInfoMessage* pClusterObjectManagerGetClusterInfoMsg = dynamic_cast<ClusterConfigObjectManagerGetClusterInfoMessage*>(pWaveLinearSequencerContext->getPWaveMessage());

     waveAssert(NULL != pClusterObjectManagerGetClusterInfoMsg,__FILE__,__LINE__);
     //Populate the secondary Node vectors
     vector<WaveManagedObject *> *pResults = querySynchronously (WaveNode::getClassName ());
     waveAssert (NULL != pResults, __FILE__, __LINE__);
     UI32 nNodes = pResults->size();

     //Check if the number of secondary nodes from the Cluster MO pPrismCluster
     //matches the number of secondary wave nodes obtained directly from the 
     // dataabse.If not bail out.

     tracePrintf(TRACE_LEVEL_DEVEL," CentralClusterConfigGetDebugInfoWorker::getSecondaryNodesInfoStep:Secondary Nodes from Cluster MO: %d, Total Nodes from DB: %d",pClusterObjectManagerGetClusterInfoMsg->getNSecondaryNodes(),nNodes);
     for(UI32 i=0;i<nNodes;++i) 
     {

	 //Note that pResults points to a vector that has all the nodes 
	 //including the principal.
	 WaveNode*  pNode= dynamic_cast<WaveNode *> ((*pResults)[i]);
         waveAssert (NULL!= pNode,__FILE__,__LINE__);

	 string secondaryNodeIpAddress = pNode->getIpAddress();
	 UI32   secondaryNodePort = pNode->getPort();
	 LocationId   secondaryNodeLocationId = pNode->getLocationId();
	 ResourceId   secondaryNodeGenericStatus = pNode->getGenericStatus();
	 ResourceId   secondaryNodeSpecificStatus = pNode->getSpecificStatus();

	 //skip the principal node
	 if(pClusterObjectManagerGetClusterInfoMsg->getPrimaryNodeIpAddress() == secondaryNodeIpAddress &&
	    pClusterObjectManagerGetClusterInfoMsg->getPrimaryNodePort() == secondaryNodePort) 
	 {
            pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodeGenericStatus(secondaryNodeGenericStatus);
	    pClusterObjectManagerGetClusterInfoMsg->setPrimaryNodeSpecificStatus(secondaryNodeSpecificStatus);
	     continue;
	 }

	 pClusterObjectManagerGetClusterInfoMsg->setSecondaryNodeDebugInfo(secondaryNodeIpAddress,
									   secondaryNodePort,
									   secondaryNodeLocationId,
									   secondaryNodeGenericStatus,
									   secondaryNodeSpecificStatus);
     }

     //Release the memory pointed to by pResults
     WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
     trace (TRACE_LEVEL_DEVEL, 
	    " CentralClusterConfigGetDebugInfoWorker::getSecondaryNodesInfoStep:End");
         pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
     return;
}   



}


