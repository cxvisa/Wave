/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectUpdateWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectCreateWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectUpdateContext.h"
#include "Framework/Types/Types.h"
#include "Framework/Attributes/AttributeTypes.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "ManagementInterface/ClientInterface/UnifiedClientUpdateMessage.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveManagedObjectAsynchronousCreateContext.h"

namespace WaveNs
{

WaveManagedObjectUpdateWorker::WaveManagedObjectUpdateWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_OBJECT_MANAGER_UPDATE_MANAGED_OBJECT, reinterpret_cast<WaveMessageHandler> (&WaveManagedObjectUpdateWorker::updateHandler));
    addOperationMap (WAVE_OBJECT_MANAGER_UPDATE_RELATIONSHIP, reinterpret_cast<WaveMessageHandler> (&WaveManagedObjectUpdateWorker::updateRelationshipMessageHandler));
}

WaveManagedObjectUpdateWorker::~WaveManagedObjectUpdateWorker ()
{
}

WaveMessage *WaveManagedObjectUpdateWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case WAVE_OBJECT_MANAGER_UPDATE_MANAGED_OBJECT :
            pWaveMessage = new WaveObjectManagerUpdateWaveManagedObjectMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void WaveManagedObjectUpdateWorker::updateHandler (WaveObjectManagerUpdateWaveManagedObjectMessage *pWaveObjectManagerUpdateWaveManagedObjectMessage)
{
    trace (TRACE_LEVEL_DEBUG, "WaveManagedObjectUpdateWorker::updateHandler : update message recived by OM");
            
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updateValidateManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::WaveManagedObjectStartTransactionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updatePreUpdateManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updateUpdateManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updateUpdateNewAttributeInManagedObject),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updatePostUpdateManagedObjectStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::commitWaveManagedObjectBeforeUpdatingBackend),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updateUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updatePostUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::updateAttributesPostUpdateHardwareStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::commitWaveManagedObjectAfterUpdatingBackend),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveManagedObjectUpdateWorker::prismLinearSequencerFailedStep),
    };

    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = new WaveManagedObjectUpdateContext (pWaveObjectManagerUpdateWaveManagedObjectMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveManagedObjectUpdateContext->setOperateOnWaveManagedObjectId    (pWaveObjectManagerUpdateWaveManagedObjectMessage->getOperateOnWaveManagedObjectId ());
    pWaveManagedObjectUpdateContext->setAttributeUserTags               (pWaveObjectManagerUpdateWaveManagedObjectMessage->getAttributeUserTags   ());
    pWaveManagedObjectUpdateContext->setAttributeNames                  (pWaveObjectManagerUpdateWaveManagedObjectMessage->getAttributeNames      ());
    pWaveManagedObjectUpdateContext->setAttributeValues                 (pWaveObjectManagerUpdateWaveManagedObjectMessage->getAttributeValues     ());
    pWaveManagedObjectUpdateContext->setChoiceUserTagNeedToRemove       (pWaveObjectManagerUpdateWaveManagedObjectMessage->getChoiceUserTagNeedToRemove ());
    pWaveManagedObjectUpdateContext->setConfigReplayInProgressFlag      (pWaveObjectManagerUpdateWaveManagedObjectMessage->getConfigReplayInProgressFlag ());

    pWaveManagedObjectUpdateContext->holdAll ();
    pWaveManagedObjectUpdateContext->start   ();

}

void WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;
    string     className;
    ObjectId operateOnWaveManagedObjectId = pWaveManagedObjectUpdateContext->getOperateOnWaveManagedObjectId ();
    bool       isALocalService = FrameworkToolKit::isALocalService(getServiceId());
    bool       isALocalMO      = false;
        
    trace (TRACE_LEVEL_INFO, string ("WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep : For service =  ") + FrameworkToolKit::getServiceNameById(getServiceId()));

    if (0 != operateOnWaveManagedObjectId.getClassId ())
    {
        className  = OrmRepository::getTableNameById (operateOnWaveManagedObjectId.getClassId ());
        isALocalMO = OrmRepository::isALocalManagedObject(className);

        trace (TRACE_LEVEL_INFO, string ("WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep : For ManagedObject = ")+className);
    }
	else if(isALocalService)
	{
		isALocalMO = true;
	}

              
    if (!isALocalService && !isALocalMO)
    {
        // Global Service & Global MO    
        pWaveManagedObjectUpdateContext->setIsDatabaseUpdateRequired (true);    
        pWaveManagedObjectUpdateContext->setIsBackendUpdateRequired (false);        

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep :Global Service & Global MO");
    } 
    else if(isALocalService && isALocalMO)
    {
        // Local Service Local MO    
        pWaveManagedObjectUpdateContext->setIsDatabaseUpdateRequired (true);
        pWaveManagedObjectUpdateContext->setIsBackendUpdateRequired (true);

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep : Local Service Local MO");
    }
    else if(isALocalService && !isALocalMO)
    {
        // Local Service Global MO    
        pWaveManagedObjectUpdateContext->setIsDatabaseUpdateRequired (false);
        pWaveManagedObjectUpdateContext->setIsBackendUpdateRequired (true);

        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep : Local Service Global MO ");
    }
    else
    {
        // Global Service Local MO    
        pWaveManagedObjectUpdateContext->setIsDatabaseUpdateRequired (false);
        pWaveManagedObjectUpdateContext->setIsBackendUpdateRequired (false);
                           
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateQueryManagedObjectStep : Global Service Local MO");
                           
        waveAssert (false, __FILE__, __LINE__);
    }
    
    WaveManagedObject *pOperateOnWaveManagedObject = NULL;

    if (ObjectId::NullObjectId != operateOnWaveManagedObjectId)
    {
        pOperateOnWaveManagedObject = queryManagedObject (operateOnWaveManagedObjectId);

    }

    if (NULL != pOperateOnWaveManagedObject)
    {
        pWaveManagedObjectUpdateContext->setPOperateOnWaveManagedObject (pOperateOnWaveManagedObject);
    }
    
    if (NULL == pOperateOnWaveManagedObject)
    {
        status = WAVE_MANAGED_OBJECT_UPDATE_OBJECT_NOT_FOUND;
    }

    pWaveManagedObjectUpdateContext->executeNextStep (status);
    return;
}

void WaveManagedObjectUpdateWorker::WaveManagedObjectStartTransactionStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::WaveManagedObjectStartTransactionStep: Entering ...");
 
    if (!pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL , "WaveManagedObjectUpdateWorker::WaveManagedObjectStartTransactionStep : skipping for Local Service & Global MO");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }
 
    prismLinearSequencerStartTransactionStep (pWaveManagedObjectUpdateContext);
}

void WaveManagedObjectUpdateWorker::updateValidateManagedObjectStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateValidateManagedObjectStep : Entering ...");

    vector<UI32>       attributeUserTags         = pWaveManagedObjectUpdateContext->getAttributeUserTags ();
    vector<string>     attributeNames            = pWaveManagedObjectUpdateContext->getAttributeNames    ();
    vector<string>     attributeValues           = pWaveManagedObjectUpdateContext->getAttributeValues   ();
    UI32               numberOfAttributeUserTags = attributeUserTags.size ();
    UI32               numberOfAttributeNames    = attributeNames.size ();
    UI32               numberOfAttributeValues   = attributeValues.size ();
    UI32               i                         = 0;
    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();

    if (NULL != pWaveManagedObject)
    {
        if ((0 != numberOfAttributeUserTags) && (0 != numberOfAttributeNames))
        {
            waveAssert (false, __FILE__, __LINE__);
        }

        waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        if (0 != numberOfAttributeNames)
        {
            waveAssert (numberOfAttributeNames == numberOfAttributeValues, __FILE__, __LINE__);

            for (i = 0; i < numberOfAttributeNames; i++)
            {
                string attributeName  = attributeNames[i];
                string attributeValue = attributeValues[i];

                waveAssert ("" != attributeName, __FILE__, __LINE__);

                Attribute *pAttribute = pWaveManagedObject->getAttributeByName (attributeName);

                waveAssert (NULL != pAttribute, __FILE__, __LINE__);

                /* Add to the Attribute vector if it is not an "Association" type attribute */
                if ((pAttribute->getAttributeType() != AttributeType::AttributeTypeObjectId) && (pAttribute->getAttributeType () != AttributeType::AttributeTypeObjectIdVector)) 
                { 
                    Attribute *pClonedAttribute = pAttribute->clone ();

                    waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

                    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateValidateManagedObjectStep: Setting by attribute name \'" + attributeName + "\' to \'" + attributeValue + "\'");

                    pClonedAttribute->fromString (attributeValue);

                    pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);
                }
                else if ((false == pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired()) && ((pAttribute->getAttributeType() == AttributeType::AttributeTypeObjectId) || (pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectIdVector)))
                {
                    AttributeObjectIdAssociation   *pAttributeObjectIdAssociation       = dynamic_cast<AttributeObjectIdAssociation *> (pAttribute);
                    string                          associatedClassName                 = pAttributeObjectIdAssociation->getAssociatedTo ();
                    map<string, Attribute*>         associatedKeyNamesAndTypesMap;
                    vector <string>                 associatedKeyNames;
                    Attribute                      *pResultAttribute;

                    associatedKeyNamesAndTypesMap   = OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (associatedClassName, associatedKeyNames);
                    pResultAttribute                = associatedKeyNamesAndTypesMap[associatedKeyNames[0]];

                    Attribute *pAssociatedAttribute = Attribute::getAttributeFromAttributeType((pResultAttribute->getAttributeType()).getAttributeTypeResourceId());

                    pAssociatedAttribute->setAttributeName(pResultAttribute->getAttributeName());
                
                    pAssociatedAttribute->fromString(attributeValue);

                    Attribute *pClonedAttribute = pAssociatedAttribute->clone ();

                    waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

                    pClonedAttribute->setAttributeName(pAttribute->getAttributeName ());

                    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateValidateManagedObjectStep: Setting by attribute name \'" + attributeName + "\' to \'" + attributeValue + "\'");

                    pClonedAttribute->fromString (attributeValue);

                    pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);
                }
            }
        }
        else
        {
            waveAssert (numberOfAttributeUserTags == numberOfAttributeValues, __FILE__, __LINE__);

            for (i = 0; i < numberOfAttributeUserTags; i++)
            {
                UI32   attributeUserTag = attributeUserTags[i];
                string attributeValue   = attributeValues[i];

                waveAssert (0 != attributeUserTag, __FILE__, __LINE__);

                Attribute *pAttribute = pWaveManagedObject->getAttributeByUserTag (attributeUserTag);

                waveAssert (NULL != pAttribute, __FILE__, __LINE__);

                /* Add to the Attribute vector if it is not an "Association" type attribute */
                if ((pAttribute->getAttributeType() != AttributeType::AttributeTypeObjectId) && (pAttribute->getAttributeType () != AttributeType::AttributeTypeObjectIdVector))
                { 
                    Attribute *pClonedAttribute = pAttribute->clone ();

                    waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

                    trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectUpdateWorker::updateValidateManagedObjectStep: Setting by attribute user tag \'") + attributeUserTag + string ("\' to \'") + attributeValue + string ("\'"));

                    pClonedAttribute->fromString (attributeValue);

                    pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);
                }

                attributeNames.push_back (pAttribute->getAttributeName ());
            }

            pWaveManagedObjectUpdateContext->setAttributeNames (attributeNames);
        }

        if(FrameworkToolKit::isALocalService (getServiceId())) 
        {
            ValidateForUpdateAtThisNodeContext *pValidateForUpdateAtThisNodeContext = new ValidateForUpdateAtThisNodeContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::validateForUpdateAtThisNodeCallBack), pWaveManagedObjectUpdateContext); 

            pValidateForUpdateAtThisNodeContext->setAttributeNames      (attributeNames);
            pValidateForUpdateAtThisNodeContext->setAttributeValues     (attributeValues);
            pValidateForUpdateAtThisNodeContext->setAttributeVector     (pWaveManagedObjectUpdateContext->getAttributes ());

            pWaveManagedObject->validateForUpdateAtThisNode (pValidateForUpdateAtThisNodeContext);
        }
        else  //TODO validation for global Managed Object
        {
            trace (TRACE_LEVEL_DEBUG , "WaveManagedObjectUpdateWorker::validateForCreateAtThisNode Global service");
         
            if (NULL != pWaveManagedObject)
            {
                ValidateForUpdateAtThisNodeContext *pValidateGlobalForUpdateAtThisNodeContext = new ValidateForUpdateAtThisNodeContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::validateForUpdateAtThisNodeCallBack), pWaveManagedObjectUpdateContext);
         
                pValidateGlobalForUpdateAtThisNodeContext->setAttributeNames      (attributeNames);
                pValidateGlobalForUpdateAtThisNodeContext->setAttributeValues     (attributeValues);
                pValidateGlobalForUpdateAtThisNodeContext->setAttributeVector     (pWaveManagedObjectUpdateContext->getAttributes ());
                             
                pWaveManagedObject->validateGlobalForUpdateAtThisNode (pValidateGlobalForUpdateAtThisNodeContext);        
            }    
        }
    }
    else
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    return;
}


void WaveManagedObjectUpdateWorker::validateForUpdateAtThisNodeCallBack (ValidateForUpdateAtThisNodeContext *pValidateGlobalForUpdateAtThisNodeContext)
{
    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pValidateGlobalForUpdateAtThisNodeContext->getPCallerContext ());
    ResourceId                                               status = pValidateGlobalForUpdateAtThisNodeContext->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        pWaveManagedObjectUpdateContext->executeNextStep (status);
        return;
    }

    pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveManagedObjectUpdateWorker::updatePreUpdateManagedObjectStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePreUpdateManagedObjectStep: Entering ...");

    vector<Attribute*> attributes                = pWaveManagedObjectUpdateContext->getAttributes ();
    vector<string>     attributeNames            = pWaveManagedObjectUpdateContext->getAttributeNames ();
    vector<string>     attributeValues           = pWaveManagedObjectUpdateContext->getAttributeValues ();
    string             attributeValue;
    UI32               numberOfAttributeNames    = attributeNames.size ();
    UI32               i;
    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();

	waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);
	
    ObjectId           parentObjectId            = pWaveManagedObject->getObjectId ();
    string             parentClassName           = OrmRepository::getTableNameById (parentObjectId.getClassId ());

    if (!pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePreUpdateManagedObjectStep: skipping for  Local Service & Global MO");
        
        pWaveManagedObjectUpdateContext->addManagedObjectForGarbageCollection (pWaveManagedObject);

        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    /* Manage Context counter to handle multiple Associations */
    ++(*pWaveManagedObjectUpdateContext); 

    for (i = 0; i < numberOfAttributeNames; i++)
    {
        Attribute *pAttribute = pWaveManagedObject->getAttributeByName (attributeNames[i]);

        attributeValue = attributeValues[i];

        waveAssert (NULL != pAttribute, __FILE__, __LINE__);

        if ((pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectId) || (pAttribute->getAttributeType () == AttributeType::AttributeTypeObjectIdVector)) 
        {

            /* Get the class name of the associated object */

            AttributeObjectIdAssociation *pAttributeObjectIdAssociation = dynamic_cast<AttributeObjectIdAssociation *> (pAttribute);
            string                        associatedClassName           = pAttributeObjectIdAssociation->getAssociatedTo ();
            map<string, Attribute*>       associatedKeyNamesAndTypesMap;
            vector <string>               associatedKeyNames;
            Attribute                    *pResultAttribute;
            vector<WaveManagedObject *>  *pResults;

            /* Get the Keys (or combination thereof) used for this class */

            associatedKeyNamesAndTypesMap = OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (associatedClassName, associatedKeyNames);

            waveAssert (associatedKeyNames.size () == 1, __FILE__, __LINE__);

            pResultAttribute = associatedKeyNamesAndTypesMap[associatedKeyNames[0]];

            /* We are only supporting MOs with a single primary key */


            Attribute *pAssociatedAttribute = Attribute::getAttributeFromAttributeType((pResultAttribute->getAttributeType()).getAttributeTypeResourceId());

            pAssociatedAttribute->setAttributeName(pResultAttribute->getAttributeName());

            pAssociatedAttribute->fromString(attributeValue);


            /* Create a clone of the associated key and set the attribute name as parent attribute name and append it to the attribute vector */
            Attribute *pClonedAttribute = pAssociatedAttribute->clone ();
            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);
            pClonedAttribute->setAttributeName(pAttribute->getAttributeName ());
            pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);

            /* Query the database to find the instance */

            WaveManagedObjectSynchronousQueryContext synchronousQueryContext(associatedClassName);
            synchronousQueryContext.addAndAttribute (pAssociatedAttribute);

            if (true == OrmRepository::isALocalManagedObject(associatedClassName))
            {
                synchronousQueryContext.setLocationIdFilter (FrameworkToolKit::getThisLocationId ());
            }

            pResults = querySynchronously (&synchronousQueryContext);

            /* Set the Object ID in the Location MO to point to the returned results */

            if (pResults->size () != 0) 
            {
                ObjectId    childObjectId   = (*pResults)[0]->getObjectId (); 

                addRelationship (parentClassName, associatedClassName, attributeNames[i], parentObjectId, childObjectId);

                pWaveManagedObjectUpdateContext->addManagedObjectsForGarbageCollection (*pResults);
            } 
            else 
            {
                IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext = new IsAssociatedManagedObjectToBeCreatedContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::isAssociatedManagedObjectToBeCreatedCallback), pWaveManagedObjectUpdateContext);

                pAssociatedContext->setAssociatedClassName(associatedClassName);
                pAssociatedContext->setAssociatedAttributeName(pAssociatedAttribute->getAttributeName());
                pAssociatedContext->setAssociatedAttributeValue(attributeValue);
                pAssociatedContext->setAttributeIndex(i);

                /* Manage Context counter to handle multiple Associations */
                ++(*pWaveManagedObjectUpdateContext);

                pWaveManagedObject->isAssociatedManagedObjectToBeCreated(pAssociatedContext); 
            }
        }
    }

    --(*pWaveManagedObjectUpdateContext);

    if (WAVE_MESSAGE_SUCCESS != pWaveManagedObjectUpdateContext->getErrorInCreatingMO ())
    {
        pWaveManagedObjectUpdateContext->executeNextStep (pWaveManagedObjectUpdateContext->getErrorInCreatingMO ());
    }
    else
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

    return;
}

ObjectId WaveManagedObjectUpdateWorker::createAssociatedManagedObject (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext, IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext, string associatedClassName, 
        string associatedAttributeName, string associatedAttributeValue)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::createAssociatedManagedObject: Entering ...");

    WaveObjectManager                                  *pWaveObjectManager          = WaveObjectManager::getOwnerForManagedClass (associatedClassName);
    //bool                isALocalManagedObject = OrmRepository::isALocalManagedObject (associatedClassName);
    vector<string>                                      associatedAttributeNames;
    vector<string>                                      associatedAttributeValues;
    UI32                                                status;
    WaveObjectManagerCreateWaveManagedObjectMessage    *pCreateMessage              = NULL; 
    WaveMessage                                       *pAssociatedMessage          = pAssociatedContext->getMessage(); 

    pAssociatedContext->setAttributeVector (pWaveManagedObjectUpdateContext->getAttributes ());
    pAssociatedContext->setAttributeNames (pWaveManagedObjectUpdateContext->getAttributeNames ());
    pAssociatedContext->setAttributeValues (pWaveManagedObjectUpdateContext->getAttributeValues ());

    if (NULL == pAssociatedMessage) 
    {
        /* Allocate the message with the appropriate service Id */
        pCreateMessage = new WaveObjectManagerCreateWaveManagedObjectMessage (pWaveObjectManager->getServiceId ());
        pCreateMessage->setManagedObjectClassNameNeedToBeCreated (associatedClassName);

        /* Setup the attributes */

        associatedAttributeValues.clear   ();
        associatedAttributeNames.clear    ();

        associatedAttributeNames.push_back(associatedAttributeName);
        associatedAttributeValues.push_back(associatedAttributeValue);
        pCreateMessage->setAttributeValues   (associatedAttributeValues);
        pCreateMessage->setAttributeNames    (associatedAttributeNames);

#if 0
                        /* Check to see if the associated class/object is of type composition or is not locally managed*/
                        if (!isALocalManagedObject) {
                            waveAssert (0, __FILE__, __LINE__);
                        }
#endif
    } 
    else 
    {
        /* We have the message, so no changes required */
    }

    /* Send this message to the OM on the local node to create the object */
    if (NULL != pAssociatedMessage) 
    {
        trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectUpdateWorker::createAssociatedManagedObject:: Sending associated Message"));

        status = sendSynchronously (pAssociatedMessage, FrameworkToolKit::getThisLocationId ());
    }
    else
    {
        trace (TRACE_LEVEL_DEVEL, string ("WaveManagedObjectUpdateWorker::createAssociatedManagedObject:: Sending Message to create a new associated managed object"));

        status = sendSynchronously (pCreateMessage, FrameworkToolKit::getThisLocationId ());
    }

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        if (NULL != pCreateMessage) 
        {
            /* Check for completion status */
            if (pCreateMessage->getCompletionStatus() == WAVE_MESSAGE_SUCCESS)
            {
                /* MO was successfully created, so get the object Id */
                ObjectId childObjectId = pCreateMessage->getObjectId();
                
                delete pCreateMessage;

                return (childObjectId);
            } 
        }
    }

    return (ObjectId::NullObjectId);
}

void WaveManagedObjectUpdateWorker::isAssociatedManagedObjectToBeCreatedCallback (IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::isAssociatedManagedObjectToBeCreatedCallback: Entering ...");

    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pAssociatedContext->getPCallerContext ());
    ResourceId                      status = pAssociatedContext->getCompletionStatus ();
    string                          associatedClassName = pAssociatedContext->getAssociatedClassName();
    WaveManagedObject              *pWaveManagedObject  = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    vector<string>                  attributeNames      = pWaveManagedObjectUpdateContext->getAttributeNames ();
    ObjectId                        parentObjectId      = pWaveManagedObject->getObjectId ();
    string                          parentClassName     = OrmRepository::getTableNameById (parentObjectId.getClassId ());
    
    if (WAVE_MESSAGE_SUCCESS == status && pAssociatedContext->getIsAssociatedMOToBeCreated())
    {
        if (getPWaveObjectManager () != WaveObjectManager::getOwnerForManagedClass (associatedClassName))
        {
            ObjectId childObjectId = createAssociatedManagedObject (pWaveManagedObjectUpdateContext, pAssociatedContext, associatedClassName, pAssociatedContext->getAssociatedAttributeName(),  pAssociatedContext->getAssociatedAttributeValue());

            if (ObjectId::NullObjectId != childObjectId) 
            {
                trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::isAssociatedManagedObjectToBeCreatedCallback: Creating the relationship");
                addRelationship (parentClassName, associatedClassName, attributeNames[pAssociatedContext->getAttributeIndex()], parentObjectId, childObjectId);
            } 
            else 
            {
                /* Manage Context counter to handle multiple Associations */
                --(*pWaveManagedObjectUpdateContext);
                pWaveManagedObjectUpdateContext->setErrorInCreatingMO (WAVE_MESSAGE_ERROR);
                pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_ERROR);
                return;
            }
        }
        else
        {
            //owner of associated Managed Object is the same as mine. Using Asynchronous context to call the function in WaveManagedObjectCreateWorker.
            WaveManagedObjectAsynchronousCreateContext *pWaveManagedObjectAsynchronousCreateContext = new WaveManagedObjectAsynchronousCreateContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::createAssociatedManagedObjectCallback), pWaveManagedObjectUpdateContext);
            vector<string>                              associatedAttributeNames;
            vector<string>                              associatedAttributeValues;

            pWaveManagedObjectUpdateContext->addAysnchronousContextForGarbageCollection (pWaveManagedObjectAsynchronousCreateContext);

            associatedAttributeNames.push_back  (pAssociatedContext->getAssociatedAttributeName());
            associatedAttributeValues.push_back (pAssociatedContext->getAssociatedAttributeValue());

            pWaveManagedObjectAsynchronousCreateContext->setAttributeValues (associatedAttributeValues);
            pWaveManagedObjectAsynchronousCreateContext->setAttributeNames  (associatedAttributeNames);
            pWaveManagedObjectAsynchronousCreateContext->setManagedObjectClassNameNeedToBeCreated (associatedClassName);
            pWaveManagedObjectAsynchronousCreateContext->setParentAttributeName (attributeNames[pAssociatedContext->getAttributeIndex()]);

            WaveManagedObjectCreateWorker *pWorker = dynamic_cast<WaveManagedObjectCreateWorker *> ((getPWaveObjectManager ())->getPWaveManagedObjectCreateWorker ());

            waveAssert (NULL != pWorker, __FILE__, __LINE__);

            pWorker->asynchronousCreateHandler (pWaveManagedObjectAsynchronousCreateContext); 

            return;           
        }
    }
    else 
    {
        /* Manage Context counter to handle multiple Associations */
        --(*pWaveManagedObjectUpdateContext);

        //User has set the completion status as SuCCESS but IsAssociatedMOToBeCreated flag is not set, so the final status is ERROR.
        if (WAVE_MESSAGE_SUCCESS == status)
        {
            status = WAVE_MESSAGE_ERROR;
        }

        pWaveManagedObjectUpdateContext->setErrorInCreatingMO(status);
        pWaveManagedObjectUpdateContext->executeNextStep (status);
        return;
    }

    /* Manage Context counter to handle multiple Associations */
    --(*pWaveManagedObjectUpdateContext);

    /* Check to see if we have encountered any error at all, in which case we will error out the last step */
    if (WAVE_MESSAGE_SUCCESS != pWaveManagedObjectUpdateContext->getErrorInCreatingMO()) 
    {
        trace (TRACE_LEVEL_ERROR, "WaveManagedObjectUpdateWorker::isAssociatedManagedObjectToBeCreatedCallback: Error in creating an Managed Object.");

        pWaveManagedObjectUpdateContext->executeNextStep (pWaveManagedObjectUpdateContext->getErrorInCreatingMO());
    }
    else 
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveManagedObjectUpdateWorker::createAssociatedManagedObjectCallback (WaveManagedObjectAsynchronousCreateContext *pWaveManagedObjectAsynchronousCreateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::createAssociatedManagedObjectCallback entering ...");

    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pWaveManagedObjectAsynchronousCreateContext->getPCallerContext ());

    waveAssert (NULL != pWaveManagedObjectUpdateContext, __FILE__, __LINE__);

    WaveManagedObject  *pWaveManagedObject  = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    ObjectId            parentObjectId      = pWaveManagedObject->getObjectId ();
    string              parentClassName     = OrmRepository::getTableNameById (parentObjectId.getClassId ());
    string              parentAttributeName = pWaveManagedObjectAsynchronousCreateContext->getParentAttributeName ();
    ObjectId            childObjectId       = pWaveManagedObjectAsynchronousCreateContext->getObjectId ();
    ResourceId          completionStatus   = pWaveManagedObjectAsynchronousCreateContext->getCompletionStatus ();
    string              childClassName      = pWaveManagedObjectAsynchronousCreateContext->getManagedObjectClassNameNeedToBeCreated ();

    if (WAVE_MESSAGE_SUCCESS == completionStatus)
    {
        if (ObjectId::NullObjectId != childObjectId)
        {
            addRelationship (parentClassName, childClassName, parentAttributeName, parentObjectId, childObjectId);
        }
        else
        {
            completionStatus = WAVE_MESSAGE_ERROR;
            pWaveManagedObjectUpdateContext->setErrorInCreatingMO (completionStatus);
        }
    }
    else
    {
        pWaveManagedObjectUpdateContext->setErrorInCreatingMO (completionStatus);
    }
    
    --(*pWaveManagedObjectUpdateContext);

    pWaveManagedObjectUpdateContext->executeNextStep (completionStatus);
}

void WaveManagedObjectUpdateWorker::updateUpdateManagedObjectStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateUpdateManagedObjectStep : Entering ...");

    WaveManagedObject *pWaveManagedObject           = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    vector<Attribute*> attributes                   = pWaveManagedObjectUpdateContext->getAttributes ();
    UI32               numberOfAttributes           = attributes.size ();
    UI32               i                            = 0;
    UI32               numberOfAssociatedAttributes = 0;

    if (!pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateUpdateManagedObjectStep : skipping for Local Service & Global MO");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;            
    }

    if (NULL != pWaveManagedObject)
    {
        pWaveManagedObjectUpdateContext->addManagedObjectForGarbageCollection (pWaveManagedObject);

        for (i = 0; i < numberOfAttributes; i++)
        {
            Attribute *pClonedAttribute = attributes[i];
            Attribute *pAttribute       = pWaveManagedObject->getAttributeByName (pClonedAttribute->getAttributeName ());
            string     tempString;

            waveAssert (NULL != pAttribute, __FILE__, __LINE__);

            if ((pAttribute->getAttributeType () != AttributeType::AttributeTypeObjectId) && (pAttribute->getAttributeType () != AttributeType::AttributeTypeObjectIdVector))
            {
                AttributeVector *attributeVector = dynamic_cast<AttributeVector *> (pAttribute);
                                
                if (!attributeVector)
                {
                    pClonedAttribute->toString (tempString);
                    pAttribute->fromString (tempString);
                }
                else
                {
                    // push the incomming Attribute's elements in the existing vector and then update 
                    attributeVector->addAttributeToVector (pClonedAttribute);
                }

                pWaveManagedObject->addAttributeToBeUpdated (pAttribute->getAttributeName ());       

            }
            else
            {
                numberOfAssociatedAttributes++;
            }
        }

        if (0 != pWaveManagedObjectUpdateContext->getChoiceUserTagNeedToRemove ())
        {
            Attribute *pChoiceAttributeToRemove = pWaveManagedObject->getAttributeByUserTag (pWaveManagedObjectUpdateContext->getChoiceUserTagNeedToRemove ());
            waveAssert (NULL != pChoiceAttributeToRemove, __FILE__, __LINE__);

            pChoiceAttributeToRemove->setDefaultValue ();
            pWaveManagedObject->addAttributeToBeUpdated (pChoiceAttributeToRemove->getAttributeName ());
        }

        if (0 != (numberOfAttributes - numberOfAssociatedAttributes))
        {
            updateWaveManagedObject (pWaveManagedObject);
        }

        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveManagedObjectUpdateWorker::updateUpdateNewAttributeInManagedObject (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    vector<Attribute*> attributes                = pWaveManagedObjectUpdateContext->getAttributes ();
    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();

    UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext = new UpdateNewAttributeInManagedObjectContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::updateUpdateNewAttributeInManagedObjectCallback), pWaveManagedObjectUpdateContext);

    pUpdateNewAttributeInManagedObjectContext->setAttributeVector (pWaveManagedObjectUpdateContext->getAttributes ());

    pWaveManagedObject->addNewAttributeToBeUpdatedForUpdate (pUpdateNewAttributeInManagedObjectContext);
}

void WaveManagedObjectUpdateWorker::updateUpdateNewAttributeInManagedObjectCallback (UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext)
{
    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pUpdateNewAttributeInManagedObjectContext->getPCallerContext ());
    WaveManagedObject              *pWaveManagedObject              = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    ResourceId                      status                          = pUpdateNewAttributeInManagedObjectContext->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR , "WaveManagedObjectUpdateWorker::createUpdateNewAttributeInManagedObjectCallback adding new attribute Fails");

        pWaveManagedObjectUpdateContext->executeNextStep (status);
        return;
    }

    vector<string>   newAttributeNames     = pUpdateNewAttributeInManagedObjectContext->getNewAttributeNames ();
    UI32             numberOfNewAttributes = newAttributeNames.size ();

    for (UI32 i = 0; i < numberOfNewAttributes; i++)
    {
        //add each attribute in the attribute vector of Main Context
        Attribute *pAttribute = pWaveManagedObject->getAttributeByName (newAttributeNames[i]);

        Attribute *pClonedAttribute = pAttribute->clone ();

        pWaveManagedObject->addAttributeToBeUpdated (pAttribute->getAttributeName ());

        pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);
    }

    pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveManagedObjectUpdateWorker::updatePostUpdateManagedObjectStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePostUpdateManagedObjectStep : Entering ...");
    
    if (!pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePostUpdateManagedObjectStep : skipping for  Local Service Global MO");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStep : Entering ...");

    if (pWaveManagedObjectUpdateContext->getIsBackendUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStep : skipping for local service");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveAsynchronousContext *pWaveAsynchronousContext     = new WaveAsynchronousContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStepCallback), pWaveManagedObjectUpdateContext);
    WaveManagedObject        *pOperateOnWaveManagedObject   = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject   ();
   
    if (NULL != pOperateOnWaveManagedObject)
    {
        pOperateOnWaveManagedObject->preUpdateHardwareStepForOperateOnWaveManagedObject (pWaveAsynchronousContext);
    }
	else
	{
		delete pWaveAsynchronousContext;
		pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_ERROR);
		
	}

    return;
}

void WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStepCallback (WaveAsynchronousContext *pWaveAsynchronousContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStepCallBack : Entering ...");

    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pWaveAsynchronousContext->getPCallerContext ());
    ResourceId                      status                          = pWaveAsynchronousContext->getCompletionStatus ();

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "WaveManagedObjectUpdateWorker::updatePreUpdateHardwareStepCallback completion status " + FrameworkToolKit::localize (status));
    }

    delete pWaveAsynchronousContext;
    pWaveManagedObjectUpdateContext->executeNextStep (status);
}

void WaveManagedObjectUpdateWorker::updateUpdateHardwareStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateUpdateHardwareStep : Entering ...");

    if (!pWaveManagedObjectUpdateContext->getIsBackendUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updateUpdateHardwareStep : skipping for Global Service");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject          *pOperateOnWaveManagedObject  = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject   ();

    if (NULL != pOperateOnWaveManagedObject)
    {    
        GetHardwareConfigurationDetailsForUpdateContext *pGetHardwareConfigurationDetailsForUpdateContext = new GetHardwareConfigurationDetailsForUpdateContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveManagedObjectUpdateWorker::updateUpdateHardwareStepCallBack), pWaveManagedObjectUpdateContext);

        pGetHardwareConfigurationDetailsForUpdateContext->setAttributeNames      (pWaveManagedObjectUpdateContext->getAttributeNames ());
        pGetHardwareConfigurationDetailsForUpdateContext->setAttributeValues     (pWaveManagedObjectUpdateContext->getAttributeValues ());
        pGetHardwareConfigurationDetailsForUpdateContext->setAttributeVector     (pWaveManagedObjectUpdateContext->getAttributes ());

        pOperateOnWaveManagedObject->getHardwareConfigurationDetailsForUpdate (pGetHardwareConfigurationDetailsForUpdateContext);

    }
    else
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_ERROR);
    }
}

void WaveManagedObjectUpdateWorker::updateUpdateHardwareStepCallBack (GetHardwareConfigurationDetailsForUpdateContext *pGetHardwareConfigurationDetailsForUpdateContext)
{
    UnifiedClientUpdateMessage     *pMessage                        = NULL;
    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pGetHardwareConfigurationDetailsForUpdateContext->getPCallerContext ());
    ResourceId                      status                          = pGetHardwareConfigurationDetailsForUpdateContext->getCompletionStatus ();
    WaveManagedObject              *pOperateOnWaveManagedObject     = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject   ();
    string                          clientNameToSend;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "createUpdateHardwareStepCallBack: failed to get the hardware details");

        pWaveManagedObjectUpdateContext->executeNextStep (status);
        return;
    }


    if (pGetHardwareConfigurationDetailsForUpdateContext->getIsUpdateBackend ()) 
    {
        if (NULL != pOperateOnWaveManagedObject)
        {
            //Set the Managed object Name
            pGetHardwareConfigurationDetailsForUpdateContext->setManagedObjectName (pOperateOnWaveManagedObject->getObjectClassName ());

            //Populate the key attributes of an MO for the backend to identify that update/delete is performed on which MO
            populateManagedObjectKeyAttributes (pWaveManagedObjectUpdateContext);

            //Populate the parent key attributes in case of composition. In case of Composition updation of the parent key alone is sufficient as part of child MO update/delete to the backend

            trace (TRACE_LEVEL_INFO, "child user tag is not zero");
            populateParentKeyAttributes (pWaveManagedObjectUpdateContext);

            //Populate the realated attributes if they are not modified
            //This is required by the backend to use common layer.
            clientNameToSend = getClientNameToSendAndPopulateRelatedAttributes (pGetHardwareConfigurationDetailsForUpdateContext);
            waveAssert ("" != clientNameToSend, __FILE__, __LINE__);

            pGetHardwareConfigurationDetailsForUpdateContext->setAttributeVector (pWaveManagedObjectUpdateContext->getAttributes ());
            pGetHardwareConfigurationDetailsForUpdateContext->setParentManagedObjectNames (pWaveManagedObjectUpdateContext->getParentManagedObjectNames());

            pMessage = new UnifiedClientUpdateMessage (pGetHardwareConfigurationDetailsForUpdateContext);

            pMessage->setConfigReplayInProgressFlag (pWaveManagedObjectUpdateContext->getConfigReplayInProgressFlag());

            trace (TRACE_LEVEL_INFO, "Sending to Client " + clientNameToSend);

            status = sendSynchronouslyToWaveClient (clientNameToSend, pMessage);

            if (status == WAVE_MESSAGE_SUCCESS)
            {
                status = pMessage->getCompletionStatus ();

                WaveObjectManagerUpdateWaveManagedObjectMessage *pUpdateMessage = reinterpret_cast<WaveObjectManagerUpdateWaveManagedObjectMessage *> (pWaveManagedObjectUpdateContext->getPWaveMessage());
                pUpdateMessage->setWarningResourceId (pMessage->getWarningResourceId());

                pWaveManagedObjectUpdateContext->setAttributeNamesFromBackend (pMessage->getAttributeNamesFromBackend ());
                pWaveManagedObjectUpdateContext->setAttributeValuesFromBackend (pMessage->getAttributeValuesFromBackend ());
            }
            else
            {
                trace (TRACE_LEVEL_INFO, string("WaveManagedObjectUpdateWorker::updateUpdateHardwareStepCallBack : Error while sending Message to client " + clientNameToSend + " with status : " + FrameworkToolKit::localize (status)));
            }
         
            if (0 != pMessage->getWarningResourceId())
            {
                trace (TRACE_LEVEL_INFO, string("WaveManagedObjectUpdateWorker::updateUpdateHardwareStepCallBack : WarningResourceId = " ) + FrameworkToolKit::localize (pMessage->getWarningResourceId()));
            }

            delete pMessage;
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, "WaveManagedObjectUpdateWorker::updateUpdateHardwareStep : Could not get the Operate on Managed Object");
            status = WAVE_MESSAGE_ERROR;
        }
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, "WaveManagedObjectUpdateWorker::updateUpdateHardwareStep : message NOT sent to backend");
    }

    pWaveManagedObjectUpdateContext->executeNextStep (status);
}

void WaveManagedObjectUpdateWorker::updatePostUpdateHardwareStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePostUpdateHardwareStep : Entering ...");
    
    if (!pWaveManagedObjectUpdateContext->getIsBackendUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::updatePostUpdateHardwareStep : Global Service");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void WaveManagedObjectUpdateWorker::updateAttributesPostUpdateHardwareStep (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    if (pWaveManagedObjectUpdateContext->getIsBackendUpdateRequired() && pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace(TRACE_LEVEL_DEVEL,"WaveManagedObjectUpdateWorker::updateAttributesPostUpdateHardwareStep ..");

        vector<string>     attributeNamesFromBackend  = pWaveManagedObjectUpdateContext->getAttributeNamesFromBackend  ();
        vector<string>     attributeValuesFromBackend = pWaveManagedObjectUpdateContext->getAttributeValuesFromBackend ();
        WaveManagedObject *pWaveManagedObject         = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    
        waveAssert (attributeNamesFromBackend.size() == attributeValuesFromBackend.size(), __FILE__, __LINE__);          
        waveAssert (pWaveManagedObject != NULL, __FILE__, __LINE__);
        
        for (UI32 i = 0; i < attributeNamesFromBackend.size(); i++)
        {
            Attribute *pAttribute = pWaveManagedObject->getAttributeByName (attributeNamesFromBackend[i]);
        
            waveAssert (pAttribute != NULL, __FILE__, __LINE__);

            pAttribute->fromString (attributeValuesFromBackend[i]);
        }
    }

    pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS); 
    return;
}

void WaveManagedObjectUpdateWorker::updateRelationshipMessageHandler (WaveObjectManagerUpdateRelationshipMessage  *pWaveObjectManagerUpdateRelationshipMessage)
{
    string      parentClassName;
    string      childClassName;
    string      relationshipName;
    ObjectId    parentObjectId;
    ObjectId    childObjectId;
    bool        isAddingRelationship = true;

    waveAssert (NULL != pWaveObjectManagerUpdateRelationshipMessage, __FILE__, __LINE__);

    pWaveObjectManagerUpdateRelationshipMessage->getRelationshipVariables (parentClassName, childClassName, relationshipName, parentObjectId, childObjectId);
    isAddingRelationship = pWaveObjectManagerUpdateRelationshipMessage->getIsAddingRelationship ();

    startTransaction ();

    if (true == isAddingRelationship)
    {
        addRelationship  (parentClassName, childClassName, relationshipName, parentObjectId, childObjectId);
    }
    else
    {
        deleteRelationship (parentClassName, childClassName, relationshipName, parentObjectId, childObjectId);
    }

    ResourceId status = commitTransaction ();

    if (FRAMEWORK_SUCCESS != status)
    {
        pWaveObjectManagerUpdateRelationshipMessage->setCompletionStatus (status);
    }
    else
    {
        pWaveObjectManagerUpdateRelationshipMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    }

    reply (pWaveObjectManagerUpdateRelationshipMessage);
}

void WaveManagedObjectUpdateWorker::commitWaveManagedObjectBeforeUpdatingBackend (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::commitWaveManagedObjectBeforeUpdatingBackend : Entering ...");
    
    if (!pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::commitWaveManagedObjectBeforeUpdatingBackend : skipping for  Local Service Global MO");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    vector<Attribute*> attributes                = pWaveManagedObjectUpdateContext->getAttributes ();

    bool updateHardwareBeforeManagedObject       = pWaveManagedObject->updateHardwareBeforeWaveManagedObject (attributes);

    if (false == updateHardwareBeforeManagedObject)
    {
        prismLinearSequencerCommitTransactionStep (pWaveManagedObjectUpdateContext);
    }
    else
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

}

void WaveManagedObjectUpdateWorker::commitWaveManagedObjectAfterUpdatingBackend (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::commitWaveManagedObjectAfterUpdatingBackend : Entering ...");

    if (!pWaveManagedObjectUpdateContext->getIsDatabaseUpdateRequired())
    {
        trace (TRACE_LEVEL_DEVEL, "WaveManagedObjectUpdateWorker::commitWaveManagedObjectAfterUpdatingBackend : skipping for Local Service & Global MO");
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;        
    }

    WaveManagedObject *pWaveManagedObject        = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject ();
    vector<Attribute*> attributes                = pWaveManagedObjectUpdateContext->getAttributes ();

    bool updateHardwareBeforeManagedObject       = pWaveManagedObject->updateHardwareBeforeWaveManagedObject (attributes);

    if (true == updateHardwareBeforeManagedObject)
    {
        prismLinearSequencerCommitTransactionStep (pWaveManagedObjectUpdateContext);
    }
    else
    {
        pWaveManagedObjectUpdateContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    }

}

void WaveManagedObjectUpdateWorker::populateManagedObjectKeyAttributes (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    WaveManagedObject              *pOperateOnWaveManagedObject     = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject   ();
    vector <string>                 keyNames;
    vector <string>::iterator       keyElement;

    OrmRepository::getUserDefinedKeyCombinationWithTypesForTable (pOperateOnWaveManagedObject->getObjectClassName (), keyNames);

    for (keyElement = keyNames.begin (); keyElement != keyNames.end (); keyElement++)
    {
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

            WaveManagedObject *associatedManagedObject = queryManagedObject (*((ObjectId*)(pAttribute->getPData ())));

            waveAssert (NULL != associatedManagedObject, __FILE__, __LINE__);

            Attribute *pAssociatedAttribute = associatedManagedObject->getAttributeByName (associatedKeyNames[0]);

            /* Create a clone of the associated key and set the attribute name as parent attribute name and append it to the attribute vector */

            pClonedAttribute = pAssociatedAttribute->clone ();

            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

            pClonedAttribute->setAttributeName (pAttribute->getAttributeName ());

            pWaveManagedObjectUpdateContext->addManagedObjectForGarbageCollection (associatedManagedObject);
        }
        else
        {
            pClonedAttribute = pAttribute->clone ();

            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);
        }

        pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);
    }
}

void WaveManagedObjectUpdateWorker::populateParentKeyAttributes (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext)
{
    vector<string>    parentMONames;
    vector<WaveManagedObject *> parentMO;

    WaveManagedObject *pOperateOnWaveManagedObject = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject();
    // Update the parent key attributes to be sent to the backend.
            
    while (ObjectId::NullObjectId != pOperateOnWaveManagedObject->getOwnerManagedObjectId())
    {       
        //Get Parent Managed Object
        pOperateOnWaveManagedObject = queryManagedObject (pOperateOnWaveManagedObject->getOwnerManagedObjectId());
        //add Parent MO Name into the vector.
        parentMONames.push_back(pOperateOnWaveManagedObject->getObjectClassName());
        parentMO.push_back(pOperateOnWaveManagedObject);
            
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
            pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);
        }
    }

    pWaveManagedObjectUpdateContext->setParentManagedObjectNames (parentMONames);

    pWaveManagedObjectUpdateContext->addManagedObjectsForGarbageCollection (parentMO);
}

string WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes (GetHardwareConfigurationDetailsForUpdateContext *pGetHardwareConfigurationDetailsForUpdateContext)
{
    WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext = reinterpret_cast<WaveManagedObjectUpdateContext *> (pGetHardwareConfigurationDetailsForUpdateContext->getPCallerContext ());
    WaveManagedObject              *pOperateOnWaveManagedObject     = pWaveManagedObjectUpdateContext->getPOperateOnWaveManagedObject   ();
    map <string, UI32>              attributeNamesGroupCodeMap      = pGetHardwareConfigurationDetailsForUpdateContext->getAttributeNamesGroupCodeMap ();
    map <UI32, string>              groupCodeBackendNamesMap        = pGetHardwareConfigurationDetailsForUpdateContext->getGroupCodeBackendNamesMap ();
    map <UI32, vector <string> >    groupCodeAttributeGroupMap      = pGetHardwareConfigurationDetailsForUpdateContext->getGroupCodeAttributeGroupMap ();
    map <string, string>            attributeNameBackendNameMap     = pGetHardwareConfigurationDetailsForUpdateContext->getAttributeNameBackendNameMap ();
    vector<string>                  attributeNames                  = pWaveManagedObjectUpdateContext->getAttributeNames ();
    vector <Attribute *>            attributeVector                 = pWaveManagedObjectUpdateContext->getAttributes ();
    vector <string>                 attributeNamesGroup;
    UI32                            groupCode                       = 0;
    bool                            attributeFound                  = false;
    string                          clientName;
    string                          attributeName;

    //Get the last attribute name in the attributeNames vector if the vector is of size 0, get the first attribute in the attributeVector
    //This is needed to support key attribute belonging to multiple groups

    if (0 < attributeNames.size ())
    {
        if (!(attributeNames.back ()).empty ())
        {
            attributeName = attributeNames.back ();
        }
        else
        {
            trace (TRACE_LEVEL_FATAL, string("WaveManagedObjectCreateWorker::getClientNameToSendAndPopulateRelatedAttributes: Could not find any element in the attributeNames vector"));
            waveAssert (false, __FILE__, __LINE__);
        }
    }
    else
    {
        waveAssert (0 != attributeVector.size (), __FILE__, __LINE__);
        attributeName = ((attributeVector) [0])->getAttributeName ();
    }
    
    trace (TRACE_LEVEL_DEVEL, string("WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes: AttributeName = ") + attributeName);

    /*//Find the backend Name corresponding to the attribute
    //If we find an entry in this map it indicates that the plugin does not want grouping and hence we will only get the client Name and return
    if (attributeNameBackendNameMap.end () != attributeNameBackendNameMap.find (attributeName))
    {
        clientName = attributeNameBackendNameMap [attributeName];
        trace (TRACE_LEVEL_DEVEL, string("WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes: ClientName = ") + attributeName);

        //set the groupCode to default value
        pGetHardwareConfigurationDetailsForUpdateContext->setGroupCode (0);
        return (clientName);
    }*/

    //Find the groupCode corresponding to the attribute in the map
    if (attributeNamesGroupCodeMap.end () != attributeNamesGroupCodeMap.find (attributeName))
    {

        groupCode = attributeNamesGroupCodeMap [attributeName];
        trace (TRACE_LEVEL_DEVEL, string("WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes: groupCode = ") + groupCode);
        
        //set the groupCode
        pGetHardwareConfigurationDetailsForUpdateContext->setGroupCode (groupCode);

    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string("WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes: Could not find the groupCode corresponding to the attributeName = ") + attributeName);
        waveAssert (false, __FILE__, __LINE__);
    }

    //Get the Vector of Attribute Names that belong to a group corresponding to the groupCode
    if (groupCodeAttributeGroupMap.end () != groupCodeAttributeGroupMap.find (groupCode))
    {
        attributeNamesGroup = groupCodeAttributeGroupMap [groupCode];
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string("WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes: Could not find the attributeGroup corresponding to the groupCode = ") + groupCode);
        waveAssert (false, __FILE__, __LINE__);
    }

    //Check if the attribute names in the group are already present in the vector of Attributes, which indicates those attributes are modified
    //For the attributes which are not found in the vector of Attributes, populate from MO queried from the DB.

    for (UI32 attributeNamesGroupIterator = 0; attributeNamesGroupIterator < attributeNamesGroup.size (); attributeNamesGroupIterator++)
    {
        for (UI32 attributeVectorIterator = 0; attributeVectorIterator < attributeVector.size (); attributeVectorIterator++)
        {
            if (attributeNamesGroup [attributeNamesGroupIterator] == (attributeVector [attributeVectorIterator])->getAttributeName ())
            {
                attributeFound = true;
                break;
            }
        }

        if (!attributeFound)
        {
            Attribute* pAttribute = pOperateOnWaveManagedObject->getAttributeByName (attributeNamesGroup [attributeNamesGroupIterator]);

            waveAssert (NULL != pAttribute, __FILE__, __LINE__);

            Attribute *pClonedAttribute = pAttribute->clone ();

            waveAssert (NULL != pClonedAttribute, __FILE__, __LINE__);

            pWaveManagedObjectUpdateContext->addToAttributeVector (pClonedAttribute);

        }
        else
        {
            attributeFound = false;
        }
    }

    //Return the client name to send based on the opcode.
    if (groupCodeBackendNamesMap.end () != groupCodeBackendNamesMap.find (groupCode))
    {
        clientName = groupCodeBackendNamesMap [groupCode];
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string("WaveManagedObjectUpdateWorker::getClientNameToSendAndPopulateRelatedAttributes: Could not find the backendName corresponding to the groupCode = ") + groupCode);
        waveAssert (false, __FILE__, __LINE__);
    }

    return (clientName);
}

}

