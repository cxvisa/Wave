/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManagerCommitTransactionContext.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

PrismElement::PrismElement (WaveObjectManager *pWaveObjectManager)
    : m_pWaveObjectManager (pWaveObjectManager)
{
    if (NULL == m_pWaveObjectManager)
    {
        // THIS MUST NEVER HAPPEN
        // We cannot use trace or prismAssert here since they are abstract virtual here
        cerr << "Prismelement::Prismelement : You cannot create a PrismElement with NULL WaveObjectManager." << endl;
        assert (0);
    }
}

PrismElement::PrismElement (const PrismElement &prismElement)
{
// FIXME : sagar : Once we the cluster service fixes the NodeManagedObject copying by value into its vectors, enable the fatal statements below.

#if 0
    WaveNs::trace (TRACE_LEVEL_FATAL, "PrismElement::PrismElement : Copy Constructing a Prism Element does not make sense and hence not allowed.");
    WaveNs::prismAssert (false, __FILE__, __LINE__);
#else
    m_pWaveObjectManager = prismElement.m_pWaveObjectManager;
#endif
}

PrismElement::~PrismElement ()
{
}

PrismElement &PrismElement::operator = (const PrismElement &prismElement)
{
    WaveNs::trace (TRACE_LEVEL_FATAL, "PrismElement::operator = : Assigning to a Prism Element does not make sense and hence not allowed.");
    WaveNs::prismAssert (false, __FILE__, __LINE__);

    return (*this);
}

/**
 * Note, if any transaction was started before calling this step, and not committed,
 * the transaction will be commited to preserve the semantics, even though if there is
 * no db update by the step and then the reply will happen as usual.
 */
void PrismElement::prismLinearSequencerSucceededStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismLinearSequencerSucceededStep : Entering ...");

    WaveMessage             *pWaveMessage             = pPrismLinearSequencerContext->getPWaveMessage ();
    PrismAsynchronousContext *pPrismAsynchronousContext = pPrismLinearSequencerContext->getPPrismAsynchronousContext ();

    if (true == (pPrismLinearSequencerContext->getIsHoldAllRequested ()))
    {
        pPrismLinearSequencerContext->unholdAll ();
    }

    ResourceId status = FRAMEWORK_SUCCESS;

    if (true == (pPrismLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pPrismLinearSequencerContext->setIsTransactionStartedByMe (false);

        // commit the transaction to preserve the semantics of the executeSuccessStep and if the transaction
        // has no data to be committed, framework will immediately return without having to go to DB.
        status = commitTransaction();
    }

    if (FRAMEWORK_SUCCESS == status)
    {
       status = WAVE_MESSAGE_SUCCESS;
    }
    else
    {
        status = WAVE_COMMIT_TRANSACTION_FAILED;
    }

    if (NULL != pWaveMessage)
    {
        pWaveMessage->setCompletionStatus (status);
        reply (pWaveMessage);
    }
    else if (NULL != pPrismAsynchronousContext)
    {
        pPrismAsynchronousContext->setCompletionStatus (status);
        pPrismAsynchronousContext->callback ();
    }

    delete pPrismLinearSequencerContext;
}

void PrismElement::prismLinearSequencerFailedStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismLinearSequencerFailedStep : Entering ...");

    WaveMessage             *pWaveMessage             = pPrismLinearSequencerContext->getPWaveMessage ();
    PrismAsynchronousContext *pPrismAsynchronousContext = pPrismLinearSequencerContext->getPPrismAsynchronousContext ();

    if (true == (pPrismLinearSequencerContext->getIsHoldAllRequested ()))
    {
        pPrismLinearSequencerContext->unholdAll ();
    }

    if (true == (pPrismLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pPrismLinearSequencerContext->setIsTransactionStartedByMe (false);
        rollbackTransaction ();
    }

    if (NULL != pWaveMessage)
    {
        pWaveMessage->setCompletionStatus (pPrismLinearSequencerContext->getCompletionStatus ());
        reply (pWaveMessage);
    }
    else if (NULL != pPrismAsynchronousContext)
    {
        pPrismAsynchronousContext->setCompletionStatus (pPrismLinearSequencerContext->getCompletionStatus ());
        pPrismAsynchronousContext->callback ();
    }

    delete pPrismLinearSequencerContext;
}

void PrismElement::prismLinearSequencerStartTransactionStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismLinearSequencerStartTransactionStep : Entering ...");

    if (false == (isTransactionInProgress ()))
    {
        pPrismLinearSequencerContext->setIsTransactionStartedByMe (true);

        startTransaction ();
    }

    pPrismLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void PrismElement::prismLinearSequencerCommitTransactionStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismLinearSequencerCommitTransactionStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == (pPrismLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pPrismLinearSequencerContext->setIsTransactionStartedByMe (false);

        WaveObjectManagerCommitTransactionContext commitTransactionContext (pPrismLinearSequencerContext);

        status = commitTransaction (&commitTransactionContext);

        if (FRAMEWORK_SUCCESS == status)
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pPrismLinearSequencerContext->executeNextStep (status);
}

/**
 * Note, if any transaction was started before calling this step, and not committed,
 * the transaction will be commited to preserve the semantics, even though if there is
 * no db update by the step and then the reply will happen as usual.
 */
ResourceId PrismElement::prismSynchronousLinearSequencerSucceededStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismSynchronousLinearSequencerSucceededStep : Entering ...");

    WaveMessage             *pWaveMessage             = pPrismSynchronousLinearSequencerContext->getPWaveMessage ();
    PrismAsynchronousContext *pPrismAsynchronousContext = pPrismSynchronousLinearSequencerContext->getPPrismAsynchronousContext ();
    ResourceId                completionStatus          = pPrismSynchronousLinearSequencerContext->getCompletionStatus ();

    if (true == (pPrismSynchronousLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pPrismSynchronousLinearSequencerContext->setIsTransactionStartedByMe (false);

        // commit the transaction to preserve the semantics of the WAVE_SEQUENCER_SKIP_TO_SUCCESS_STEP return code and if
        // the transaction has no data to be committed, framework will immediately return without having to go to DB.
        WaveObjectManagerCommitTransactionContext commitTransactionContext (pPrismSynchronousLinearSequencerContext);

        ResourceId status = commitTransaction (&commitTransactionContext);

        if (FRAMEWORK_SUCCESS != status)
        {
            completionStatus = WAVE_COMMIT_TRANSACTION_FAILED;
        }
    }

    if (NULL != pWaveMessage)
    {
        pWaveMessage->setCompletionStatus (completionStatus);
        reply (pWaveMessage);
    }
    else if (NULL != pPrismAsynchronousContext)
    {
        pPrismAsynchronousContext->setCompletionStatus (completionStatus);
        pPrismAsynchronousContext->callback ();
    }

    delete pPrismSynchronousLinearSequencerContext;
    return (completionStatus);
}

ResourceId PrismElement::prismSynchronousLinearSequencerFailedStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismSynchronousLinearSequencerFailedStep : Entering ...");

    WaveMessage             *pWaveMessage             = pPrismSynchronousLinearSequencerContext->getPWaveMessage ();
    PrismAsynchronousContext *pPrismAsynchronousContext = pPrismSynchronousLinearSequencerContext->getPPrismAsynchronousContext ();
    ResourceId                completionStatus          = pPrismSynchronousLinearSequencerContext->getCompletionStatus ();

    if (true == (pPrismSynchronousLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pPrismSynchronousLinearSequencerContext->setIsTransactionStartedByMe (false);
        rollbackTransaction ();
    }

    if (NULL != pWaveMessage)
    {
        pWaveMessage->setCompletionStatus (completionStatus);
        reply (pWaveMessage);
    }
    else if (NULL != pPrismAsynchronousContext)
    {
        pPrismAsynchronousContext->setCompletionStatus (completionStatus);
        pPrismAsynchronousContext->callback ();
    }

    delete pPrismSynchronousLinearSequencerContext;
    return (completionStatus);
}

ResourceId PrismElement::prismSynchronousLinearSequencerStartTransactionStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismLinearSequencerStartTransactionStep : Entering ...");

    if (false == (isTransactionInProgress ()))
    {
        pPrismSynchronousLinearSequencerContext->setIsTransactionStartedByMe (true);

        startTransaction ();
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PrismElement::prismSynchronousLinearSequencerCommitTransactionStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PrismElement::prismLinearSequencerCommitTransactionStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == (pPrismSynchronousLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pPrismSynchronousLinearSequencerContext->setIsTransactionStartedByMe (false);

        WaveObjectManagerCommitTransactionContext commitTransactionContext (pPrismSynchronousLinearSequencerContext);

        status = commitTransaction (&commitTransactionContext);

        if (FRAMEWORK_SUCCESS == status)
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    return (status);
}

WaveObjectManager *PrismElement::getPWaveObjectManager () const
{
    return (m_pWaveObjectManager);
}

WaveManagedObject *PrismElement::createManagedObjectInstance (const string &managedClassName)
{
    trace (TRACE_LEVEL_ERROR, "PrismElement::createManagedObjectInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    trace (TRACE_LEVEL_ERROR, "PrismElement::createManagedObjectInstance : ObjectManagers and Workers MUST overwrite this virtual function.");
    return (NULL);
}

WaveMessage *PrismElement::createMessageInstance (const UI32 &operationCode)
{
    trace (TRACE_LEVEL_ERROR, "PrismElement::createMessageInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    trace (TRACE_LEVEL_ERROR, "PrismElement::createMessageInstance : ObjectManagers and Workers MUST overwrite this virtual function.");
    return (NULL);
}

void PrismElement::setPWaveObjectManager (WaveObjectManager *pWaveObjectManager)
{
    m_pWaveObjectManager = pWaveObjectManager;
}

}
