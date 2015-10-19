/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Persistence/Test/PersistenceTestObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Regression/RegressionTestObjectManager.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Core/Test/FrameworkTestabilityMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Regression/RegressionTestMessage.h"

namespace WaveNs
{

PersistenceTestObjectManager::PersistenceTestObjectManager ()
    : WaveTestObjectManager ("Persistence Test")
{
}

PersistenceTestObjectManager::~PersistenceTestObjectManager ()
{
}

PersistenceTestObjectManager * PersistenceTestObjectManager::getInstance ()
{
    static PersistenceTestObjectManager *pPersistenceTestObjectManager = new PersistenceTestObjectManager ();

    WaveNs::waveAssert (NULL != pPersistenceTestObjectManager, __FILE__, __LINE__);

    return (pPersistenceTestObjectManager);
}

WaveServiceId PersistenceTestObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void PersistenceTestObjectManager::testRequestHandler (RegressionTestMessage *pRegressionTestMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&PersistenceTestObjectManager::simpleTransactionForObjectCreationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&PersistenceTestObjectManager::nestedTransactionForObjectCreationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&PersistenceTestObjectManager::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&PersistenceTestObjectManager::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pRegressionTestMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void PersistenceTestObjectManager::simpleTransactionForObjectCreationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "PersistenceTestObjectManager::simpleTransactionForObjectCreationStep : Entering ...");

    FrameworkTestabilityMessage8 message, pageQueryMessage;
    UI32                         numberOfObjectsToBeCreated = 1000;

    //To do:- Make the page size configurable
    UI32                         resultSizeOfPagedQuery = 23;

    if (0 != (m_regressionInput.size ()))
    {
        numberOfObjectsToBeCreated = atoi (m_regressionInput[0].c_str ());
    }

    message.setNumberOfObjectsToBeCreated (numberOfObjectsToBeCreated);

    ResourceId status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "PersistenceTestObjectManager::simpleTransactionForObjectCreationStep : Failed to send message to test Persistence.  Status : " + FrameworkToolKit::localize (status));

        pWaveLinearSequencerContext->executeNextStep (status);
        return;
    }
    else
    {
        status = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "PersistenceTestObjectManager::simpleTransactionForObjectCreationStep : Persistence Test failed.  Completion Status : " + FrameworkToolKit::localize (status));

            pWaveLinearSequencerContext->executeNextStep (status);
            return;
        }
    }


//Paged query testing
    if (0 != (m_regressionInput.size ()))
    {
        numberOfObjectsToBeCreated = atoi (m_regressionInput[0].c_str ());
    }

    pageQueryMessage.setNumberOfObjectsToBeCreated (numberOfObjectsToBeCreated);
    pageQueryMessage.setPageSize(resultSizeOfPagedQuery);		
	

    status = sendSynchronously (&pageQueryMessage);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "PersistenceTestObjectManager::simpleTransactionForObjectCreationStep : Failed to send paged message to test Persistence.  Status : " + FrameworkToolKit::localize (status));
    }
    else
    {
        status = pageQueryMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "PersistenceTestObjectManager::simpleTransactionForObjectCreationStep : Persistence paged Test failed.  Completion Status : " + FrameworkToolKit::localize (status));
        }
    }


    pWaveLinearSequencerContext->executeNextStep (status);
}

void PersistenceTestObjectManager::nestedTransactionForObjectCreationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "Starting Simple Nested Transaction Test. More nesting ");

    UI32               numberOfMessagesToSend = 1000;
    UI32               i                      = 0;
    WaveMessageStatus status                 = WAVE_MESSAGE_ERROR;

    if (0 != (m_regressionInput.size ()))
    {
        numberOfMessagesToSend = atoi (m_regressionInput[0].c_str ());
    }

    trace (TRACE_LEVEL_INFO, string ("    Sending ") + numberOfMessagesToSend + " messages.");

    for (i = 0; i < numberOfMessagesToSend; i++)
    {
        //trace (TRACE_LEVEL_INFO, "PersistenceTestObjectManager::nestedTransactionForObjectCreationStep : New ");

        FrameworkTestabilityMessage9 *pMessage = new FrameworkTestabilityMessage9 ();

        status = sendSynchronously (pMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_DEBUG, string ("PersistenceTestObjectManager::nestedTransactionForObjectCreationStep : Sending a message to [") + WaveThread::getWaveServiceNameForServiceId (pMessage->getSenderServiceCode ()) + " service] failed.");
            delete pMessage;
        }
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

}
