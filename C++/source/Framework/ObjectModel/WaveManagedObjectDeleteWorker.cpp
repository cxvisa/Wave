/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectDeleteWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectDeleteContext.h"
#include "Framework/Types/Types.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "ManagementInterface/ClientInterface/UnifiedClientDeleteMessage.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectRelationalMapping/OrmRelation.h"
#include "Framework/ObjectRelationalMapping/ManagedObjectSchemaInfoRepository.h"
#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeTypes.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/ObjectModel/WaveLocalManagedObjectBase.h"
#include <algorithm>

using namespace std;

namespace WaveNs
{

WaveManagedObjectDeleteWorker::WaveManagedObjectDeleteWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECT, reinterpret_cast<WaveMessageHandler> (&WaveManagedObjectDeleteWorker::deleteHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECTS, reinterpret_cast<WaveMessageHandler> (&WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDelete));
}

WaveManagedObjectDeleteWorker::~WaveManagedObjectDeleteWorker ()
{
}

WaveMessage *WaveManagedObjectDeleteWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECT :
            pWaveMessage = new WaveObjectManagerDeleteWaveManagedObjectMessage;
            break;

        case WAVE_OBJECT_MANAGER_DELETE_MANAGED_OBJECTS :
            pWaveMessage = new WaveObjectManagerDeleteWaveManagedObjectsMessage;
            break;


        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}


void WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDelete (WaveObjectManagerDeleteWaveManagedObjectsMessage *pWaveObjectManagerDeleteWaveManagedObjectsMessage)
{
    trace(TRACE_LEVEL_DEVEL,"WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDelete entering ..");

    WaveLinearSequencerStep sequencerStepsForMultipleDelete [] = 
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::sendAsynchronousDeleteMessagesStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerFailedStep),
    };
    
    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContextForMultipleDelete = new WaveManagedObjectDeleteContext (pWaveObjectManagerDeleteWaveManagedObjectsMessage, this, sequencerStepsForMultipleDelete, sizeof (sequencerStepsForMultipleDelete) / sizeof (sequencerStepsForMultipleDelete[0])); 

    pWaveManagedObjectDeleteContextForMultipleDelete->start   ();
}

void WaveManagedObjectDeleteWorker::sendAsynchronousDeleteMessagesStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContextForMultipleDelete)
{
    trace(TRACE_LEVEL_DEVEL,"WaveManagedObjectDeleteWorker::sendAsynchronousDeleteMessagesStep entering ..");

    WaveObjectManagerDeleteWaveManagedObjectsMessage *pWaveObjectManagerDeleteWaveManagedObjectsMessage = reinterpret_cast<WaveObjectManagerDeleteWaveManagedObjectsMessage *> (pWaveManagedObjectDeleteContextForMultipleDelete->getPWaveMessage ());

    vector<ObjectId> managedObjectIdVector = pWaveObjectManagerDeleteWaveManagedObjectsMessage->getManagedObjectsIdVector();
    WaveObjectManagerDeleteWaveManagedObjectMessage *pWaveObjectManagerDeleteWaveManagedObjectMessage = NULL;

    ++(*pWaveManagedObjectDeleteContextForMultipleDelete);

    trace(TRACE_LEVEL_INFO,string("WaveManagedObjectDeleteWorker::sendAsynchronousDeleteMessagesStep : managedObjectIdVector.size = ")+managedObjectIdVector.size());

    for (UI32 i = 0; i < managedObjectIdVector.size(); i++)
    {
       pWaveObjectManagerDeleteWaveManagedObjectMessage = new WaveObjectManagerDeleteWaveManagedObjectMessage (getServiceId()); 

       pWaveObjectManagerDeleteWaveManagedObjectMessage->setOperateOnWaveManagedObjectId (managedObjectIdVector[i]);
       pWaveObjectManagerDeleteWaveManagedObjectMessage->setAttributeValues              (pWaveObjectManagerDeleteWaveManagedObjectsMessage->getAttributeValues());
       pWaveObjectManagerDeleteWaveManagedObjectMessage->setIsMO                         (pWaveObjectManagerDeleteWaveManagedObjectsMessage->getIsMO ());
       pWaveObjectManagerDeleteWaveManagedObjectMessage->setParentObjectId               (pWaveObjectManagerDeleteWaveManagedObjectsMessage->getParentObjectId ());
       pWaveObjectManagerDeleteWaveManagedObjectMessage->setChildUserTag                 (pWaveObjectManagerDeleteWaveManagedObjectsMessage->getChildUserTag ());
       pWaveObjectManagerDeleteWaveManagedObjectMessage->setConfigReplayInProgressFlag   (pWaveObjectManagerDeleteWaveManagedObjectsMessage->getConfigReplayInProgressFlag ());

       if (0 != (pWaveObjectManagerDeleteWaveManagedObjectsMessage->getAttributeNameVectorVector()).size())
       {
           pWaveObjectManagerDeleteWaveManagedObjectMessage->setAttributeNames ((pWaveObjectManagerDeleteWaveManagedObjectsMessage->getAttributeNameVectorVector())[i]);     
       }
       else
       {
           pWaveObjectManagerDeleteWaveManagedObjectMessage->setAttributeUserTags ((pWaveObjectManagerDeleteWaveManagedObjectsMessage->getAttributeUserTagVectorVector())[i]);
       }

       WaveMessageStatus sendStatus = send (pWaveObjectManagerDeleteWaveManagedObjectMessage, reinterpret_cast<WaveMessageResponseHandler> (&WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDeleteCallback), pWaveManagedObjectDeleteContextForMultipleDelete);

       if (WAVE_MESSAGE_SUCCESS == sendStatus)
       {
           ++(*pWaveManagedObjectDeleteContextForMultipleDelete);
       }
       else
       {
           trace(TRACE_LEVEL_ERROR,"WaveManagedObjectDeleteWorker::sendAsynchronousDeleteMessagesStep : Failed to send message"); 
           pWaveManagedObjectDeleteContextForMultipleDelete->executeNextStep (sendStatus);
       }
    }

    --(*pWaveManagedObjectDeleteContextForMultipleDelete);

    pWaveManagedObjectDeleteContextForMultipleDelete->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDeleteCallback (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void* pCallerContext)
{
    trace (TRACE_LEVEL_DEVEL,"WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDeleteCallback entering ..");

    waveAssert (NULL != pCallerContext, __FILE__, __LINE__);

    ResourceId status           = WAVE_MESSAGE_SUCCESS;
    ResourceId completionStatus = WAVE_MESSAGE_SUCCESS;

    WaveObjectManagerDeleteWaveManagedObjectMessage *pWaveObjectManagerDeleteWaveManagedObjectMessage = reinterpret_cast<WaveObjectManagerDeleteWaveManagedObjectMessage *> (pWaveMessage);

    WaveManagedObjectDeleteContext *pWaveLinearSequencerContext = reinterpret_cast<WaveManagedObjectDeleteContext *> (pCallerContext);
    waveAssert (NULL != pWaveLinearSequencerContext, __FILE__, __LINE__);

    WaveObjectManagerDeleteWaveManagedObjectsMessage *pWaveObjectManagerDeleteWaveManagedObjectsMessage = reinterpret_cast<WaveObjectManagerDeleteWaveManagedObjectsMessage *> (pWaveLinearSequencerContext->getPWaveMessage ()); 

    waveAssert (NULL != pWaveObjectManagerDeleteWaveManagedObjectsMessage, __FILE__, __LINE__);

    //set the partial success flag
    pWaveObjectManagerDeleteWaveManagedObjectsMessage->setIsPropagateErrorCodeNeeded (pWaveObjectManagerDeleteWaveManagedObjectMessage->getIsPropagateErrorCodeNeeded ());
    pWaveObjectManagerDeleteWaveManagedObjectsMessage->setWarningResourceId (pWaveObjectManagerDeleteWaveManagedObjectMessage->getWarningResourceId());

    // copy the propogated status to multiple delete message. 
    pWaveObjectManagerDeleteWaveManagedObjectsMessage->setlocalizedCompletionStatusForStatusPropagationVector (pWaveObjectManagerDeleteWaveManagedObjectMessage->getlocalizedCompletionStatusForStatusPropagationVector ());

    pWaveObjectManagerDeleteWaveManagedObjectsMessage->setcompletionStatusForStatusPropagationVector (pWaveObjectManagerDeleteWaveManagedObjectMessage->getcompletionStatusForStatusPropagationVector ());

    pWaveObjectManagerDeleteWaveManagedObjectsMessage->setlocationsForStatusPropagationVector (pWaveObjectManagerDeleteWaveManagedObjectMessage->getlocationsForStatusPropagationVector ());

    --(*pWaveLinearSequencerContext);

    if (FRAMEWORK_SUCCESS != frameworkStatus)
    {
        status = frameworkStatus;
        trace (TRACE_LEVEL_ERROR,string("WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDeleteCallback : Failed to send the Message : Framework Status : ")+FrameworkToolKit::localize (status));
    }
    else
    {
        completionStatus = pWaveMessage->getCompletionStatus();
        
        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            status = completionStatus;
            trace (TRACE_LEVEL_ERROR,string("WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDeleteCallback : Failed to send the Message : Completion Status : ")+FrameworkToolKit::localize (status));
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL,"WaveManagedObjectDeleteWorker::deleteHandlerForMultipleDeleteCallback : Successfully send the message to the OM");
        }
    }

    if (NULL != pWaveMessage)
    {
        delete pWaveMessage;
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

void WaveManagedObjectDeleteWorker::deleteHandler (WaveObjectManagerDeleteWaveManagedObjectMessage *pWaveObjectManagerDeleteWaveManagedObjectMessage)
{

    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = NULL;

    WaveLinearSequencerStep sequencerStepsForMO[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteValidateManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePostUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::WaveManagedObjectStartTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePreDeleteManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteDeleteManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePostDeleteManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerCommitTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerStep sequencerStepsForLeaf[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteValidateManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::WaveManagedObjectStartTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePreDeleteManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteDeleteManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteUpdateNewAttributeInManagedObject),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePostDeleteManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::commitWaveManagedObjectBeforeUpdatingBackend),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deleteUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::deletePostUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::commitWaveManagedObjectAfterUpdatingBackend),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectDeleteWorker::waveLinearSequencerFailedStep),
    };

    if (pWaveObjectManagerDeleteWaveManagedObjectMessage->getIsMO()) 
    {

        pWaveManagedObjectDeleteContext = new WaveManagedObjectDeleteContext (pWaveObjectManagerDeleteWaveManagedObjectMessage, this, sequencerStepsForMO, sizeof (sequencerStepsForMO) / sizeof (sequencerStepsForMO[0]));
    } 
    else 
    {
        pWaveManagedObjectDeleteContext = new WaveManagedObjectDeleteContext (pWaveObjectManagerDeleteWaveManagedObjectMessage, this, sequencerStepsForLeaf, sizeof (sequencerStepsForLeaf) / sizeof (sequencerStepsForLeaf[0]));
    }

    pWaveManagedObjectDeleteContext->setOperateOnWaveManagedObjectId    (pWaveObjectManagerDeleteWaveManagedObjectMessage->getOperateOnWaveManagedObjectId ());
    pWaveManagedObjectDeleteContext->setAttributeUserTags               (pWaveObjectManagerDeleteWaveManagedObjectMessage->getAttributeUserTags   ());
    pWaveManagedObjectDeleteContext->setAttributeNames                  (pWaveObjectManagerDeleteWaveManagedObjectMessage->getAttributeNames      ());
    pWaveManagedObjectDeleteContext->setAttributeValues                 (pWaveObjectManagerDeleteWaveManagedObjectMessage->getAttributeValues     ());
    pWaveManagedObjectDeleteContext->setNeedToDeleteManagedObject       (pWaveObjectManagerDeleteWaveManagedObjectMessage->getIsMO     ());
    pWaveManagedObjectDeleteContext->setParentObjectId                  (pWaveObjectManagerDeleteWaveManagedObjectMessage->getParentObjectId ());
    pWaveManagedObjectDeleteContext->setChildUserTag                    (pWaveObjectManagerDeleteWaveManagedObjectMessage->getChildUserTag ());
    pWaveManagedObjectDeleteContext->setConfigReplayInProgressFlag      (pWaveObjectManagerDeleteWaveManagedObjectMessage->getConfigReplayInProgressFlag ());

    trace (TRACE_LEVEL_INFO, string ("xml tag: ") + pWaveObjectManagerDeleteWaveManagedObjectMessage->getChildUserTag ());


    pWaveManagedObjectDeleteContext->holdAll ();
    pWaveManagedObjectDeleteContext->start   ();

}

void WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;
    string     className;
    ObjectId operateOnWaveManagedObjectId = pWaveManagedObjectDeleteContext->getOperateOnWaveManagedObjectId ();
    bool       isALocalService = FrameworkToolKit::isALocalService(getServiceId());
    bool       isALocalMO      = false;

    trace(TRACE_LEVEL_INFO,string("WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : For service = ")+FrameworkToolKit::getServiceNameById(getServiceId()));

    if (0 != operateOnWaveManagedObjectId.getClassId ())
    {
        className  = OrmRepository::getTableNameById (operateOnWaveManagedObjectId.getClassId ());
        isALocalMO = OrmRepository::isALocalManagedObject(className);

        trace(TRACE_LEVEL_INFO,string("WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : For ManagedObject = ")+className);
    }     
	else if(isALocalService)
	{
		isALocalMO  = true;
	}

    
    if (!isALocalService && !isALocalMO)
    {
        // Global Service & Global MO    
        pWaveManagedObjectDeleteContext->setIsDatabaseUpdateRequired (true);
        pWaveManagedObjectDeleteContext->setIsBackendUpdateRequired (false);

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : Global Service & Global MO");
    }
    else if(isALocalService && isALocalMO)
    {
        // Local Service Local MO    
        pWaveManagedObjectDeleteContext->setIsDatabaseUpdateRequired (true);
        pWaveManagedObjectDeleteContext->setIsBackendUpdateRequired (true);

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : Local Service Local MO  ");
    }
    else if(isALocalService && !isALocalMO)
    {
        // Local Service Global MO    
        pWaveManagedObjectDeleteContext->setIsDatabaseUpdateRequired (false);
        pWaveManagedObjectDeleteContext->setIsBackendUpdateRequired (true);

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : Local Service Global MO ");
    }
    else
    {
        // Global Service Local MO    
        pWaveManagedObjectDeleteContext->setIsDatabaseUpdateRequired (false);
        pWaveManagedObjectDeleteContext->setIsBackendUpdateRequired (false);

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteQueryManagedObjectStep : Global Service Local MO ");
                         
        waveAssert (false, __FILE__, __LINE__);
    }    

    WaveManagedObject *pOperateOnWaveManagedObject = NULL;

    if (ObjectId::NullObjectId != operateOnWaveManagedObjectId)
    {
        pOperateOnWaveManagedObject = queryManagedObject (operateOnWaveManagedObjectId);
    }

    if (NULL != pOperateOnWaveManagedObject)
    {
        pWaveManagedObjectDeleteContext->setPOperateOnWaveManagedObject (pOperateOnWaveManagedObject);
    }
    
    if (NULL == pOperateOnWaveManagedObject)
    {
        status = WAVE_MANAGED_OBJECT_DELETE_OBJECT_NOT_FOUND;
    }

    pWaveManagedObjectDeleteContext->executeNextStep (status);
    return;
}

void WaveManagedObjectDeleteWorker::WaveManagedObjectStartTransactionStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::WaveManagedObjectStartTransactionStep: Entering ...");
 
    if (!pWaveManagedObjectDeleteContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL , "WaveManagedObjectDeleteWorker::WaveManagedObjectStartTransactionStep : skipping for Local Service & Global MO");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }
 
    waveLinearSequencerStartTransactionStep (pWaveManagedObjectDeleteContext);
}

void WaveManagedObjectDeleteWorker::deleteValidateManagedObjectStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteValidateManagedObjectStep : Entering ...");

    vector<UI32>       attributeUserTags         = pWaveManagedObjectDeleteContext->getAttributeUserTags ();
    vector<string>     attributeNames            = pWaveManagedObjectDeleteContext->getAttributeNames    ();
    vector<string>     attributeValues           = pWaveManagedObjectDeleteContext->getAttributeValues   ();
    UI32               numberOfAttributeUserTags = attributeUserTags.size ();
    UI32               numberOfAttributeNames    = attributeNames.size ();
    UI32               i,j                       = 0;
    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    string             attributeValue;


   // if (false == pWaveManagedObjectDeleteContext->isNeedToDeleteManagedObject ()) 
   // {
        if (NULL != pWaveManagedObject)
        {
            if ((0 != numberOfAttributeUserTags) && (0 != numberOfAttributeNames))
            {
                waveAssert (false, __FILE__, __LINE__);
            }

            waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

            if (0 != numberOfAttributeNames)
            {
                for (i = 0; i < numberOfAttributeNames; i++)
                {
                    string attributeName  = attributeNames[i];

                    waveAssert ("" != attributeName, __FILE__, __LINE__);

                    Attribute *pAttribute = pWaveManagedObject->getAttributeByName (attributeName);

                    waveAssert (NULL != pAttribute, __FILE__, __LINE__);

                    if ((pAttribute->getAttributeType() != AttributeType::AttributeTypeObjectId) && (pAttribute->getAttributeType () != AttributeType::AttributeTypeObjectIdVector))
                    {

                        Attribute *pClonedAttribute = pAttribute->clone ();
    
                        waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

                        //pClonedAttribute->setDefaultValue ();

                        pClonedAttribute->toString (attributeValue);

                        attributeValues.push_back (attributeValue);

                        pWaveManagedObjectDeleteContext->addToAttributeVector (pClonedAttribute);
                    }
                    else
                    {
                        AttributeObjectIdAssociation *pAttributeObjectIdAssociation                 = dynamic_cast <AttributeObjectIdAssociation *> (pAttribute);
                        AttributeObjectIdVectorAssociation *pAttributeObjectIdVectorAssociation     = dynamic_cast <AttributeObjectIdVectorAssociation *> (pAttribute);
                        string childClassName;

                        if (NULL != pAttributeObjectIdAssociation)
                        {
                            childClassName = pAttributeObjectIdAssociation->getAssociatedTo ();
                            //pAttribute->setDefaultValue ();
                        }
                        else
                        {
                            // TODO:Need to Handle the Association Vector.
                            childClassName = pAttributeObjectIdVectorAssociation->getAssociatedTo ();
                        }
                    }
                }

                pWaveManagedObjectDeleteContext->setAttributeValues (attributeValues);
            }
            else
            {
                for (j = 0; j < numberOfAttributeUserTags; j++)
                {
                    UI32   attributeUserTag = attributeUserTags[j];


                    waveAssert (0 != attributeUserTag, __FILE__, __LINE__);

                    Attribute *pAttribute = pWaveManagedObject->getAttributeByUserTag (attributeUserTag);

                    waveAssert (NULL != pAttribute, __FILE__, __LINE__);

                    if ((pAttribute->getAttributeType() != AttributeType::AttributeTypeObjectId) && (pAttribute->getAttributeType () != AttributeType::AttributeTypeObjectIdVector))
                    {
                        Attribute *pClonedAttribute = pAttribute->clone ();

                        waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

                        //pClonedAttribute->setDefaultValue ();

                        pWaveManagedObjectDeleteContext->addToAttributeVector (pClonedAttribute);

                        pClonedAttribute->toString (attributeValue);

                        attributeValues.push_back (attributeValue);
                    }
                    else
                    {
                        AttributeObjectIdAssociation *pAttributeObjectIdAssociation                 = dynamic_cast <AttributeObjectIdAssociation *> (pAttribute);
                        AttributeObjectIdVectorAssociation *pAttributeObjectIdVectorAssociation     = dynamic_cast <AttributeObjectIdVectorAssociation *> (pAttribute);
                        string childClassName;

                        if (NULL != pAttributeObjectIdAssociation)
                        {
                            childClassName = pAttributeObjectIdAssociation->getAssociatedTo ();

                            //pAttribute->setDefaultValue ();
                        }
                        else
                        {
                            childClassName = pAttributeObjectIdVectorAssociation->getAssociatedTo ();
                        }

                    }

                    attributeNames.push_back (pAttribute->getAttributeName ());
                }

                pWaveManagedObjectDeleteContext->setAttributeNames (attributeNames);
                pWaveManagedObjectDeleteContext->setAttributeValues (attributeValues);
            }
          
            if (FrameworkToolKit::isALocalService(getServiceId())) 
            {
                ValidateForDeleteAtThisNodeContext *pValidateForDeleteAtThisNodeContext = new ValidateForDeleteAtThisNodeContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectDeleteWorker::validateForDeleteAtThisNodeCallBack), pWaveManagedObjectDeleteContext); 
                pValidateForDeleteAtThisNodeContext->setAttributeNames      (attributeNames);
                pValidateForDeleteAtThisNodeContext->setAttributeValues     (attributeValues);
                pValidateForDeleteAtThisNodeContext->setAttributeVector     (pWaveManagedObjectDeleteContext->getAttributes ());

                pWaveManagedObject->validateForDeleteAtThisNode (pValidateForDeleteAtThisNodeContext);
            }
            else //TODO validation for global plugin
            {
               ValidateForDeleteAtThisNodeContext *pValidateGlobalForDeleteAtThisNodeContext = new ValidateForDeleteAtThisNodeContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectDeleteWorker::validateForDeleteAtThisNodeCallBack), pWaveManagedObjectDeleteContext);
               pValidateGlobalForDeleteAtThisNodeContext->setAttributeNames      (attributeNames);
               pValidateGlobalForDeleteAtThisNodeContext->setAttributeValues     (attributeValues);
               pValidateGlobalForDeleteAtThisNodeContext->setAttributeVector     (pWaveManagedObjectDeleteContext->getAttributes ());
                               
               pWaveManagedObject->validateGlobalForDeleteAtThisNode (pValidateGlobalForDeleteAtThisNodeContext);        
            }
        }
        else
        {
            pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_ERROR);
            return;
        }
   /* }
    else
    {
      pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }*/
}


void WaveManagedObjectDeleteWorker::validateForDeleteAtThisNodeCallBack (ValidateForDeleteAtThisNodeContext *pValidateForDeleteAtThisNodeContext)
{
    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = reinterpret_cast<WaveManagedObjectDeleteContext *> (pValidateForDeleteAtThisNodeContext->getPCallerContext ());
    ResourceId                                               status = pValidateForDeleteAtThisNodeContext->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR , "WaveManagedObjectDeleteWorker::validateForDeleteAtThisNodeCallBack Validation Fails");

        pWaveManagedObjectDeleteContext->executeNextStep (status);
        return;
    }

    pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveManagedObjectDeleteWorker::deletePreDeleteManagedObjectStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePreDeleteManagedObjectStep : Entering ...");
    
    if (!pWaveManagedObjectDeleteContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePreDeleteManagedObjectStep: skipping for  Local Service & Global MO");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }    

    if (false == pWaveManagedObjectDeleteContext->isNeedToDeleteManagedObject ())
    {
        vector<string>     attributeNames            = pWaveManagedObjectDeleteContext->getAttributeNames ();
        UI32               numberOfAttributeNames    = attributeNames.size ();
        UI32               i;
        WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
 
        /* Manage Context counter to handle multiple Associations */
        ++(*pWaveManagedObjectDeleteContext);
        
        for (i = 0; i < numberOfAttributeNames; i++)
        {
            Attribute *pAttribute = pWaveManagedObject->getAttributeByName (attributeNames[i]);
 
            waveAssert (NULL != pAttribute, __FILE__, __LINE__);
 
            if ((pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectId) || (pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectIdVector))
            {
                AttributeObjectIdAssociation *pAttributeObjectIdAssociation = dynamic_cast<AttributeObjectIdAssociation *> (pAttribute);
                string                        associatedClassName           = pAttributeObjectIdAssociation->getAssociatedTo ();
                vector <string>               associatedKeyNames;
 
                /* Get the Keys (or combination thereof) used for this class */
 
                OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (associatedClassName, associatedKeyNames);
 
                /* We are only supporting MOs with a single primary key */
    
                waveAssert (associatedKeyNames.size () == 1, __FILE__, __LINE__);

                WaveManagedObject *associatedManagedObject = queryManagedObject (pAttributeObjectIdAssociation->getValue());
 
                Attribute *pAssociatedAttribute = associatedManagedObject->getAttributeByName (associatedKeyNames[0]);
 
                /* Create a clone of the associated key and set the attribute name as parent attribute name and append it to the attribute vector */
 
                Attribute *pClonedAttribute = pAssociatedAttribute->clone ();
 
                waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);
 
                pClonedAttribute->setAttributeName (pAttribute->getAttributeName ());

                pWaveManagedObjectDeleteContext->addToAttributeVector (pClonedAttribute);
 
                pWaveManagedObjectDeleteContext->addManagedObjectForGarbageCollection (associatedManagedObject);
            }
        }
 
        --(*pWaveManagedObjectDeleteContext);
    }

    pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
            
    return; 
}

void WaveManagedObjectDeleteWorker::deleteDeleteManagedObjectStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteDeleteManagedObjectStep : Entering ...");

    vector<UI32>       attributeUserTags         = pWaveManagedObjectDeleteContext->getAttributeUserTags ();
    vector<Attribute*> attributes                = pWaveManagedObjectDeleteContext->getAttributes ();
    UI32               numberOfAttributes        = attributes.size ();
    UI32               i                         = 0;
    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();

    if (!pWaveManagedObjectDeleteContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteDeleteManagedObjectStep : skipping for Local Service & Global MO");

        if (NULL != pWaveManagedObject)
        {
            pWaveManagedObjectDeleteContext->addManagedObjectForGarbageCollection (pWaveManagedObject);
        }    

        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    if (false == pWaveManagedObjectDeleteContext->isNeedToDeleteManagedObject ()) 
    {
        if (NULL != pWaveManagedObject)
        {
            pWaveManagedObjectDeleteContext->addManagedObjectForGarbageCollection (pWaveManagedObject);

            for (i = 0; i < numberOfAttributes; i++)
            {
                Attribute *pClonedAttribute = (attributes[i])->clone ();

                waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

                Attribute *pAttribute       = pWaveManagedObject->getAttributeByName (pClonedAttribute->getAttributeName ());
                string     tempString;

                waveAssert (NULL != pAttribute, __FILE__, __LINE__);
               
                if ((pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectId) || (pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectIdVector))
                {
                    pAttribute->setDefaultValue ();
                }
                else
                {
                    pClonedAttribute->setDefaultValue ();
                    pClonedAttribute->toString (tempString);
 
                    AttributeVector *attributeVector = dynamic_cast<AttributeVector *> (pAttribute);
 
                    if (!attributeVector)
                    {
                        pAttribute->fromString (tempString);
                        pWaveManagedObject->setAttributeDefaultValue (pAttribute->getAttributeName ());
                    }
                    else
                    {
                        if (tempString.empty())
                        {
                            pAttribute->fromString (tempString);
                            pWaveManagedObject->setAttributeDefaultValue (pAttribute->getAttributeName ());
                        }
                        else
                        {
                            attributeVector->deleteAttributeFromVector (pClonedAttribute);
                            pWaveManagedObject->addAttributeToBeUpdated (pAttribute->getAttributeName ());
                        }
                    }
                }
            }

            updateWaveManagedObject (pWaveManagedObject);
        }
        else
        {
            pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_ERROR);
            return;
        }
    } 
    /* The MO is deleted in the postDelete step */

    pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
} 

void WaveManagedObjectDeleteWorker::deleteUpdateNewAttributeInManagedObject (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    vector<Attribute*> attributes                = pWaveManagedObjectDeleteContext->getAttributes ();
    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();

    UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext = new UpdateNewAttributeInManagedObjectContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectDeleteWorker::deleteUpdateNewAttributeInManagedObjectCallback), pWaveManagedObjectDeleteContext);

    pUpdateNewAttributeInManagedObjectContext->setAttributeVector (pWaveManagedObjectDeleteContext->getAttributes ());

    pWaveManagedObject->addNewAttributeToBeUpdatedForDelete (pUpdateNewAttributeInManagedObjectContext);
}

void WaveManagedObjectDeleteWorker::deleteUpdateNewAttributeInManagedObjectCallback (UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext)
{
    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = reinterpret_cast<WaveManagedObjectDeleteContext *> (pUpdateNewAttributeInManagedObjectContext->getPCallerContext ());
    WaveManagedObject              *pWaveManagedObject              = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    ResourceId                      status                          = pUpdateNewAttributeInManagedObjectContext->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR , "WaveManagedObjectDeleteWorker::createUpdateNewAttributeInManagedObjectCallback adding new attribute Fails");

        pWaveManagedObjectDeleteContext->executeNextStep (status);
        return;
    }

    vector<string>   newAttributeNames     = pUpdateNewAttributeInManagedObjectContext->getNewAttributeNames ();
    UI32             numberOfNewAttributes = newAttributeNames.size ();

    for (UI32 i = 0; i < numberOfNewAttributes; i++)
    {
        //add each attribute in the attribute vector of Main Context
        Attribute *pAttribute = pWaveManagedObject->getAttributeByName (newAttributeNames[i]);

        Attribute *pClonedAttribute = pAttribute->clone ();

        pWaveManagedObjectDeleteContext->addToAttributeVector (pClonedAttribute);
    }

    pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveManagedObjectDeleteWorker::deletePostDeleteManagedObjectStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePostDeleteManagedObjectStep : Entering ...");

    if (!pWaveManagedObjectDeleteContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePostDeleteManagedObjectStep : skipping for  Local Service Global MO");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject                              *pWaveManagedObject  = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    // check if it is composition then remove composition

    UI32        childUserTag                = pWaveManagedObjectDeleteContext->getChildUserTag ();
    ResourceId  status                      = WAVE_MESSAGE_SUCCESS;
        
    if (0 != childUserTag)
    {
        trace (TRACE_LEVEL_INFO, string ("child user tag ") + childUserTag);

        ObjectId            parentObjectId              = pWaveManagedObjectDeleteContext->getParentObjectId ();
        WaveManagedObject  *pParentWaveManagedObject    = queryManagedObject (parentObjectId);
        ObjectId            childObjectId               = pWaveManagedObjectDeleteContext->getOperateOnWaveManagedObjectId ();
        string              parentClassName             = OrmRepository::getTableNameById (parentObjectId.getClassId ());
        string              childClassName              = OrmRepository::getTableNameById (childObjectId.getClassId ());

        waveAssert (NULL != pParentWaveManagedObject, __FILE__, __LINE__);

        Attribute *pAttribute       = pParentWaveManagedObject->getAttributeByUserTag (childUserTag);
        string     compositionName  = pAttribute->getAttributeName ();

        if (isManagedClassSupported (parentClassName))
        {
            deleteRelationship  (parentClassName, childClassName, compositionName, parentObjectId, childObjectId);
        }
        else
        {
            status = updateRelationship (pWaveManagedObjectDeleteContext, parentClassName, childClassName, compositionName, parentObjectId, childObjectId);
        }

        pWaveManagedObjectDeleteContext->addManagedObjectForGarbageCollection (pParentWaveManagedObject);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            pWaveManagedObjectDeleteContext->executeNextStep (status);
            return;
        }
    }
    /* Figure out if any of the objects are associated with this object and send them delete 
     * requests for the specific attributes */

    if (pWaveManagedObjectDeleteContext->isNeedToDeleteManagedObject())
    {
        deleteAssociations (pWaveManagedObjectDeleteContext);

        delete pWaveManagedObject;

        pWaveManagedObjectDeleteContext->setPOperateOnWaveManagedObject(NULL);
    }
    
    pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStep : Entering ...");

    if (pWaveManagedObjectDeleteContext->getIsBackendUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStep : skipping for local service");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveAsynchronousContext *pWaveAsynchronousContext     = new WaveAsynchronousContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStepCallback), pWaveManagedObjectDeleteContext);
    WaveManagedObject        *pOperateOnWaveManagedObject   = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject   ();
   
    if (NULL != pOperateOnWaveManagedObject)
    {
        pOperateOnWaveManagedObject->preDeleteHardwareStepForOperateOnWaveManagedObject (pWaveAsynchronousContext);
    }
	else
	{
		delete pWaveAsynchronousContext;
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_ERROR);
	}
    
    return;
}

void WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStepCallback (WaveAsynchronousContext *pWaveAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStepCallBack : Entering ...");

    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = reinterpret_cast<WaveManagedObjectDeleteContext *> (pWaveAsynchronousContext->getPCallerContext ());
    ResourceId                      status                          = pWaveAsynchronousContext->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "WaveManagedObjectDeleteWorker::deletePreUpdateHardwareStepCallback completion status " + FrameworkToolKit::localize (status));
    }

    pWaveManagedObjectDeleteContext->executeNextStep (status);
}

void WaveManagedObjectDeleteWorker::deleteUpdateHardwareStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteUpdateHardwareStep : Entering ...");

    if (!pWaveManagedObjectDeleteContext->getIsBackendUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteUpdateHardwareStep : skipping for Global Service");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject          *pOperateOnWaveManagedObject  = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject   ();

    if (NULL != pOperateOnWaveManagedObject)
    {
        GetHardwareConfigurationDetailsForDeleteContext *pGetHardwareConfigurationDetailsForDeleteContext = new GetHardwareConfigurationDetailsForDeleteContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectDeleteWorker::deleteUpdateHardwareStepCallBack), pWaveManagedObjectDeleteContext);

        pGetHardwareConfigurationDetailsForDeleteContext->setAttributeNames      (pWaveManagedObjectDeleteContext->getAttributeNames ());
        pGetHardwareConfigurationDetailsForDeleteContext->setAttributeValues     (pWaveManagedObjectDeleteContext->getAttributeValues ());
        pGetHardwareConfigurationDetailsForDeleteContext->setAttributeVector     (pWaveManagedObjectDeleteContext->getAttributes ());

        pOperateOnWaveManagedObject->getHardwareConfigurationDetailsForDelete (pGetHardwareConfigurationDetailsForDeleteContext);
    }
    else
    {
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveManagedObjectDeleteWorker::deleteUpdateHardwareStepCallBack (GetHardwareConfigurationDetailsForDeleteContext *pGetHardwareConfigurationDetailsForDeleteContext)
{
    UnifiedClientDeleteMessage     *pMessage                        = NULL;
    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = reinterpret_cast<WaveManagedObjectDeleteContext *> (pGetHardwareConfigurationDetailsForDeleteContext->getPCallerContext ());
    ResourceId                      status                          = pGetHardwareConfigurationDetailsForDeleteContext->getCompletionStatus ();
    WaveManagedObject              *pOperateOnWaveManagedObject     = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject   ();
    vector <Attribute *>            attributeVector                 = pWaveManagedObjectDeleteContext->getAttributes ();
    string                          clientNameToSend;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "createUpdateHardwareStepCallBack: failed to get the hardware details");

        pWaveManagedObjectDeleteContext->executeNextStep (status);
        return;
    }

    if (pGetHardwareConfigurationDetailsForDeleteContext->getIsUpdateBackend ())
    {

        if (NULL != pOperateOnWaveManagedObject)
        {
            pGetHardwareConfigurationDetailsForDeleteContext->setManagedObjectName (pOperateOnWaveManagedObject->getObjectClassName ());

            //Populate the key attributes of an MO for the backend to identify that update/delete is performed on which MO
            if (false == pWaveManagedObjectDeleteContext->isNeedToDeleteManagedObject ())
            {
                populateManagedObjectKeyAttributes (pWaveManagedObjectDeleteContext);
            }

            //Populate the parent key attributes in case of composition. In case of Composition updation of the parent key alone is sufficient as part of child MO update/delete to the backend
            populateParentKeyAttributes (pWaveManagedObjectDeleteContext);

            //Populate the realated attributes if they are not modified
            //This is required by the backend to use common layer.
            clientNameToSend = getClientNameToSendAndPopulateRelatedAttributes (pGetHardwareConfigurationDetailsForDeleteContext);
            waveAssert ("" != clientNameToSend, __FILE__, __LINE__);

            pGetHardwareConfigurationDetailsForDeleteContext->setAttributeVector (pWaveManagedObjectDeleteContext->getAttributes ());
            pGetHardwareConfigurationDetailsForDeleteContext->setParentManagedObjectNames (pWaveManagedObjectDeleteContext->getParentManagedObjectNames());

            pMessage = new UnifiedClientDeleteMessage (pGetHardwareConfigurationDetailsForDeleteContext);

            pMessage->setConfigReplayInProgressFlag (pWaveManagedObjectDeleteContext->getConfigReplayInProgressFlag());

            trace (TRACE_LEVEL_INFO, "Sending to Client " + clientNameToSend);

            status = sendSynchronouslyToWaveClient (clientNameToSend, pMessage);

            if (status == WAVE_MESSAGE_SUCCESS)
            {
                status = pMessage->getCompletionStatus ();

                WaveObjectManagerDeleteWaveManagedObjectMessage *pDeleteMessage = reinterpret_cast<WaveObjectManagerDeleteWaveManagedObjectMessage *> (pWaveManagedObjectDeleteContext->getPWaveMessage());
                pDeleteMessage->setWarningResourceId (pMessage->getWarningResourceId());
            }
            else
            {
                trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteUpdateHardwareStepCallBack : Error while sending Message to client " + clientNameToSend + " with status : " + FrameworkToolKit::localize (status)));
            }

            if (0 != pMessage->getWarningResourceId())
            {
                trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteUpdateHardwareStepCallBack : WarningResourceId = " ) + FrameworkToolKit::localize (pMessage->getWarningResourceId()));
            }
            

            delete pMessage;
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "WaveManagedObjectUpdateWorker::deleteUpdateHardwareStep : Could not get the Operate on Managed Object");
            status = WAVE_MESSAGE_ERROR;
        }
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, "WaveManagedObjectUpdateWorker::deleteUpdateHardwareStep : message NOT sent to backend");
    }

    pWaveManagedObjectDeleteContext->executeNextStep (status);

}
    
void WaveManagedObjectDeleteWorker::deletePostUpdateHardwareStep (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePostUpdateHardwareStep : Entering ...");

    if (!pWaveManagedObjectDeleteContext->getIsBackendUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deletePostUpdateHardwareStep : skipping for Global Service");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;       
    }

    pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

ResourceId WaveManagedObjectDeleteWorker::updateRelationship (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext, const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId)
{
    // This function should be used when parent MO is owned by this currently working object manager.
    // create new message to send to other node
    // put all the field in the message, need to create message in such a way that, receiver can use it for updating MO and backend.
    // Make sure we use nested transaction for updating parent MO. It means, when receiver received this message, Object Id of child is not commited in the database.

    // send parent attibute name, parent attribute value as received from WyserEa g/w which is the keyvalue of child (this MO).

    vector<string>     attributeNames            = pWaveManagedObjectDeleteContext->getAttributeNames ();
    vector<string>     attributeValues           = pWaveManagedObjectDeleteContext->getAttributeValues ();
    string             attributeValue;
    WaveObjectManager *pWaveObjectManager        = WaveObjectManager::getOwnerForManagedClass (parentClassName);

    WaveObjectManagerUpdateRelationshipMessage  *pWaveObjectManagerUpdateRelationshipMessage = new WaveObjectManagerUpdateRelationshipMessage (pWaveObjectManager->getServiceId ());

    pWaveObjectManagerUpdateRelationshipMessage->setRelationshipVariables (parentClassName, childClassName, relationshipName, parentObjectId, childObjectId);

    pWaveObjectManagerUpdateRelationshipMessage->setIsAddingRelationship (false);

    WaveMessageStatus status = sendSynchronously (pWaveObjectManagerUpdateRelationshipMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        return (status);
    }
    else
    {
        return (pWaveObjectManagerUpdateRelationshipMessage->getCompletionStatus ());
    }
}

void WaveManagedObjectDeleteWorker::commitWaveManagedObjectBeforeUpdatingBackend (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::commitWaveManagedObjectBeforeUpdatingBackend : Entering ...");

    if (!pWaveManagedObjectDeleteContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::commitWaveManagedObjectBeforeUpdatingBackend : skipping for  Local Service Global MO");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    vector<Attribute*> attributes                = pWaveManagedObjectDeleteContext->getAttributes ();

    bool updateHardwareBeforeManagedObject       = pWaveManagedObject->updateHardwareBeforeWaveManagedObject (attributes);

    if (false == updateHardwareBeforeManagedObject)
    {
        waveLinearSequencerCommitTransactionStep (pWaveManagedObjectDeleteContext);
    }
    else
    {
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

}

void WaveManagedObjectDeleteWorker::commitWaveManagedObjectAfterUpdatingBackend (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::commitWaveManagedObjectAfterUpdatingBackend : Entering ...");
    
    if (!pWaveManagedObjectDeleteContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::commitWaveManagedObjectAfterUpdatingBackend : skipping for  Local Service Global MO");
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    vector<Attribute*> attributes                = pWaveManagedObjectDeleteContext->getAttributes ();

    bool updateHardwareBeforeManagedObject       = pWaveManagedObject->updateHardwareBeforeWaveManagedObject (attributes);

    if (true == updateHardwareBeforeManagedObject)
    {
        waveLinearSequencerCommitTransactionStep (pWaveManagedObjectDeleteContext);
    }
    else
    {
        pWaveManagedObjectDeleteContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveManagedObjectDeleteWorker::populateManagedObjectKeyAttributes (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    WaveManagedObject              *pOperateOnWaveManagedObject     = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    vector <string>                 keyNames;
    vector <string>::iterator       keyElement;

    OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (pOperateOnWaveManagedObject->getObjectClassName (), keyNames);

    for (keyElement = keyNames.begin (); keyElement != keyNames.end (); keyElement++)
    {
        trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectDeleteWorker::populateManagedObjectKeyAttributes :: Key Name = ") + *keyElement);

        Attribute* pAttribute       = pOperateOnWaveManagedObject->getAttributeByName (*keyElement);
        Attribute *pClonedAttribute = NULL;

        waveAssert (NULL != pAttribute, __FILE__, __LINE__);

        if ((pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectId) || (pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectIdVector))
        {
            /* Get the class name of the associated object */

            AttributeObjectIdAssociation *pAttributeObjectIdAssociation = dynamic_cast<AttributeObjectIdAssociation *> (pAttribute);
            string                        associatedClassName           = pAttributeObjectIdAssociation->getAssociatedTo ();
            vector <string>               associatedKeyNames;

            /* Get the Keys (or combination thereof) used for this class */

            OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (associatedClassName, associatedKeyNames);

            /* We are only supporting MOs with a single primary key */

            waveAssert (associatedKeyNames.size () == 1, __FILE__, __LINE__);

            WaveManagedObject *associatedManagedObject = queryManagedObject (pAttributeObjectIdAssociation->getValue());

            Attribute *pAssociatedAttribute = associatedManagedObject->getAttributeByName (associatedKeyNames[0]);

            /* Create a clone of the associated key and set the attribute name as parent attribute name and append it to the attribute vector */

            pClonedAttribute = pAssociatedAttribute->clone ();

            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

            pClonedAttribute->setAttributeName (pAttribute->getAttributeName ());

            pWaveManagedObjectDeleteContext->addManagedObjectForGarbageCollection (associatedManagedObject);
        }   
        else
        {
            pClonedAttribute = pAttribute->clone ();

            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);
        }

        pWaveManagedObjectDeleteContext->addToAttributeVector (pClonedAttribute);
    }
}

void WaveManagedObjectDeleteWorker::populateParentKeyAttributes (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
   vector<string>    parentMONames;  
    WaveManagedObject *pOperateOnWaveManagedObject = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject();
    // Update the parent key attributes to be sent to the backend.
 
    while (ObjectId::NullObjectId != pOperateOnWaveManagedObject->getOwnerManagedObjectId())
    {       
        //Get Parent Managed Object
        pOperateOnWaveManagedObject = queryManagedObject (pOperateOnWaveManagedObject->getOwnerManagedObjectId());

        pWaveManagedObjectDeleteContext->addManagedObjectForGarbageCollection (pOperateOnWaveManagedObject);
        //add Parent MO Name into the vector.
        parentMONames.push_back(pOperateOnWaveManagedObject->getObjectClassName());
 
        vector<string>            keyNames;
        vector <string>::iterator keyElement;
        //Get Key Names for the Managed Class.
        OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (pOperateOnWaveManagedObject->getObjectClassName (), keyNames);
                
        for (keyElement = keyNames.begin (); keyElement != keyNames.end (); keyElement++)
        {
            Attribute *attr =  pOperateOnWaveManagedObject->getAttributeByName(*keyElement);
         
            waveAssert (NULL != attr, __FILE__, __LINE__);
 
            Attribute *pClonedAttribute = attr->clone ();
 
            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);
 
            //add attrivute value to the vector.
            pWaveManagedObjectDeleteContext->addToAttributeVector (pClonedAttribute);
        }
    }
    pWaveManagedObjectDeleteContext->setParentManagedObjectNames (parentMONames); 
}

string WaveManagedObjectDeleteWorker::getClientNameToSendAndPopulateRelatedAttributes (GetHardwareConfigurationDetailsForDeleteContext *pGetHardwareConfigurationDetailsForDeleteContext)
{
    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = reinterpret_cast<WaveManagedObjectDeleteContext *> (pGetHardwareConfigurationDetailsForDeleteContext->getPCallerContext ());
    map <string, UI32>              attributeNamesGroupCodeMap      = pGetHardwareConfigurationDetailsForDeleteContext->getAttributeNamesGroupCodeMap ();
    map <UI32, string>              groupCodeBackendNamesMap        = pGetHardwareConfigurationDetailsForDeleteContext->getGroupCodeBackendNamesMap ();
    map <string, string>            attributeNameBackendNameMap     = pGetHardwareConfigurationDetailsForDeleteContext->getAttributeNameBackendNameMap ();
    vector <Attribute *>            attributeVector                 = pWaveManagedObjectDeleteContext->getAttributes ();
    UI32                            groupCode                       = 0;
    string                          clientName;

    //Get the first attribute in the vector
    waveAssert (0 != attributeVector.size (), __FILE__, __LINE__);
    string attributeName = ((attributeVector) [0])->getAttributeName ();

    trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectDeleteWorker::getClientNameToSendAndPopulateRelatedAttributes: attributeName =") + attributeName);

    /*//Find the backend Name corresponding to the attribute
    //If we find an entry in this map it indicates that the plugin does not want grouping and hence we will only get the client Name and return
    if (attributeNameBackendNameMap.end () != attributeNameBackendNameMap.find (attributeName))
    {
        clientName = attributeNameBackendNameMap [attributeName];
        trace (TRACE_LEVEL_DEVEL, string("WaveManagedObjectDeleteWorker::getClientNameToSendAndPopulateRelatedAttributes: ClientName = ") + attributeName);

        //set the groupCode to default value
        pGetHardwareConfigurationDetailsForDeleteContext->setGroupCode (0);        

        return (clientName);
    }*/

    //Find the groupCode corresponding to the attribute in the map
    if (attributeNamesGroupCodeMap.end () != attributeNamesGroupCodeMap.find (attributeName))
    {

        groupCode = attributeNamesGroupCodeMap [attributeName];

        trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectDeleteWorker::getClientNameToSendAndPopulateRelatedAttributes: groupCode =") + groupCode);

        //set the groupCode
        pGetHardwareConfigurationDetailsForDeleteContext->setGroupCode (groupCode);

    }
    else
    {
        trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectDeleteWorker::getClientNameToSendAndPopulateRelatedAttributes: Could not find the groupCode corresponding to the attributeName =") + attributeName);
        waveAssert (false, __FILE__, __LINE__);
    }

    //Return the client name to send based on the opcode.
    if (groupCodeBackendNamesMap.end () != groupCodeBackendNamesMap.find (groupCode))
    {
        clientName = groupCodeBackendNamesMap [groupCode];
    }
    else
    {
        trace (TRACE_LEVEL_DEVEL, string("WaveManagedObjectCreateWorker::getClientNameToSendAndPopulateRelatedAttributes: Could not find the backendName corresponding to the groupCode = ") + groupCode);
        waveAssert (false, __FILE__, __LINE__);
    }

    return (clientName);
}

ResourceId WaveManagedObjectDeleteWorker::deleteAssociations (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectDeleteWorker::deleteAssociations : Entering ...");

    OrmRepository                                  *orm                 = OrmRepository::getInstance ();
    ManagedObjectSchemaInfoRepository              &moRepository        = orm->getMOSchemaInfoRepository ();
    WaveManagedObject                              *pWaveManagedObject  = pWaveManagedObjectDeleteContext->getPOperateOnWaveManagedObject ();
    ObjectId                                        myObjectId          = pWaveManagedObject->getObjectId ();
    string                                          myClassName         = OrmRepository::getTableNameById (myObjectId.getClassId ());
    ManagedObjectSchemaInfo                        *moSchemaInfo        = moRepository.findSchemaInfoObject(myClassName);
    map<string, ManagedObjectSchemaInfo*>           relationFromMap;
    map<string, ManagedObjectSchemaInfo*>::iterator itr ;
    UI32                                            i                   = 0;

    trace (TRACE_LEVEL_DEVEL, string (" 2: ") + myClassName + " schemename = " + moSchemaInfo->getName()); 

    waveAssert (NULL != moSchemaInfo, __FILE__, __LINE__);

    relationFromMap = moSchemaInfo->getRelationFromTables(); 

    /* Get the "Relation from" Table, and iterate through it */
    for (itr = relationFromMap.begin(); itr != relationFromMap.end(); itr++)
    {
        const string                associatedFromClassName         = itr->second->getName();
        WaveObjectManager          *pWaveObjectManager              = WaveObjectManager::getOwnerForManagedClass (associatedFromClassName);
        ManagedObjectSchemaInfo    *pFromSchemaInfo                 = itr->second;
        vector <string>             fromKeyNames;
        map<string, Attribute*>     fromKeyNamesAndTypesMap         = OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (associatedFromClassName, fromKeyNames);


        // TODO: Need to handle the case for singleton properly.

        if (0 != fromKeyNames.size ())
        {
            trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations : Iterating through class=") + itr->first + string(" with key=") + fromKeyNames[0]);
        }

        /* For each schema that is related to this class, get the relationtype field. The "second" field contains the Schema */
        map<string, string> relationFieldsTypeMap = pFromSchemaInfo->getRelationFields ();
        map<string, string>::iterator itr2;

        /* Go through the schema and find out the field which is related to this class */ 
        for (itr2 = relationFieldsTypeMap.begin(); itr2 != relationFieldsTypeMap.end(); itr2++)
        {
            OrmRelationUmlType  relationUmlType;
            OrmRelationType     relationType;
            vector<string>      tokens;

            /* Break the second part into tokens. This is of type a-1-classname */
            tokenize(itr2->second, tokens, '-');
            string associatedToClassName = tokens[2]; 

            tokens.erase(tokens.begin(),tokens.end());

            tokenize(associatedToClassName, tokens, '|');
            associatedToClassName = tokens[0];
    
            /* Parse this information to get the relationtype */
            OrmRepository::getOrmRelationTypeAndOrmRelationUmlType (associatedFromClassName, itr2->first, relationType, relationUmlType); 

            trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations : Iterating Relations[") + i + string("]: AttributeName=")+itr2->first + string (": RelationUmltype=")+relationUmlType+string(": fullstring=") + itr2->second + string (": associatedToClassName=") + associatedToClassName);

            if (relationUmlType == ORM_RELATION_UML_TYPE_ASSOCIATION && (associatedToClassName == myClassName)) 
            {

                bool isALocalManagedObject = OrmRepository::isALocalManagedObject(associatedFromClassName);

                /* Query the table and get the MOs that are associating to this class */
                WaveManagedObjectSynchronousQueryContext synchronousQueryContext(associatedFromClassName);
                synchronousQueryContext.addAndAttribute (new AttributeObjectId (myObjectId, itr2->first));

                if (true == isALocalManagedObject)
                {
                    synchronousQueryContext.addSelectField("ownerWaveNodeObjectId");
                }
                else
                {
                    synchronousQueryContext.addSelectField("objectId");
                }

                trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations :Querying Database  ") + associatedFromClassName +string(" for ")+ itr2->first);

                vector<WaveManagedObject *> *pResults = querySynchronously (&synchronousQueryContext);

                waveAssert (NULL != pResults, __FILE__, __LINE__);

                if (0 != pResults->size())
                {
                   trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations :Reults Database size ") + pResults->size());
 
                    //Set the ManagedObject Name (associated to current MO) in the Context. Plugin developer sets the message depending on the MO name.  
                    pWaveManagedObjectDeleteContext->setAssociatedFromManagedObjectName (associatedFromClassName);
 
                    //Call the Virtual function where plugin developer sets the non-UP message.
                    pWaveManagedObject->isManagedObjectsAssociatedToCurrentMONeedsToBeDeleted (pWaveManagedObjectDeleteContext);
 
                    WaveMessage             *pMessage                  = pWaveManagedObjectDeleteContext->getMessage();
                    WaveSendToClusterContext *pWaveSendToClusterContext = NULL;
                    vector<LocationId>        locationIds;
                    LocationId                handlingLocation          = 0;
                    WaveLocalManagedObjectBase *pWaveLocalManagedObjectBase = NULL;
                    UI32                       index;
 
                    if (pMessage != NULL)
                    {
                        for (index = 0; index < pResults->size(); index ++)
                        {
                           if (true == isALocalManagedObject)
                            {
                                pWaveLocalManagedObjectBase = dynamic_cast<WaveLocalManagedObjectBase *> ((*pResults)[index]);
 
                                waveAssert (NULL != pWaveLocalManagedObjectBase, __FILE__, __LINE__);
 
                                handlingLocation = pWaveLocalManagedObjectBase->getOwnerLocationId ();
                            }
 
                            if (handlingLocation != 0 )
                            {
                                locationIds.push_back(handlingLocation);
                            }
                        }
                        
                        if (false == isALocalManagedObject)
                        {
                            handlingLocation = FrameworkToolKit::getClusterPrimaryLocationId ();
                            locationIds.push_back(handlingLocation);
                        }
 
                        sort(locationIds.begin(), locationIds.end());
                        locationIds.erase(unique(locationIds.begin(), locationIds.end()), locationIds.end());
 
                        pWaveSendToClusterContext = new WaveSendToClusterContext (this, reinterpret_cast<WaveAsynchronousCallback>(&WaveManagedObjectDeleteWorker::deleteAssociationCallback), pWaveManagedObjectDeleteContext);
 
                        pWaveSendToClusterContext->setPWaveMessageForPhase1 (pMessage);
 
                        if (0 != locationIds.size())
                        {
                            pWaveSendToClusterContext->setLocationsToSendToForPhase1 (locationIds);
                            sendToWaveCluster (pWaveSendToClusterContext);
                            ++(*pWaveManagedObjectDeleteContext);
                        }
                        else
                        {
                            delete pWaveSendToClusterContext;
                        }
                    }
                    else
                    {
                        map<LocationId, vector<ObjectId> >           locationToVectorObjectIdMap;
                        map<LocationId, vector<ObjectId> >::iterator locationToVectorObjectIdMapIterator;
                        map<LocationId, vector<vector<string> > >    locationToVectorVectorAttributeNamesMap;

                        if (false == isALocalManagedObject)
                        {
                            handlingLocation = FrameworkToolKit::getClusterPrimaryLocationId ();
                        }

                        for (index = 0; index < pResults->size(); index ++)
                        {
                            vector<string>   attributeNames;
                            
                            if (true == isALocalManagedObject)
                            {
                                pWaveLocalManagedObjectBase = dynamic_cast<WaveLocalManagedObjectBase *> ((*pResults)[index]);
 
                                waveAssert (NULL != pWaveLocalManagedObjectBase, __FILE__, __LINE__);
 
                                handlingLocation = pWaveLocalManagedObjectBase->getOwnerLocationId ();
                            }
                        
                            locationToVectorObjectIdMap[handlingLocation].push_back((*pResults)[index]->getObjectId());

                            attributeNames.clear ();
                            attributeNames.push_back(itr2->first);

                            locationToVectorVectorAttributeNamesMap[handlingLocation].push_back(attributeNames);
                           
                        } 
 
                        for (locationToVectorObjectIdMapIterator = locationToVectorObjectIdMap.begin(); locationToVectorObjectIdMapIterator != locationToVectorObjectIdMap.end(); locationToVectorObjectIdMapIterator++)
                        {
                            // send the UP message
                            WaveObjectManagerDeleteWaveManagedObjectsMessage  *pDeleteMessage = new WaveObjectManagerDeleteWaveManagedObjectsMessage (pWaveObjectManager->getServiceId());

                            // set the objectId vector into te message.
                            pDeleteMessage->setManagedObjectsIdVector       (locationToVectorObjectIdMapIterator->second);
 
                            //Set the attribute Vector into the message
                            pDeleteMessage->setAttributeNameVectorVector    (locationToVectorVectorAttributeNamesMap[locationToVectorObjectIdMapIterator->first]);

                            //set the LocationId
                            locationIds.push_back(locationToVectorObjectIdMapIterator->first);
 
                            // Check to see if the attribute name is actually the key for the object
                            if (0 != fromKeyNames.size ())
                            {
                                if (itr2->first == fromKeyNames[0])
                                {
                                    trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations : Setting MO to 1"));
                                    pDeleteMessage->setIsMO (1);
                                }
                                else
                                {
                                    trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations : Setting MO to 0"));
                                    pDeleteMessage->setIsMO (0);
                                }
                            }
                            else
                            {
                                pDeleteMessage->setIsMO (0);
                            }
 
                           pWaveSendToClusterContext = new WaveSendToClusterContext (this, reinterpret_cast<WaveAsynchronousCallback>(&WaveManagedObjectDeleteWorker::deleteAssociationCallback), pWaveManagedObjectDeleteContext);
 
                           pWaveSendToClusterContext->setPWaveMessageForPhase1 (pDeleteMessage);
                        
                           waveAssert (1 == locationIds.size(), __FILE__, __LINE__); 
 
                           if (0 != locationIds.size())
                           {
                                pWaveSendToClusterContext->setLocationsToSendToForPhase1 (locationIds);
                                sendToWaveCluster (pWaveSendToClusterContext);
                                ++(*pWaveManagedObjectDeleteContext);
                           }
                           else
                           {
                               delete pWaveSendToClusterContext;
                           }

                           locationIds.erase(locationIds.begin(),locationIds.end());
                       }
                    }
                } 

                pWaveManagedObjectDeleteContext->addManagedObjectsForGarbageCollection (*pResults);
            }
            else 
            {
                if (relationUmlType == ORM_RELATION_UML_TYPE_COMPOSITION && (associatedToClassName == myClassName)) 
                {
                    vector<ObjectId> objectIdVector;
                    ObjectId parentObjectId = pWaveManagedObject->getOwnerManagedObjectId();

                    trace (TRACE_LEVEL_INFO, string("WaveManagedObjectDeleteWorker::deleteAssociations :Type composition!! classname= ")+associatedFromClassName+string(" objectid=")+parentObjectId.getInstanceId());

                    objectIdVector.push_back (parentObjectId);
                    vector<WaveManagedObject *> *pResults = querySynchronously (associatedFromClassName, objectIdVector);

                    pWaveManagedObjectDeleteContext->addManagedObjectsForGarbageCollection (*pResults);

                    WaveManagedObject  *pParentManagedObject = (*pResults)[0]; 

                    waveAssert (NULL != pParentManagedObject, __FILE__, __LINE__); 

                    /* Ensure that the Object Manager is the same as the current one */
                    if (getPWaveObjectManager() == WaveObjectManager::getOwnerForManagedClass(associatedFromClassName)) 
                    {
                        deleteRelationship  (associatedFromClassName, myClassName, itr2->first, pWaveManagedObject->getOwnerManagedObjectId(), myObjectId);
                    }
                }
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

void WaveManagedObjectDeleteWorker::deleteAssociationCallback (WaveSendToClusterContext *pWaveSendToClusterContext)
{
    trace(TRACE_LEVEL_DEVEL,"WaveManagedObjectDeleteWorker::deleteAssociationCallback");

    ResourceId status = pWaveSendToClusterContext->getCompletionStatus ();
 
    WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext = reinterpret_cast<WaveManagedObjectDeleteContext*>(pWaveSendToClusterContext->getPCallerContext());
 
    delete (pWaveSendToClusterContext->getPWaveMessageForPhase1());
    delete (pWaveSendToClusterContext);

    --(*pWaveManagedObjectDeleteContext);

    pWaveManagedObjectDeleteContext->executeNextStep (status);
}

}

