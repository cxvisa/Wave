/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PolicyObjectManagerInitializationWorker.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Policy/CategoryManagedObject.h"
#include "Policy/PfrThresholdTemplateManagedObject.h"
#include "Policy/PolicyObjectManager.h"
#include "Policy/PolicyObjectManagerInitializationContext.h"
#include "Framework/Utils/StringUtils.h"
#include "Policy/ApplicationManagedObject.h"
#include "Policy/SubCategoryManagedObject.h"

namespace WaveNs
{

PolicyObjectManagerInitializationWorker::PolicyObjectManagerInitializationWorker (PolicyObjectManager *pPolicyObjectManager)
    : WaveWorker (pPolicyObjectManager)
{
}

PolicyObjectManagerInitializationWorker::~PolicyObjectManagerInitializationWorker ()
{
}

void PolicyObjectManagerInitializationWorker::install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    WaveBootReason waveBootReason = pWaveAsynchronousContextForBootPhases->getBootReason ();

    if (WAVE_BOOT_FIRST_TIME_BOOT == waveBootReason)
    {
        PrismLinearSequencerStep sequencerSteps[] =
        {
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installLoadNbar2FileStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installLoadPfrThresholdsFileStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installComputeCategoriesStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::prismLinearSequencerStartTransactionStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installCreateCategoriesStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installCreatePfrThresholdsStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installCreateSubCategoriesStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::installCreateApplicationsStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::prismLinearSequencerCommitTransactionStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::prismLinearSequencerSucceededStep),
            reinterpret_cast<PrismLinearSequencerStep> (&PolicyObjectManagerInitializationWorker::prismLinearSequencerFailedStep)
        };

        PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext = new PolicyObjectManagerInitializationContext (pWaveAsynchronousContextForBootPhases, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

        pPolicyObjectManagerInitializationContext->holdAll ();
        pPolicyObjectManagerInitializationContext->start ();
    }
    else
    {
        pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        pWaveAsynchronousContextForBootPhases->callback            ();
    }
}

void PolicyObjectManagerInitializationWorker::installLoadNbar2FileStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    pPolicyObjectManagerInitializationContext->loadNbar2 ();

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PolicyObjectManagerInitializationWorker::installLoadPfrThresholdsFileStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    pPolicyObjectManagerInitializationContext->loadPfrThresholdTemplateRoot ();

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PolicyObjectManagerInitializationWorker::installComputeCategoriesStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    pPolicyObjectManagerInitializationContext->computeAdjustedCategoryNames ();

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PolicyObjectManagerInitializationWorker::installCreateCategoriesStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    set<string> adjustedCategoryNames = pPolicyObjectManagerInitializationContext->getAdjustedCategoryNames ();

    set<string>::const_iterator element    = adjustedCategoryNames.begin ();
    set<string>::const_iterator endElement = adjustedCategoryNames.end   ();

    while (endElement != element)
    {
        string               adjustedCategoryName = *element;
        PolicyObjectManager *pPolicyObjectManager = dynamic_cast<PolicyObjectManager *> (getPWaveObjectManager ());

        prismAssert (pPolicyObjectManager, __FILE__, __LINE__);

        CategoryManagedObject *pNewCategoryManagedObject = new CategoryManagedObject (pPolicyObjectManager);

        prismAssert (NULL != pNewCategoryManagedObject, __FILE__, __LINE__);

        pNewCategoryManagedObject->setName (adjustedCategoryName);

        pPolicyObjectManagerInitializationContext->addCategoryNameToObjectIdMapping (pNewCategoryManagedObject->getName (), pNewCategoryManagedObject->getObjectId ());

        pPolicyObjectManagerInitializationContext->addManagedObjectForGarbageCollection (pNewCategoryManagedObject);

        element++;
    }

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PolicyObjectManagerInitializationWorker::installCreatePfrThresholdsStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    PfrThresholdTemplateRoot &pfrThresholdTemplateRoot = pPolicyObjectManagerInitializationContext->getPfrThresholdTemplateRoot ();

    vector<PfrThresholdTemplateElement *> &pfrThresholdTemplateElements         = pfrThresholdTemplateRoot.getPfrThresholdTemplateElements ();
    UI32                                   numberOfPfrThresholdTemplateElements = pfrThresholdTemplateElements.size ();
    UI32                                   i                                    = 0;
    PolicyObjectManager                   *pPolicyObjectManager                 = dynamic_cast<PolicyObjectManager *> (getPWaveObjectManager ());

    trace (TRACE_LEVEL_INFO, string ("PolicyObjectManagerInitializationWorker::installCreatePfrThresholdsStep : Number of Threshold Templates : ") + numberOfPfrThresholdTemplateElements);
    for (i = 0; i < numberOfPfrThresholdTemplateElements; i++)
    {
        PfrThresholdTemplateElement *pPfrThresholdTemplateElement = pfrThresholdTemplateElements[i];

        prismAssert (NULL != pPfrThresholdTemplateElement, __FILE__, __LINE__);

        string templateName        = pPfrThresholdTemplateElement->getTemplateName        ();
        SI32   lossRate            = pPfrThresholdTemplateElement->getLossRate            ();
        SI32   oneWayDelay         = pPfrThresholdTemplateElement->getOneWayDelay         ();
        SI32   jitter              = pPfrThresholdTemplateElement->getJitter              ();
        SI32   lossRatePriority    = pPfrThresholdTemplateElement->getLossRatePriority    ();
        SI32   oneWayDelayPriority = pPfrThresholdTemplateElement->getOneWayDelayPriority ();
        SI32   jitterPriority      = pPfrThresholdTemplateElement->getJitterPriority      ();

        PfrThresholdTemplateManagedObject *pPfrThresholdTemplateManagedObject = new PfrThresholdTemplateManagedObject (pPolicyObjectManager);

        prismAssert (NULL != pPfrThresholdTemplateManagedObject, __FILE__, __LINE__);

        pPfrThresholdTemplateManagedObject->setName                (templateName);
        pPfrThresholdTemplateManagedObject->setLossRate            (lossRate);
        pPfrThresholdTemplateManagedObject->setOneWayDelay         (oneWayDelay);
        pPfrThresholdTemplateManagedObject->setJitter              (jitter);
        pPfrThresholdTemplateManagedObject->setLossRatePriority    (lossRatePriority);
        pPfrThresholdTemplateManagedObject->setOneWayDelayPriority (oneWayDelayPriority);
        pPfrThresholdTemplateManagedObject->setJitterPriority      (jitterPriority);

        vector<string> subCategoryNames         = (pPfrThresholdTemplateElement->getSubCategoryCollection ()).getSubCategoryNames ();
        UI32           numberOfSubCategoryNames = subCategoryNames.size ();
        UI32           j                        = 0;

        for (j = 0; j < numberOfSubCategoryNames; j++)
        {
            pPolicyObjectManagerInitializationContext->addSubCategoryToPfrThresholdMapping (subCategoryNames[j], pPfrThresholdTemplateManagedObject->getObjectId ());
        }

        pPolicyObjectManagerInitializationContext->addManagedObjectForGarbageCollection (pPfrThresholdTemplateManagedObject);
    }

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PolicyObjectManagerInitializationWorker::installCreateSubCategoriesStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    vector<pair<string, ObjectId> > subCategoryToPfrThresholdMappings;

    pPolicyObjectManagerInitializationContext->getSubCategoryToPfrThresholdMappings (subCategoryToPfrThresholdMappings);

    UI32                 numberOfSubCategoryToPfrThresholdMappings = subCategoryToPfrThresholdMappings.size ();
    UI32                 i                                    = 0;
    PolicyObjectManager *pPolicyObjectManager                 = dynamic_cast<PolicyObjectManager *> (getPWaveObjectManager ());

    prismAssert (NULL != pPolicyObjectManager, __FILE__, __LINE__);

    trace (TRACE_LEVEL_INFO, string ("PolicyObjectManagerInitializationWorker::installCreateSubCategoriesStep : Number of Sub Categories : ") + numberOfSubCategoryToPfrThresholdMappings);

    for (i = 0; i < numberOfSubCategoryToPfrThresholdMappings; i++)
    {
        SubCategoryManagedObject *pSubCategoryManagedObject = new SubCategoryManagedObject (pPolicyObjectManager);

        prismAssert (NULL != pSubCategoryManagedObject, __FILE__, __LINE__);

        pSubCategoryManagedObject->setName                         ((subCategoryToPfrThresholdMappings[i]).first);
        pSubCategoryManagedObject->setPfrThresholdTemplateObjectId ((subCategoryToPfrThresholdMappings[i]).second);

        pPolicyObjectManagerInitializationContext->addSubCategoryNameToObjectIdMapping (pSubCategoryManagedObject->getName (), pSubCategoryManagedObject->getObjectId ());

        pPolicyObjectManagerInitializationContext->addManagedObjectForGarbageCollection (pSubCategoryManagedObject);
    }

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PolicyObjectManagerInitializationWorker::installCreateApplicationsStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext)
{
    Nbar2                       &nbar2            = pPolicyObjectManagerInitializationContext->getNbar2 ();
    set<string>                  allProtocolNames = nbar2.getAllProtocolNames ();
    set<string>::const_iterator  element          = allProtocolNames.begin ();
    set<string>::const_iterator  endElement       = allProtocolNames.end ();

    PolicyObjectManager *pPolicyObjectManager = dynamic_cast<PolicyObjectManager *> (getPWaveObjectManager ());

    prismAssert (NULL != pPolicyObjectManager, __FILE__, __LINE__);

    while (endElement != element)
    {
        string                    protocolName              = *element;
        ApplicationManagedObject *pApplicationManagedObject = new ApplicationManagedObject (pPolicyObjectManager);

        prismAssert (NULL != pApplicationManagedObject, __FILE__, __LINE__);

        Nbar2Protocol *pNbar2Protocol = nbar2.getNbar2Protocol (protocolName);

        prismAssert (NULL != pNbar2Protocol, __FILE__, __LINE__);

        pApplicationManagedObject->loadFromNbar2Protocol (*pNbar2Protocol);

        string   categoryName        = (pNbar2Protocol->getAttributes ()).getAdjustedCategoryName ();
        string   subCategoryName     = (pNbar2Protocol->getAttributes ()).getSubCategory          ();

        ObjectId categoryObjectId    = pPolicyObjectManagerInitializationContext->getCategoryObjectId    (categoryName);
        ObjectId subCategoryObjectId = pPolicyObjectManagerInitializationContext->getSubCategoryObjectId (subCategoryName);

        pApplicationManagedObject->setCategoryObjectId    (categoryObjectId);
        pApplicationManagedObject->setSubCategoryObjectId (subCategoryObjectId);

        pPolicyObjectManagerInitializationContext->addManagedObjectForGarbageCollection (pApplicationManagedObject);

        element++;
    }

    pPolicyObjectManagerInitializationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
