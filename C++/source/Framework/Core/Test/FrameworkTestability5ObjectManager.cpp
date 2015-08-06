/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/Core/Test/FrameworkTestability5ObjectManager.h"
#include "Framework/Core/Test/FrameworkTestabilityMessages.h"
#include "Framework/Core/Test/WaveTestManagedObject9.h"
#include "Framework/Messaging/Local/Test/FrameworkTestabilityEvents.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestTypes.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

FrameworkTestability5ObjectManager::FrameworkTestability5ObjectManager ()
    : WaveLocalObjectManager ("Framework Testability5")
{
    WaveTestManagedObject9  waveTestManagedObject9  (this);
    waveTestManagedObject9.setupOrm ();
    addManagedClass (WaveTestManagedObject9::getClassName ());
    
    addOperationMap (FRAMEWORK_TESTABILITY_MESSAGE10, reinterpret_cast<WaveMessageHandler> (&FrameworkTestability5ObjectManager::frameworkTestability10MessageHandler));
}

FrameworkTestability5ObjectManager *FrameworkTestability5ObjectManager::getInstance ()
{
    static FrameworkTestability5ObjectManager *pFrameworkTestability5ObjectManager = NULL;

    if (NULL == pFrameworkTestability5ObjectManager)
    {
        pFrameworkTestability5ObjectManager = new FrameworkTestability5ObjectManager ();
        WaveNs::waveAssert (NULL != pFrameworkTestability5ObjectManager, __FILE__, __LINE__);
    }

    return (pFrameworkTestability5ObjectManager);
}

FrameworkTestability5ObjectManager::~FrameworkTestability5ObjectManager ()
{
}

WaveServiceId FrameworkTestability5ObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

WaveMessage *FrameworkTestability5ObjectManager::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case FRAMEWORK_TESTABILITY_MESSAGE10 :
            pWaveMessage = new FrameworkTestabilityMessage10;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

WaveManagedObject *FrameworkTestability5ObjectManager::createManagedObjectInstance (const string &managedClassName)
{
    WaveManagedObject *pWaveManagedObject = NULL;

    if ((WaveTestManagedObject9::getClassName ()) == managedClassName)
    {
        pWaveManagedObject = new WaveTestManagedObject9 (this);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "FrameworkTestability5ObjectManager::createManagedObjectInstance : Unknown Managed Class Name : " + managedClassName);
    }

    return (pWaveManagedObject);
    

}
void FrameworkTestability5ObjectManager::frameworkTestability10MessageHandler (FrameworkTestabilityMessage10 *pMessage)
{
    ResourceId  status  =   WAVE_MESSAGE_SUCCESS;
    UI32        i       =   0;
    UI32        numberOfObjectsToCreate = 10;                                      

    for (i = 0; i < numberOfObjectsToCreate; i++)
    {
        startTransaction ();

        WaveTestManagedObject9 *pWaveTestManagedObject9 = new WaveTestManagedObject9 (this);

        pWaveTestManagedObject9->setInteger9 (i);
        pWaveTestManagedObject9->setMessage9 ("Wave's Test Cases For Nested Transaction");

        status = commitTransaction ();
        
        if (status != FRAMEWORK_SUCCESS)
        {
            trace (TRACE_LEVEL_ERROR, "FrameworkTestability4ObjectManager::frameworkTestability9MessageHandler : Transaction failed.  Status : " + FrameworkToolKit::localize (status));
            break;
        }
        else
        {
            status = WAVE_MESSAGE_SUCCESS;
        }
    }

    pMessage->setCompletionStatus (status);
    reply (pMessage);
}

}
