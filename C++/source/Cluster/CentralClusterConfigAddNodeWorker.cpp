/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 *            Himanshu Varshney                                            *
 ***************************************************************************/

#include "Cluster/CentralClusterConfigAddNodeWorker.h"
#include "Cluster/CentralClusterConfigObjectManager.h"
#include "Cluster/ClusterMessages.h"
#include "Cluster/ClusterTypes.h"
#include "Cluster/Local/WaveNode.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Cluster/WaveCluster.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"

namespace WaveNs
{

CentralClusterConfigAddNodeWorker::CentralClusterConfigAddNodeWorker (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager)
    : WaveWorker (pCentralClusterConfigObjectManager)
{
    addOperationMap (CLUSTER_ADD_NODE, reinterpret_cast<WaveMessageHandler> (&CentralClusterConfigAddNodeWorker::addNodeMessageHandler));
}

CentralClusterConfigAddNodeWorker::~CentralClusterConfigAddNodeWorker ()
{
}

WaveMessage *CentralClusterConfigAddNodeWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case CLUSTER_ADD_NODE :
            pWaveMessage = new ClusterObjectManagerAddNodeMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void CentralClusterConfigAddNodeWorker::addNodeMessageHandler (ClusterObjectManagerAddNodeMessage *pClusterObjectManagerAddNodeMessage)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigAddNodeWorker::addNodeMessaheHandler : Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigAddNodeWorker::addNodeValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigAddNodeWorker::addNodeRequestFrameworkToAddNodeStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigAddNodeWorker::addNodeCommitStep),
//        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigAddNodeWorker::addNodeStartHeartBeatsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigAddNodeWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&CentralClusterConfigAddNodeWorker::waveLinearSequencerFailedStep)
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pClusterObjectManagerAddNodeMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0])); 
//    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();

}

void CentralClusterConfigAddNodeWorker::addNodeValidateStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigAddNodeWorker::addNodeValidateStep : starting ...");

    ClusterObjectManagerAddNodeMessage *pClusterObjectManagerAddNodeMessage = reinterpret_cast<ClusterObjectManagerAddNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    string                               nodeName;
    UI32                                 nodePort;
    UI32                                 i, j;
    WaveNode                            *pNode    = NULL;
    UI32                                 currentTotalNodes;
    UI32                                 NewNodes;
    vector<string>                       NodeNames;
    vector<UI32>                         NodePorts;
    UI32                                 NodeSize;

    // Check if cluster is already created and reject if it is not created

    vector<WaveManagedObject *> *pResults = querySynchronously (WaveCluster::getClassName ());
    
    waveAssert (NULL != pResults, __FILE__, __LINE__);

    if (NULL == pResults)
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }
    UI32 numberOfResults = pResults->size();
    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);


    if (1 < numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("CentralClusterConfigAddNodeWorker::AddNodeValidateStep : There can only be one cluster in the system.  Some thing went wrong.  We obtained ") + numberOfResults + string (" of clusters"));
        waveAssert (false, __FILE__, __LINE__);

        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (1 != numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigAddNodeWorker::AddNodeValidateStep : There is no Cluster Created");

        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR_CLUSTER_VALIDATION_FAILED);
        return;
    }

    if (1 == numberOfResults)
    {
        // Validate the node name and port number, it should be same as any of current node;
        pResults = querySynchronously (WaveNode::getClassName ());

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        NewNodes = pClusterObjectManagerAddNodeMessage->getNSecondaryNodes ();

        currentTotalNodes = pResults->size ();

        for (j = 0; j < NewNodes; j++)
        {
            nodeName = pClusterObjectManagerAddNodeMessage->getSecondaryNodeName (j);
            nodePort = pClusterObjectManagerAddNodeMessage->getSecondaryNodePort (j);

            NodeNames.push_back (nodeName);
            NodePorts.push_back (nodePort);

            for (i = 0; i < currentTotalNodes; i++)
            {
                pNode = dynamic_cast<WaveNode *> ((*pResults)[i]);
        
                if (NULL == pNode)
                {
                    trace (TRACE_LEVEL_FATAL, "CentralClusterConfigAddNodeWorker::AddNodeValidateStep: WaveNode result entry found NULL");
                    waveAssert (false, __FILE__, __LINE__);
                    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
                    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
                    return;
                }

                if ((((pNode->getIpAddress ()) ==  nodeName) && ((pNode->getPort ()) ==  nodePort)) ||
                    ("127.0.0.1" == nodeName) ||
                    ("" == nodeName) ||
                    (1024 > nodePort))
                {
                    //Invalid Node Name or port
                    trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::AddNodeValidateStep: Invalid Node Name/ port");
        		    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
                    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
                    return;
                }

            }
        // Check if any new node is duplicate of previous new node
            NodeSize = NodeNames.size ();

            for (i = 0; i < (NodeSize - 1); i++)
            {
                if (NodeNames[i] == nodeName && NodePorts[i] == nodePort)
                {
                    trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::AddNodeValidateStep: Trying to add Duplicate Node");

		    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
                    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
                    return;
                }

            }
        }
    } 
   
    //Validated the ip and port name of secondary node
    //delete the vector and node and proceed to next step
    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pResults);
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}


void CentralClusterConfigAddNodeWorker::addNodeRequestFrameworkToAddNodeStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    ClusterObjectManagerAddNodeMessage             *pClusterObjectManagerAddNodeMessage             = reinterpret_cast<ClusterObjectManagerAddNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage = new FrameworkObjectManagerAddNodesToClusterMessage ();
    UI32                                            noNewNodes                                      = pClusterObjectManagerAddNodeMessage->getNSecondaryNodes ();
    ResourceId                                      status                                          = WAVE_MESSAGE_SUCCESS;
    UI32                                            i;
    string                                          newNode;
    UI32                                            newNodePort;

    /* Inform Framework that we got a message to add new nodes */

    for (i = 0; i < noNewNodes; i++)
    {
        newNode     = pClusterObjectManagerAddNodeMessage->getSecondaryNodeName (i);
        newNodePort = pClusterObjectManagerAddNodeMessage->getSecondaryNodePort (i);

        pFrameworkObjectManagerAddNodesToClusterMessage->addNewNodeIpAddressAndPort (newNode, newNodePort);
    }

    pFrameworkObjectManagerAddNodesToClusterMessage->setIsAddNodeForSpecialCaseFlag (pClusterObjectManagerAddNodeMessage->getIsAddNodeForSpecialCaseFlag ());

    vector<string> filenamesToSync ;
    pClusterObjectManagerAddNodeMessage->getFilenamesToSync ( filenamesToSync );
    pFrameworkObjectManagerAddNodesToClusterMessage->setFilenamesToSync ( filenamesToSync );
    filenamesToSync.clear();

    status = send (pFrameworkObjectManagerAddNodesToClusterMessage, reinterpret_cast<WaveMessageResponseHandler> (&CentralClusterConfigAddNodeWorker::addNodeRequestFrameworkToAddNodeCallBack), pWaveLinearSequencerContext);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "CentralClusterConfigAddNodeWorker::createClusterRequestFrameworkToAddNodeStep : Could not request Framework For Adding Nodes.  Status " + FrameworkToolKit::localize (status));

        pWaveLinearSequencerContext->executeNextStep (status);
    }

}

void CentralClusterConfigAddNodeWorker::addNodeRequestFrameworkToAddNodeCallBack (FrameworkStatus frameworkStatus, FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage, void *pContext)
{
    trace (TRACE_LEVEL_DEVEL, "CentralClusterConfigAddNodeWorker::createClusterRequestFrameworkToAddNodeCallback : Entering ...");

    WaveLinearSequencerContext              *pWaveLinearSequencerContext         = reinterpret_cast<WaveLinearSequencerContext *> (pContext);

    ClusterObjectManagerAddNodeMessage       *pClusterObjectManagerAddNodeMessage  = reinterpret_cast<ClusterObjectManagerAddNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    ResourceId                                status                               = WAVE_MESSAGE_SUCCESS;
    ResourceId                                completionStatus                     = WAVE_MESSAGE_SUCCESS;
    UI32                                      i                                    = 0;
    string                                    newNode;
    UI32                                      newNodePort;
    UI32                                      noNewNodes                            = pClusterObjectManagerAddNodeMessage->getNSecondaryNodes ();
    
    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        status = frameworkStatus;
    }
    else
    {
        completionStatus = pFrameworkObjectManagerAddNodesToClusterMessage->getCompletionStatus();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            status = completionStatus;
        }
    }

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, string ("CentralClusterConfigAddNodeWorker::processFrameworkAddNodeReply : FrameworkStatus : ") + frameworkStatus + string (", Message Status : ") + completionStatus);

        for (i = 0; i < noNewNodes; i++)
        {
            newNode     = pClusterObjectManagerAddNodeMessage->getSecondaryNodeName (i);
            newNodePort = pClusterObjectManagerAddNodeMessage->getSecondaryNodePort (i);
            pClusterObjectManagerAddNodeMessage->setNodeStaus (newNode, newNodePort, status);
        }
    }
    else
    {
        for (i = 0; i < noNewNodes; i++)
        {
            newNode     = pClusterObjectManagerAddNodeMessage->getSecondaryNodeName (i);
            newNodePort = pClusterObjectManagerAddNodeMessage->getSecondaryNodePort (i);
            pClusterObjectManagerAddNodeMessage->setNodeStaus (newNode, newNodePort, pFrameworkObjectManagerAddNodesToClusterMessage->getNewNodeStatus (newNode, newNodePort));
        }
    }

    delete pFrameworkObjectManagerAddNodesToClusterMessage;

    pWaveLinearSequencerContext->executeNextStep (status);
}

void CentralClusterConfigAddNodeWorker::addNodeCommitStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    ClusterObjectManagerAddNodeMessage *pClusterObjectManagerAddNodeMessage = reinterpret_cast<ClusterObjectManagerAddNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    string                                    newNode;
    UI32                                      newNodePort;
    ResourceId                                newNodeStatus;
    UI32                                      noNewNode                     = pClusterObjectManagerAddNodeMessage->getNSecondaryNodes ();
    WaveCluster                             *pWaveCluster;
    UI32                                      i;    
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS; 

    vector<WaveManagedObject *>              *pWaveClusterResults          = querySynchronously (WaveCluster::getClassName ());
    
    if (NULL == pWaveClusterResults)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigAddNodeWorker::addNodeCommitStep : WaveCluster Query Returns NULL");
        waveAssert (false, __FILE__, __LINE__);
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveClusterResults);
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    UI32                                      numberOfResults               = pWaveClusterResults->size ();
  
    if (1 < numberOfResults)
    {
        trace (TRACE_LEVEL_FATAL, string ("CentralClusterConfigAddNodeWorker::AddNodeValidateStep : There can only be one cluster in the system.          Some thing went wrong.  We obtained ") + numberOfResults + string (" of clusters"));
        waveAssert (false, __FILE__, __LINE__);
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveClusterResults);
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (1 != numberOfResults)
    {
        trace (TRACE_LEVEL_WARN, "CentralClusterConfigAddNodeWorker::addNodeCommitStep : There is no Cluster, Cluster is Deleted. Can Not Continue With Add Node");

        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    pWaveCluster = (reinterpret_cast<WaveCluster *> ((*pWaveClusterResults)[0]));

    startTransaction();

    vector<vector<WaveManagedObject *> *> waveNodeVectors;
    for (i = 0; i < noNewNode; i++)
    {
        newNode       = pClusterObjectManagerAddNodeMessage->getStatusNodeName   (i);
        newNodePort   = pClusterObjectManagerAddNodeMessage->getStatusNodePort   (i);
        newNodeStatus = pClusterObjectManagerAddNodeMessage->getStatusNodeStatus (i);

        if (WAVE_MESSAGE_SUCCESS == newNodeStatus)
        {
            WaveManagedObjectSynchronousQueryContext queryContext (WaveNode::getClassName ());
            
            queryContext.addAndAttribute (new AttributeString (newNode,     "ipAddress"));
            queryContext.addAndAttribute (new AttributeUI32   (newNodePort, "port"));
            
            vector<WaveManagedObject *>   *pResults = querySynchronously (&queryContext);

            waveAssert (NULL != pResults, __FILE__, __LINE__);

            numberOfResults = pResults->size ();
            
            waveAssert (1 == numberOfResults, __FILE__, __LINE__);
            
            WaveNode *pWaveNode = dynamic_cast<WaveNode *> ((*pResults)[0]);
	    waveAssert( NULL != pWaveNode, __FILE__, __LINE__);
   
            updateWaveManagedObject (pWaveCluster); 
            pWaveCluster->addSecondaryNode (pWaveNode->getObjectId ());
            waveNodeVectors.push_back(pResults);
        }
    }

    status = commitTransaction ();

    if (FRAMEWORK_SUCCESS != status)
    {
        trace (TRACE_LEVEL_FATAL, "CentralClusterConfigAddNodeWorker::addNodeCommitStep : Failed to Persist the configuration.  Cannot Continue.  Status : " + FrameworkToolKit::localize (status));
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        // Reset the status so that it can be used to pass on to the pWaveLinearSequencerContext.

        status = WAVE_MESSAGE_SUCCESS;
    }

    UI32 numVectors = waveNodeVectors.size();

    for (i = 0; i < numVectors; ++i)
    {
        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(waveNodeVectors[i]);
    }

    
    WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(pWaveClusterResults);
    pWaveLinearSequencerContext->executeNextStep (status);
}

void CentralClusterConfigAddNodeWorker::addNodeStartHeartBeatsStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    ClusterObjectManagerAddNodeMessage *pClusterObjectManagerAddNodeMessage = reinterpret_cast<ClusterObjectManagerAddNodeMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    UI32                                      noNewNode                     = pClusterObjectManagerAddNodeMessage->getNSecondaryNodes ();
    ResourceId                                status                        = WAVE_MESSAGE_SUCCESS;
    string                                    newNode;
    UI32                                      newNodePort;
    ResourceId                                newNodeStatus;
    UI32                                      i;

    for (i = 0; i < noNewNode; i++)
    {
        newNode       = pClusterObjectManagerAddNodeMessage->getStatusNodeName   (i);
        newNodePort   = pClusterObjectManagerAddNodeMessage->getStatusNodePort   (i);
        newNodeStatus = pClusterObjectManagerAddNodeMessage->getStatusNodeStatus (i);

        if (WAVE_MESSAGE_SUCCESS == newNodeStatus)
        {
            StartHeartBeatMessage *pMessage = new StartHeartBeatMessage ();

            pMessage->setDstIpAddress                 (newNode);
            pMessage->setDstPortNumber                (newNodePort);
            pMessage->setHeartBeatInterval            (CENTERAL_CLUSTER_HEART_BEAT_PERIOD);
            pMessage->setHeartBeatFailureThreshold    (MAX_LOST_HEARTBEAT);

            status = sendSynchronously (pMessage);

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "CentralClusterConfigAddNodeWorker::addNodeClusterStartHeartBeatsStep : Could not start heart beating with Node : " + newNode + string (", Port : ") + newNodePort + string (", Status = ") + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                status = pMessage->getCompletionStatus ();

                if (WAVE_MESSAGE_SUCCESS != status)
                {
                    trace (TRACE_LEVEL_FATAL, "CentralClusterConfigAddNodeWorker::addNodeStartHeartBeatsStep : Could not start heart beating with Node : " + newNode + string (", Port : ") + newNodePort + string (", Completion Status = ") + FrameworkToolKit::localize (status));                     waveAssert (false, __FILE__, __LINE__);
                }
            }

            delete pMessage;
        }
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}

