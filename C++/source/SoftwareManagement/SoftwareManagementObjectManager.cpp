/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SoftwareManagement/SoftwareManagementObjectManager.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Version/PrismVersion.h"
#include "Framework/Utils/AssertUtils.h"
#include "SoftwareManagement/SoftwareManagementVersionWorker.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

SoftwareManagementObjectManager::SoftwareManagementObjectManager ()
    : WaveObjectManager (SoftwareManagementObjectManager::getClassName ())
{
    m_pSoftwareManagementVersionWorker = new SoftwareManagementVersionWorker (this);

    prismAssert (NULL != m_pSoftwareManagementVersionWorker, __FILE__, __LINE__);
}

SoftwareManagementObjectManager::~SoftwareManagementObjectManager ()
{
    if (NULL != m_pSoftwareManagementVersionWorker)
    {
        delete m_pSoftwareManagementVersionWorker;
    }
}

SoftwareManagementObjectManager *SoftwareManagementObjectManager::getInstance ()
{
    static SoftwareManagementObjectManager *pSoftwareManagementObjectManager = NULL;

    if (NULL == pSoftwareManagementObjectManager)
    {
        pSoftwareManagementObjectManager = new SoftwareManagementObjectManager ();
        WaveNs::prismAssert (NULL != pSoftwareManagementObjectManager, __FILE__, __LINE__);
    }

    return (pSoftwareManagementObjectManager);
}

WaveServiceId SoftwareManagementObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string SoftwareManagementObjectManager::getClassName ()
{
    return ("Software Management");
}

void SoftwareManagementObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&SoftwareManagementObjectManager::displayVersionStep),
        reinterpret_cast<PrismLinearSequencerStep> (&SoftwareManagementObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&SoftwareManagementObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWaveAsynchronousContextForBootPhases, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void SoftwareManagementObjectManager::displayVersionStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SoftwareManagementObjectManager::displayVersionStep : Entering ...");

    const PrismVersion *pPrismVersion = PrismVersion::getInstance ();

    trace (TRACE_LEVEL_INFO, "Prism Version : " + pPrismVersion->getMajor () + "." + pPrismVersion->getMinor () + "." + pPrismVersion->getPatch () + "." + pPrismVersion->getRevision () + "-" + pPrismVersion->getBuildType () + "." + pPrismVersion->getBuildNumber ());
    trace (TRACE_LEVEL_INFO, "Prism Build   : " + pPrismVersion->getUser () + "@" + pPrismVersion->getHost () + "." + pPrismVersion->getDomain ());
    trace (TRACE_LEVEL_INFO, "Prism Date    : " + pPrismVersion->getDate ());

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
