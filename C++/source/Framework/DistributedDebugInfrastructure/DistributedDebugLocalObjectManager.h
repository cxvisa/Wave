/**
 *@file DistributedDebugLocalObjectManager.h 
 * Copyright (C) 2010 BrocadeCommunications Systems,Inc.
 * All rights reserved. Description: This file declares the
 *              class which is responsible for sending debug
 *              queries and putting together all the responses
 *              
 * 
 * Author :     Aashish Akhouri 
 * Date :       06/18/2011 
 */
#ifndef DISTRIBUTEDDEBUGLOCALOBJECTMANAGER_H
#define DISTRIBUTEDDEBUGLOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
namespace WaveNs
{


class WaveSynchronousLinearSequencerContext;
class RunDebugScriptOnClusterMemberMessage;

class DistributedDebugLocalObjectManager : public WaveLocalObjectManager
{
    public:
	static DistributedDebugLocalObjectManager       *getInstance                  ();
        static WaveServiceId                            getWaveServiceId                         (); 

        static string   getServiceName ();


    private:
                                   DistributedDebugLocalObjectManager                                      ();
    virtual                       ~DistributedDebugLocalObjectManager                                      ();


    virtual WaveMessage *createMessageInstance    (const UI32 &operationCode);


              void executeScriptStep (WaveSynchronousLinearSequencerContext *pRunDebugScriptMessageHandlerContext);

              void  runDebugScriptOnClusterMemberMessageHandler(RunDebugScriptOnClusterMemberMessage*  pRunDebugScriptOnClusterMemberMessage);

    // Now the data members

 
};

}

#endif
