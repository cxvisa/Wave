/**
 *@file DistributedDebugGlobalObjectManager.h 
 * Copyright (C) 2010 BrocadeCommunications Systems,Inc.
 * All rights reserved.
 * Description: This file declares the
 *              class which is responsible for sending debug
 *              queries and putting together all the responses
 *              
 * 
 * Author :     Aashish Akhouri 
 * Date :       06/18/2011 
 */




#ifndef DISTRIBUTEDDEBUGGLOBALOBJECTMANAGER_H
#define DISTRIBUTEDDEBUGGLOBALOBJECTMANAGER_H


#include "Framework/DistributedDebugInfrastructure/DistributedDebugInfrastructureMessages.h"
#include "Framework/ObjectModel/WaveObjectManager.h"



namespace WaveNs
{



class DistributedDebugGlobalObjectManager : public WaveObjectManager
{
public:

	        static  string          getClassName ();
                static  WaveServiceId  getWaveServiceId ();
                static  string          getPrismServiceName ();                
                static  DistributedDebugGlobalObjectManager *getInstance ();

                void  runDebugScriptMessageHandler  (RunDebugScriptMessage* pRunDebugScriptMessage);

private:
                DistributedDebugGlobalObjectManager ();
	        virtual ~DistributedDebugGlobalObjectManager ();

                virtual PrismMessage *createMessageInstance    (const UI32 &operationCode);

                void sendDebugScriptToAllNodesStep (PrismLinearSequencerContext* pRunDebugScriptMessageHandlerContext);

                void sendDebugScriptToAllNodesCallback (WaveSendToClusterContext *pWaveSendToClusterContext);
};

}

#endif
