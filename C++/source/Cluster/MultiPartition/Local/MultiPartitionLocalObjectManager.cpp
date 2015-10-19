/*********************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                     *
 *   All rights reserved.                                            *
 *   Author : Jayaraman Iyer                                         *
 *********************************************************************/

#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalObjectManager.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalMessages.h"
#include "Cluster/MultiPartition/Local/MultiPartitionCleanupAgent.h"
#include "Cluster/MultiPartition/Local/MultiPartitionLocalTypes.h"
#include "WaveResourceIds.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace WaveNs
{

    MultiPartitionLocalObjectManager::MultiPartitionLocalObjectManager ()  : WaveLocalObjectManager  (getServiceName ())
    {
        addOperationMap (MULTI_PARTITION_DELETE_LOCAL_PARTITION_INSTANCE,  reinterpret_cast<WaveMessageHandler> (&MultiPartitionLocalObjectManager::tenancyDeleteMessageHandler));    
    }

    MultiPartitionLocalObjectManager::~MultiPartitionLocalObjectManager ()
    {
    }

    MultiPartitionLocalObjectManager  *MultiPartitionLocalObjectManager::getInstance()
    {
        static MultiPartitionLocalObjectManager *pLocalObjectManager = new MultiPartitionLocalObjectManager ();

        WaveNs::waveAssert (NULL != pLocalObjectManager, __FILE__, __LINE__);

        return (pLocalObjectManager);
    }

    string  MultiPartitionLocalObjectManager::getServiceName()
    {
        return ("Multi Partition Local Service");
    }

    WaveServiceId  MultiPartitionLocalObjectManager::getWaveServiceId()
    {
        return ((getInstance ())->getServiceId ());
    }

    WaveMessage *MultiPartitionLocalObjectManager::createMessageInstance (const UI32 &operationCode)
    {
        WaveMessage *pWaveMessage = NULL;

        switch (operationCode)
        {
            case MULTI_PARTITION_DELETE_LOCAL_PARTITION_INSTANCE :
                 pWaveMessage = new MultiPartitionDeleteLocalPartitionMessage ();
                 waveAssert (NULL != pWaveMessage , __FILE__, __LINE__);
                 break;

            default :
                pWaveMessage = NULL;
        }

        return (pWaveMessage);
    }

    void  MultiPartitionLocalObjectManager::tenancyDeleteMessageHandler( MultiPartitionDeletePartitionMessage *pMultiPartitionDeletePartitionMessage)
    {
     // Validations and Queries should go here

          WaveSynchronousLinearSequencerStep  sequencerSteps[] =
          {
               reinterpret_cast<WaveSynchronousLinearSequencerStep>(&MultiPartitionLocalObjectManager::validateInputs),
               // reinterpret_cast<WaveSynchronousLinearSequencerStep>(&MultiPartitionLocalObjectManager::prismSynchronousLinearSequencerStartTransactionStep),
               reinterpret_cast<WaveSynchronousLinearSequencerStep>(&MultiPartitionLocalObjectManager::processPartitionObjectCleanup),

               // reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionLocalObjectManager::prismSynchronousLinearSequencerCommitTransactionStep),
               reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionLocalObjectManager::prismSynchronousLinearSequencerSucceededStep),
               reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionLocalObjectManager::prismSynchronousLinearSequencerFailedStep)

          };

          WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (pMultiPartitionDeletePartitionMessage, this,
                                                                                                       sequencerSteps, 
                                                                                                       sizeof (sequencerSteps) /sizeof (sequencerSteps[0]));

          WaveNs::waveAssert (NULL != pWaveSynchronousLinearSequencerContext, __FILE__, __LINE__);
        
          pWaveSynchronousLinearSequencerContext->execute ();
     }

     ResourceId   MultiPartitionLocalObjectManager::validateInputs (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext) 
     {
         ResourceId status = WAVE_MESSAGE_SUCCESS;

         tracePrintf(TRACE_LEVEL_INFO,  "MultiPartitionLocalObjectManager::validateInputs called " );

         MultiPartitionDeleteLocalPartitionMessage   *pDeleteMTMessage = reinterpret_cast<MultiPartitionDeleteLocalPartitionMessage *> (pWaveSynchronousLinearSequencerContext->getPWaveMessage ());
         WaveNs::waveAssert (NULL != pDeleteMTMessage, __FILE__, __LINE__);
         
         do {
                // TODO: Add any checks here. 
         } while(0);

         if (true == pDeleteMTMessage->getIsPartialCleanup ())
         {
             ResourceId partialCleanupTag = pDeleteMTMessage->getPartialCleanupTag ();

             trace (TRACE_LEVEL_INFO, string ("MultiPartitionLocalObjectManager::validateInputs : PartialCleanup : partialCleanupTag [") + FrameworkToolKit::localizeToSourceCodeEnum (partialCleanupTag) + string ("]"));
         }
         else
         {
             trace (TRACE_LEVEL_INFO, string ("MultiPartitionLocalObjectManager::validateInputs : Non-partial Cleanup (delete)."));
         }

         return (status);     
     }

     ResourceId   MultiPartitionLocalObjectManager::processPartitionObjectCleanup (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext) 
     {
         ResourceId status = WAVE_MESSAGE_SUCCESS;

         tracePrintf(TRACE_LEVEL_INFO,  "MultiPartitionLocalObjectManager::processPartitionObjectCleanup  called. " );

         MultiPartitionDeleteLocalPartitionMessage   *pDeleteMTMessage = reinterpret_cast<MultiPartitionDeleteLocalPartitionMessage *> (pWaveSynchronousLinearSequencerContext->getPWaveMessage ());
         WaveNs::waveAssert (NULL != pDeleteMTMessage, __FILE__, __LINE__);

         UI32 senderServiceId   = pDeleteMTMessage->getSenderServiceId ();
         string partitionName      = pDeleteMTMessage->getPartitionName();

         ObjectId ownerPartitionObjectId   = pDeleteMTMessage->getOwnerPartitionManagedObjectId (); 

         MultiPartitionCleanupAgent  *pMultiPartitionCleanupAgent  = new MultiPartitionCleanupAgent(this, partitionName, senderServiceId , ownerPartitionObjectId);
         waveAssert(NULL != pMultiPartitionCleanupAgent, __FILE__ , __LINE__);

         if (true == pDeleteMTMessage->getIsPartialCleanup ())
         {
             ResourceId partialCleanupTag = pDeleteMTMessage->getPartialCleanupTag ();
             pMultiPartitionCleanupAgent->setPartialCleanupTag (partialCleanupTag);
         }

         tracePrintf(TRACE_LEVEL_INFO,  "MultiPartitionLocalObjectManager::processPartitionObjectCleanup: Before CleanupAgent is called. " );
         status = pMultiPartitionCleanupAgent->execute();
         tracePrintf(TRACE_LEVEL_INFO,  "MultiPartitionLocalObjectManager::processPartitionObjectCleanup: After  CleanupAgent is called. " );

         delete pMultiPartitionCleanupAgent;

         return (status);     
     }

}

