/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/FrameworkCoreTestObjectManager.h"
#include "Framework/Trace/TraceTypes.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

FrameworkCoreTestObjectManager::FrameworkCoreTestObjectManager ()
    : PrismTestObjectManager ("Framework Core Test")
{
}

FrameworkCoreTestObjectManager *FrameworkCoreTestObjectManager::getInstance ()
{
    static FrameworkCoreTestObjectManager *pFrameworkCoreTestObjectManager = NULL;

    if (NULL == pFrameworkCoreTestObjectManager)
    {
        pFrameworkCoreTestObjectManager = new FrameworkCoreTestObjectManager ();
        WaveNs::prismAssert (NULL != pFrameworkCoreTestObjectManager, __FILE__, __LINE__);
    }

    return (pFrameworkCoreTestObjectManager);
}

FrameworkCoreTestObjectManager::~FrameworkCoreTestObjectManager ()
{
}

WaveServiceId FrameworkCoreTestObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void FrameworkCoreTestObjectManager::testRequestHandler (RegressionTestMessage *pMessage)
{
    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&FrameworkCoreTestObjectManager::frameworkCoreTestFormattedErrorStringValidationStep),
        reinterpret_cast<PrismLinearSequencerStep> (&FrameworkCoreTestObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&FrameworkCoreTestObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

void FrameworkCoreTestObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    unsigned vectorSize;
    for(vectorSize = 0; vectorSize < vectorSI64.size(); vectorSize++)
    {
        vectorSI64.at(vectorSize) = WAVE_LLONG_MAX - vectorSize;
    }
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void FrameworkCoreTestObjectManager::frameworkCoreTestFormattedErrorStringValidationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    UI32                    i                               = 0;
    UI32                    NumberOfMessages                = 100;
    IpV4Address             ipV4;
    vector <Attribute *>    errorArguments;
    char                    ipString[16];
    char                    testString[1024];
    string                  errorString;
    char                    checkString[1024] = {0};
    ResourceId              status                          = WAVE_MESSAGE_SUCCESS;

    for (i = 0; i < NumberOfMessages; i++)
    {
        errorArguments.clear ();
        snprintf (testString, 1024, "this is the %%%d th string", i);
        snprintf (ipString, 16, "%d.%d.%d.%d", i,i,i,i); 
        ipV4.fromString (ipString);

        errorArguments.push_back (new AttributeUI32 (i, "integer"));
        errorArguments.push_back (new AttributeString(string (testString),"string"));
        errorArguments.push_back (new AttributeIpV4Address (ipV4, "ipaddress"));
        
        errorString = FrameworkToolKit::localize (FRAMEWORK_ERROR_FORMATTED_ERROR_TEST, errorArguments);

        snprintf (checkString, 1024, "This is to test integer %d output, string %s and ip %s ", i, testString, ipString);

        if (0 != errorString.compare (checkString))
        {
            status = WAVE_MESSAGE_ERROR;
        }
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

}
