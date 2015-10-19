/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SoftwareManagement/SoftwareManagementObjectManager.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Version/WaveVersion.h"
#include "Framework/Utils/AssertUtils.h"
#include "SoftwareManagement/SoftwareManagementVersionWorker.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

SoftwareManagementObjectManager::SoftwareManagementObjectManager ()
    : WaveObjectManager (SoftwareManagementObjectManager::getClassName ())
{
    m_pSoftwareManagementVersionWorker = new SoftwareManagementVersionWorker (this);

    waveAssert (NULL != m_pSoftwareManagementVersionWorker, __FILE__, __LINE__);
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
        WaveNs::waveAssert (NULL != pSoftwareManagementObjectManager, __FILE__, __LINE__);
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
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&SoftwareManagementObjectManager::displayVersionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SoftwareManagementObjectManager::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SoftwareManagementObjectManager::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWaveAsynchronousContextForBootPhases, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void SoftwareManagementObjectManager::displayVersionStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SoftwareManagementObjectManager::displayVersionStep : Entering ...");

    const WaveVersion *pWaveVersion = WaveVersion::getInstance ();

    trace (TRACE_LEVEL_INFO, "Wave Version : " + pWaveVersion->getMajor () + "." + pWaveVersion->getMinor () + "." + pWaveVersion->getPatch () + "." + pWaveVersion->getRevision () + "-" + pWaveVersion->getBuildType () + "." + pWaveVersion->getBuildNumber ());
    trace (TRACE_LEVEL_INFO, "Wave Build   : " + pWaveVersion->getUser () + "@" + pWaveVersion->getHost () + "." + pWaveVersion->getDomain ());
    trace (TRACE_LEVEL_INFO, "Wave Date    : " + pWaveVersion->getDate ());

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
