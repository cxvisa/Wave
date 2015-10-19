/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

using namespace std;

namespace WaveNs
{

WaveLinearSequencerContext::WaveLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
{
    m_pWaveMessage                              = pWaveMessage;
    m_pWaveAsynchronousContext                  = NULL;
    m_pWaveElement                              = pWaveElement;
    m_pSteps                                     = NULL;
    m_numberOfSteps                              = numberOfSteps;
    m_currentStep                                = 0;
    m_numberOfCallbacksBeforeAdvancingToNextStep = 0;
    m_isHoldAllRequested                         = false;
    m_isTransactionStartedByMe                   = false;
    m_numberOfFailures                           = 0;
    m_pQueryResults                              = NULL;
    m_isADelayedCommitTransaction                = false;
    m_completionStatus                           = WAVE_MESSAGE_ERROR;

    m_returnValue                                = -1;
    m_returnValueR                               = -1;
    m_clockId                                    = 0;

    if (3 > m_numberOfSteps)
    {
        cerr << "WaveLinearSequencerContext::WaveLinearSequencerContext : There should be atleast three steps to run a Wave Linear Sequencer. " << numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pSteps = new WaveLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveLinearSequencerContext::WaveLinearSequencerContext : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = pSteps[i];
    }

    return;
}

WaveLinearSequencerContext::WaveLinearSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
{
    m_pWaveMessage                              = NULL;
    m_pWaveAsynchronousContext                  = pWaveAsynchronousContext;
    m_pWaveElement                              = pWaveElement;
    m_pSteps                                     = NULL;
    m_numberOfSteps                              = numberOfSteps;
    m_currentStep                                = 0;
    m_numberOfCallbacksBeforeAdvancingToNextStep = 0;
    m_isHoldAllRequested                         = false;
    m_isTransactionStartedByMe                   = false;
    m_numberOfFailures                           = 0;
    m_pQueryResults                              = NULL;
    m_isADelayedCommitTransaction                = false;
    m_completionStatus                           = WAVE_MESSAGE_ERROR;

    m_returnValue                                = -1;
    m_returnValueR                               = -1;
    m_clockId                                    = 0;

    if (3 > m_numberOfSteps)
    {
        cerr << "WaveLinearSequencerContext::WaveLinearSequencerContext : There should be atleast three steps to run a Wave Linear Sequencer. " << numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pSteps = new WaveLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveLinearSequencerContext::WaveLinearSequencerContext : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = pSteps[i];
    }

    return;
}

WaveLinearSequencerContext::WaveLinearSequencerContext (const WaveLinearSequencerContext &waveLinearSequencerContext)
{
    m_pWaveMessage                              = waveLinearSequencerContext.m_pWaveMessage;
    m_pWaveAsynchronousContext                  = waveLinearSequencerContext.m_pWaveAsynchronousContext;
    m_pWaveElement                              = waveLinearSequencerContext.m_pWaveElement;
    m_pSteps                                     = waveLinearSequencerContext.m_pSteps;
    m_numberOfSteps                              = waveLinearSequencerContext.m_numberOfSteps;
    m_currentStep                                = waveLinearSequencerContext.m_currentStep;
    m_numberOfCallbacksBeforeAdvancingToNextStep = waveLinearSequencerContext.m_numberOfCallbacksBeforeAdvancingToNextStep;
    m_isHoldAllRequested                         = waveLinearSequencerContext.m_isHoldAllRequested;
    m_isTransactionStartedByMe                   = waveLinearSequencerContext.m_isTransactionStartedByMe;
    m_numberOfFailures                           = waveLinearSequencerContext.m_numberOfFailures;
    m_pQueryResults                              = waveLinearSequencerContext.m_pQueryResults;
    m_isADelayedCommitTransaction                = waveLinearSequencerContext.m_isADelayedCommitTransaction;
    m_completionStatus                           = waveLinearSequencerContext.m_completionStatus;

    m_returnValue                                = -1;
    m_returnValueR                               = -1;
    m_clockId                                    = 0;


    if (3 > m_numberOfSteps)
    {
        cerr << "WaveLinearSequencerContext::WaveLinearSequencerContext : There should be atleast three steps to run a Wave Linear Sequencer. " << m_numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    m_pSteps = new WaveLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveLinearSequencerContext::WaveLinearSequencerContext : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = waveLinearSequencerContext.m_pSteps[i];
    }

    return;
}

WaveLinearSequencerContext::~WaveLinearSequencerContext ()
{
    if (NULL != m_pSteps)
    {
        delete[] m_pSteps;
    }

    if (NULL != m_pQueryResults)
    {
        UI32 numberOfQueryResults = m_pQueryResults->size ();
        UI32 i                    = 0;

        for (i = 0; i < numberOfQueryResults; i++)
        {
            delete ((*m_pQueryResults)[i]);
        }

        m_pQueryResults->clear ();
        delete m_pQueryResults;
    }

    garbageCollect ();
}

WaveLinearSequencerContext &WaveLinearSequencerContext::operator = (const WaveLinearSequencerContext &waveLinearSequencerContext)
{
    m_pWaveMessage                              = waveLinearSequencerContext.m_pWaveMessage;
    m_pWaveAsynchronousContext                  = waveLinearSequencerContext.m_pWaveAsynchronousContext;
    m_pWaveElement                              = waveLinearSequencerContext.m_pWaveElement;
    m_pSteps                                     = waveLinearSequencerContext.m_pSteps;
    m_numberOfSteps                              = waveLinearSequencerContext.m_numberOfSteps;
    m_currentStep                                = waveLinearSequencerContext.m_currentStep;
    m_numberOfCallbacksBeforeAdvancingToNextStep = waveLinearSequencerContext.m_numberOfCallbacksBeforeAdvancingToNextStep;
    m_isHoldAllRequested                         = waveLinearSequencerContext.m_isHoldAllRequested;
    m_isTransactionStartedByMe                   = waveLinearSequencerContext.m_isTransactionStartedByMe;
    m_numberOfFailures                           = waveLinearSequencerContext.m_numberOfFailures;
    m_isADelayedCommitTransaction                = waveLinearSequencerContext.m_isADelayedCommitTransaction;
    m_pQueryResults                              = waveLinearSequencerContext.m_pQueryResults;

    m_returnValue                                = -1;
    m_returnValueR                               = -1;
    m_clockId                                    = 0;


    if (3 > m_numberOfSteps)
    {
        cerr << "WaveLinearSequencerContext::operator = : There should be atleast three steps to run a Wave Linear Sequencer. " << m_numberOfSteps << " Steps were specified." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return (*this);
    }

    m_pSteps = new WaveLinearSequencerStep[m_numberOfSteps];

    if (NULL == m_pSteps)
    {
        cerr << "WaveLinearSequencerContext::operator = : Could not allocate memory for steps." << endl;
        waveAssert (false, __FILE__, __LINE__);
        return (*this);
    }

    UI32 i = 0;

    for (i = 0; i < m_numberOfSteps; i++)
    {
        m_pSteps[i] = waveLinearSequencerContext.m_pSteps[i];
    }

    return (*this);
}

void WaveLinearSequencerContext::advanceCurrentStep ()
{
    m_currentStep++;
}

void WaveLinearSequencerContext::executeCurrentStep ()
{
    if (m_currentStep < (m_numberOfSteps - 2))
    {
        if ((0 != m_clockId) && (NULL != m_pWaveMessage) && (NULL != m_pWaveElement))
        {
            m_operationCode = m_pWaveMessage->getOperationCode ();
            m_returnValue   = clock_gettime (m_clockId,      &m_ts1);
            m_returnValueR  = clock_gettime (CLOCK_REALTIME, &m_tsr1);
        }
    }

    (m_pWaveElement->*(m_pSteps[m_currentStep])) (this);
}

ResourceId WaveLinearSequencerContext::getCompletionStatus ()
{
    return (m_completionStatus);
}

void WaveLinearSequencerContext::start ()
{
    SI32 returnValue = pthread_getcpuclockid (pthread_self (), &m_clockId);

    if (0 != returnValue)
    {
        m_clockId = 0;

        cerr << "Could not get Clock ID for this thread." << endl;
    }

    m_returnValue  = -1;
    m_returnValueR = -1;

    executeCurrentStep ();
}

/**
 * Note, make sure that a call to this function is followed by a return.
 * There should be absolutely no call to "executeNextStep" after calling this function.
 */
void WaveLinearSequencerContext::executeSuccessStep ()
{
    if (m_currentStep >= (m_numberOfSteps - 2))
    {
        cerr << "WaveLinearSequencerContext::jumpToSuccessStep : Invalid state for this operation. Step (" << m_currentStep << " / " << m_numberOfSteps << ")" << endl;
        executeNextStep(WAVE_MESSAGE_SUCCESS);
        return;
    }

    // Move step pointer to success step, set status to SUCCSSS, and then just execute the step.
    m_currentStep = m_numberOfSteps - 2;
    m_completionStatus = WAVE_MESSAGE_SUCCESS;

    executeCurrentStep ();
    return;
}

void WaveLinearSequencerContext::executeNextStep (const ResourceId &currentStepStatus)
{
    UI32     numberOfSeconds     = 0;
    SI32     numberOfNanoSeconds = 0;

    if (0 != m_numberOfCallbacksBeforeAdvancingToNextStep)
    {
        return;
    }

    if (m_currentStep < (m_numberOfSteps - 2))
    {
        if (0 == m_returnValue)
        {
            m_returnValue = clock_gettime (m_clockId, &m_ts2);

            if (0 == m_returnValue)
            {
                numberOfSeconds     = m_ts2.tv_sec  - m_ts1.tv_sec;
                numberOfNanoSeconds = m_ts2.tv_nsec - m_ts1.tv_nsec;

                m_pWaveElement->updateTimeConsumedInThisThread (m_operationCode, m_currentStep, numberOfSeconds, numberOfNanoSeconds);
            }
        }

        if (0 == m_returnValueR)
        {
            m_returnValueR = clock_gettime (CLOCK_REALTIME, &m_tsr2);

            if (0 == m_returnValueR)
            {
                numberOfSeconds     = m_tsr2.tv_sec  - m_tsr1.tv_sec;
                numberOfNanoSeconds = m_tsr2.tv_nsec - m_tsr1.tv_nsec;

                m_pWaveElement->updateRealTimeConsumedInThisThread (m_operationCode, m_currentStep, numberOfSeconds, numberOfNanoSeconds);
            }
        }
    }

    m_completionStatus = currentStepStatus;

    advanceCurrentStep ();

    if ((m_numberOfSteps - 2) < m_currentStep)
    {
        cerr << "WaveLinearSequencerContext::executeNextStep : Trying to execute beyond the end of the sequencer. (" << m_currentStep << " / " << m_numberOfSteps << ")" << endl;
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    // FIXME : sagar : Handle intermediate step failures.

    if (WAVE_MESSAGE_SUCCESS == m_completionStatus)
    {
        executeCurrentStep ();
        return;
    }
    else
    {
        m_currentStep = m_numberOfSteps - 1;
        executeCurrentStep ();
        return;
    }
}

WaveMessage *WaveLinearSequencerContext::getPWaveMessage ()
{
    return (m_pWaveMessage);
}

void WaveLinearSequencerContext::setPWaveMessage (WaveMessage *pWaveMessage)
{
    m_pWaveMessage = pWaveMessage;
}

WaveAsynchronousContext *WaveLinearSequencerContext::getPWaveAsynchronousContext ()
{
    return (m_pWaveAsynchronousContext);
}

WaveLinearSequencerContext &WaveLinearSequencerContext::operator ++ ()
{
    ++m_numberOfCallbacksBeforeAdvancingToNextStep;

    return (*this);
}

WaveLinearSequencerContext &WaveLinearSequencerContext::operator -- ()
{
    --m_numberOfCallbacksBeforeAdvancingToNextStep;

    return (*this);
}

UI32 WaveLinearSequencerContext::getNumberOfCallbacksBeforeAdvancingToNextStep ()
{
    return (m_numberOfCallbacksBeforeAdvancingToNextStep);
}

void WaveLinearSequencerContext::holdAll ()
{
    waveAssert (NULL != m_pWaveElement, __FILE__, __LINE__);

    m_pWaveElement->holdAll ();
    m_isHoldAllRequested = true;
}

void WaveLinearSequencerContext::unholdAll ()
{
    waveAssert (NULL != m_pWaveElement, __FILE__, __LINE__);

    m_pWaveElement->unholdAll ();
    m_isHoldAllRequested = false;
}

bool WaveLinearSequencerContext::getIsHoldAllRequested ()
{
    return (m_isHoldAllRequested);
}

bool WaveLinearSequencerContext::getIsTransactionStartedByMe () const
{
    return (m_isTransactionStartedByMe);
}

void WaveLinearSequencerContext::setIsTransactionStartedByMe (const bool &isTransactionStartedByMe)
{
    m_isTransactionStartedByMe = isTransactionStartedByMe;
}

UI32 WaveLinearSequencerContext::getNumberOfFailures () const
{
    return (m_numberOfFailures);
}

void WaveLinearSequencerContext::setNumberOfFailures (const UI32 &numberOfFailures)
{
    m_numberOfFailures = numberOfFailures;
}

void WaveLinearSequencerContext::incrementNumberOfFailures ()
{
    m_numberOfFailures++;
}

void WaveLinearSequencerContext::incrementNumberOfFailures (const UI32 &numberOfFailures)
{
    m_numberOfFailures += numberOfFailures;
}

vector<WaveManagedObject *> *WaveLinearSequencerContext::getPQueryResults () const
{
    return (m_pQueryResults);
}

void WaveLinearSequencerContext::setPQueryResults (vector<WaveManagedObject *> *pQueryResults)
{
    m_pQueryResults = pQueryResults;
}

void WaveLinearSequencerContext::addManagedObjectsForGarbageCollection (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection)
{
    m_managedObjectsForGarbageCollection.insert (m_managedObjectsForGarbageCollection.end (), managedObjectsForGarbageCollection.begin (), managedObjectsForGarbageCollection.end ());
}

void WaveLinearSequencerContext::addManagedObjectForGarbageCollection (WaveManagedObject *pWaveManagedObjectForGarbageCollection)
{
    waveAssert (NULL != pWaveManagedObjectForGarbageCollection, __FILE__, __LINE__);

    m_managedObjectsForGarbageCollection.push_back (pWaveManagedObjectForGarbageCollection);
}

void WaveLinearSequencerContext::garbageCollect ()
{
    UI32 numberOfManagedObjectsForGarbageCollection = m_managedObjectsForGarbageCollection.size ();
    UI32 i                                          = 0;

    for (i = 0; i < numberOfManagedObjectsForGarbageCollection; i++)
    {
        waveAssert (NULL != m_managedObjectsForGarbageCollection[i], __FILE__, __LINE__);

        delete (m_managedObjectsForGarbageCollection[i]);
    }
}

bool WaveLinearSequencerContext::getIsADelayedCommitTransaction () const
{
    return (m_isADelayedCommitTransaction);
}

void WaveLinearSequencerContext::setIsADelayedCommitTransaction (const bool &isADelayedCommitTransaction)
{
    m_isADelayedCommitTransaction = isADelayedCommitTransaction;
}

}
