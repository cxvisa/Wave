/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PolicyObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Policy/ApplicationWorker.h"
#include "Policy/CategoryWorker.h"
#include "Shell/ShellDebug.h"
#include "Policy/NBAR2/Nbar2.h"
#include "Policy/PolicyObjectManagerInitializationWorker.h"

 namespace WaveNs
 {

PolicyObjectManager::PolicyObjectManager ()
    : WaveObjectManager (PolicyObjectManager::getServiceName ())
{
     m_pCategoryWorker = new CategoryWorker (this);

     prismAssert (NULL != m_pCategoryWorker, __FILE__, __LINE__);

     m_pPolicyObjectManagerInitializationWorker = new PolicyObjectManagerInitializationWorker (this);

     prismAssert (NULL != m_pPolicyObjectManagerInitializationWorker, __FILE__, __LINE__);

     m_pApplicationWorker = new ApplicationWorker (this);

     prismAssert (NULL != m_pApplicationWorker, __FILE__, __LINE__);

     addDebugFunction ((ShellCmdFunction) (&PolicyObjectManager::loadNbar2File), "loadnbar2file");
}

PolicyObjectManager::~PolicyObjectManager ()
{
    if (NULL != m_pCategoryWorker)
    {
        delete m_pCategoryWorker;
    }

    if (NULL != m_pPolicyObjectManagerInitializationWorker)
    {
        delete m_pPolicyObjectManagerInitializationWorker;
    }
}

string PolicyObjectManager::getServiceName ()
{
    return ("Policy Manager");
}

PolicyObjectManager *PolicyObjectManager::getInstance ()
{
    static PolicyObjectManager *pPolicyObjectManager = new PolicyObjectManager ();

    WaveNs::prismAssert (NULL != pPolicyObjectManager, __FILE__, __LINE__);

    return (pPolicyObjectManager);
}

PrismServiceId PolicyObjectManager::getPrismServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

ResourceId PolicyObjectManager::loadNbar2File (UI32 argc, vector<string> argv)
{
    Nbar2 nbar2;

    WaveNs::trace (TRACE_LEVEL_INFO, "Loadoing NBAR2 from file : " + argv[1]);

    nbar2.load (argv[1]);

    return (WAVE_MESSAGE_SUCCESS);
}

}

