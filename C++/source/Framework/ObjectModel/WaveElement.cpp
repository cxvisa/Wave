/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManagerCommitTransactionContext.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

#include "Framework/Messaging/LightHouse/LightPulse.h"
namespace WaveNs
{

WaveElement::WaveElement (WaveObjectManager *pWaveObjectManager)
    : m_pWaveObjectManager (pWaveObjectManager)
{
    if (NULL == m_pWaveObjectManager)
    {
        // THIS MUST NEVER HAPPEN
        // We cannot use trace or waveAssert here since they are abstract virtual here
        cerr << "Waveelement::Waveelement : You cannot create a WaveElement with NULL WaveObjectManager." << endl;
        assert (0);
    }
}

WaveElement::WaveElement (const WaveElement &waveElement)
{
// FIXME : sagar : Once we the cluster service fixes the NodeManagedObject copying by value into its vectors, enable the fatal statements below.

#if 0
    WaveNs::trace (TRACE_LEVEL_FATAL, "WaveElement::WaveElement : Copy Constructing a Wave Element does not make sense and hence not allowed.");
    WaveNs::waveAssert (false, __FILE__, __LINE__);
#else
    m_pWaveObjectManager = waveElement.m_pWaveObjectManager;
#endif
}

WaveElement::~WaveElement ()
{
}

WaveElement &WaveElement::operator = (const WaveElement &waveElement)
{
    WaveNs::trace (TRACE_LEVEL_FATAL, "WaveElement::operator = : Assigning to a Wave Element does not make sense and hence not allowed.");
    WaveNs::waveAssert (false, __FILE__, __LINE__);

    return (*this);
}

/**
 * Note, if any transaction was started before calling this step, and not committed,
 * the transaction will be commited to preserve the semantics, even though if there is
 * no db update by the step and then the reply will happen as usual.
 */
void WaveElement::waveLinearSequencerSucceededStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveLinearSequencerSucceededStep : Entering ...");

    WaveMessage             *pWaveMessage             = pWaveLinearSequencerContext->getPWaveMessage ();
    WaveAsynchronousContext *pWaveAsynchronousContext = pWaveLinearSequencerContext->getPWaveAsynchronousContext ();

    if (true == (pWaveLinearSequencerContext->getIsHoldAllRequested ()))
    {
        pWaveLinearSequencerContext->unholdAll ();
    }

    ResourceId status = FRAMEWORK_SUCCESS;

    if (true == (pWaveLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pWaveLinearSequencerContext->setIsTransactionStartedByMe (false);

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
    else if (NULL != pWaveAsynchronousContext)
    {
        pWaveAsynchronousContext->setCompletionStatus (status);
        pWaveAsynchronousContext->callback ();
    }

    delete pWaveLinearSequencerContext;
}

void WaveElement::waveLinearSequencerFailedStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveLinearSequencerFailedStep : Entering ...");

    WaveMessage             *pWaveMessage             = pWaveLinearSequencerContext->getPWaveMessage ();
    WaveAsynchronousContext *pWaveAsynchronousContext = pWaveLinearSequencerContext->getPWaveAsynchronousContext ();

    if (true == (pWaveLinearSequencerContext->getIsHoldAllRequested ()))
    {
        pWaveLinearSequencerContext->unholdAll ();
    }

    if (true == (pWaveLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pWaveLinearSequencerContext->setIsTransactionStartedByMe (false);
        rollbackTransaction ();
    }

    if (NULL != pWaveMessage)
    {
        pWaveMessage->setCompletionStatus (pWaveLinearSequencerContext->getCompletionStatus ());
        reply (pWaveMessage);
    }
    else if (NULL != pWaveAsynchronousContext)
    {
        pWaveAsynchronousContext->setCompletionStatus (pWaveLinearSequencerContext->getCompletionStatus ());
        pWaveAsynchronousContext->callback ();
    }

    delete pWaveLinearSequencerContext;
}

void WaveElement::waveLinearSequencerStartTransactionStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveLinearSequencerStartTransactionStep : Entering ...");

    if (false == (isTransactionInProgress ()))
    {
        pWaveLinearSequencerContext->setIsTransactionStartedByMe (true);

        startTransaction ();
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveElement::waveLinearSequencerCommitTransactionStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveLinearSequencerCommitTransactionStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == (pWaveLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pWaveLinearSequencerContext->setIsTransactionStartedByMe (false);

        WaveObjectManagerCommitTransactionContext commitTransactionContext (pWaveLinearSequencerContext);

        status = commitTransaction (&commitTransactionContext);

        if (FRAMEWORK_SUCCESS == status)
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

/**
 * Note, if any transaction was started before calling this step, and not committed,
 * the transaction will be committed to preserve the semantics, even though if there is
 * no db update by the step and then the reply will happen as usual.
 */
ResourceId WaveElement::waveSynchronousLinearSequencerSucceededStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveSynchronousLinearSequencerSucceededStep : Entering ...");

    WaveMessage             *pWaveMessage             = pWaveSynchronousLinearSequencerContext->getPWaveMessage ();
    WaveAsynchronousContext *pWaveAsynchronousContext = pWaveSynchronousLinearSequencerContext->getPWaveAsynchronousContext ();
    ResourceId                completionStatus          = pWaveSynchronousLinearSequencerContext->getCompletionStatus ();

    if (true == (pWaveSynchronousLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pWaveSynchronousLinearSequencerContext->setIsTransactionStartedByMe (false);

        // commit the transaction to preserve the semantics of the WAVE_SEQUENCER_SKIP_TO_SUCCESS_STEP return code and if
        // the transaction has no data to be committed, framework will immediately return without having to go to DB.
        WaveObjectManagerCommitTransactionContext commitTransactionContext (pWaveSynchronousLinearSequencerContext);

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
    else if (NULL != pWaveAsynchronousContext)
    {
        pWaveAsynchronousContext->setCompletionStatus (completionStatus);
        pWaveAsynchronousContext->callback ();
    }

    delete pWaveSynchronousLinearSequencerContext;
    return (completionStatus);
}

ResourceId WaveElement::waveSynchronousLinearSequencerFailedStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveSynchronousLinearSequencerFailedStep : Entering ...");

    WaveMessage             *pWaveMessage             = pWaveSynchronousLinearSequencerContext->getPWaveMessage ();
    WaveAsynchronousContext *pWaveAsynchronousContext = pWaveSynchronousLinearSequencerContext->getPWaveAsynchronousContext ();
    ResourceId                completionStatus          = pWaveSynchronousLinearSequencerContext->getCompletionStatus ();

    if (true == (pWaveSynchronousLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pWaveSynchronousLinearSequencerContext->setIsTransactionStartedByMe (false);
        rollbackTransaction ();
    }

    if (NULL != pWaveMessage)
    {
        pWaveMessage->setCompletionStatus (completionStatus);
        reply (pWaveMessage);
    }
    else if (NULL != pWaveAsynchronousContext)
    {
        pWaveAsynchronousContext->setCompletionStatus (completionStatus);
        pWaveAsynchronousContext->callback ();
    }

    delete pWaveSynchronousLinearSequencerContext;
    return (completionStatus);
}

ResourceId WaveElement::waveSynchronousLinearSequencerStartTransactionStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveLinearSequencerStartTransactionStep : Entering ...");

    if (false == (isTransactionInProgress ()))
    {
        pWaveSynchronousLinearSequencerContext->setIsTransactionStartedByMe (true);

        startTransaction ();
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveElement::waveSynchronousLinearSequencerCommitTransactionStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveElement::waveLinearSequencerCommitTransactionStep : Entering ...");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == (pWaveSynchronousLinearSequencerContext->getIsTransactionStartedByMe ()))
    {
        pWaveSynchronousLinearSequencerContext->setIsTransactionStartedByMe (false);

        WaveObjectManagerCommitTransactionContext commitTransactionContext (pWaveSynchronousLinearSequencerContext);

        status = commitTransaction (&commitTransactionContext);

        if (FRAMEWORK_SUCCESS == status)
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    return (status);
}

WaveObjectManager *WaveElement::getPWaveObjectManager () const
{
    return (m_pWaveObjectManager);
}

WaveManagedObject *WaveElement::createManagedObjectInstance (const string &managedClassName)
{
    trace (TRACE_LEVEL_ERROR, "WaveElement::createManagedObjectInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    trace (TRACE_LEVEL_ERROR, "WaveElement::createManagedObjectInstance : ObjectManagers and Workers MUST overwrite this virtual function.");
    return (NULL);
}

WaveMessage *WaveElement::createMessageInstance (const UI32 &operationCode)
{
    trace (TRACE_LEVEL_ERROR, "WaveElement::createMessageInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    trace (TRACE_LEVEL_ERROR, "WaveElement::createMessageInstance : ObjectManagers and Workers MUST overwrite this virtual function.");
    return (NULL);
}

LightPulse *WaveElement::createLightPulseInstance (const string &lightPulseName)
{
    trace (TRACE_LEVEL_ERROR, "WaveElement::createLightPulseInstance : NOT IMPLEMENTED.  RETURNS NULL BY DEFAULT.");
    trace (TRACE_LEVEL_ERROR, "WaveElement::createLightPulseInstance : ObjectManagers and Workers MUST overwrite this virtual function.");
    return (NULL);
}

void WaveElement::setPWaveObjectManager (WaveObjectManager *pWaveObjectManager)
{
    m_pWaveObjectManager = pWaveObjectManager;
}

}
