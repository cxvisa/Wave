/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

FrameworkSequenceGenerator::FrameworkSequenceGenerator ()
{
}

FrameworkSequenceGenerator::~FrameworkSequenceGenerator ()
{
}

void FrameworkSequenceGenerator::getInitializeSequenceDuringPrePhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToInitializeDuringPrePhase;
}

void FrameworkSequenceGenerator::getEnableSequenceDuringPrePhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToEnableDuringPrePhase;
}

void FrameworkSequenceGenerator::getInstallSequenceDuringPrePhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToInstallDuringPrePhase;
}

void FrameworkSequenceGenerator::getBootSequenceDuringPrePhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToBootDuringPrePhase;
}

void FrameworkSequenceGenerator::getShutdownSequenceDuringPostPhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToShutdownDuringPostPhase;
}

void FrameworkSequenceGenerator::getUninstallSequenceDuringPostPhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToUninstallDuringPostPhase;
}

void FrameworkSequenceGenerator::getUninitializeSequenceDuringPostPhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToUninitializeDuringPostPhase;
}

void FrameworkSequenceGenerator::getDisableSequenceDuringPostPhase (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToDisableDuringPostPhase;
}

void FrameworkSequenceGenerator::getInitializeSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToInitialize;
}

void FrameworkSequenceGenerator::getEnableSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToEnable;
}

void FrameworkSequenceGenerator::getInstallSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToInstall;
}

void FrameworkSequenceGenerator::getBootSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToBoot;
}

void FrameworkSequenceGenerator::getShutdownSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToShutdown;
}

void FrameworkSequenceGenerator::getUninstallSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToUninstall;
}

void FrameworkSequenceGenerator::getUninitializeSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToUninitialize;
}

void FrameworkSequenceGenerator::getDisableSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToDisable;
}

void FrameworkSequenceGenerator::getFailoverSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToFailover;
}

void FrameworkSequenceGenerator::getZeroizeSequence (vector<WaveServiceId> &serviceIds) const
{
    serviceIds = m_waveServiceIdsToZeroize;
}

void FrameworkSequenceGenerator::addWaveServiceIdToAll (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    if (true == isForNormalPhase)
    {
        m_waveServiceIdsToInitialize.push_back (prismServiceId);
        m_waveServiceIdsToEnable.push_back (prismServiceId);
        m_waveServiceIdsToInstall.push_back (prismServiceId);
        m_waveServiceIdsToBoot.push_back (prismServiceId);
        m_waveServiceIdsToShutdown.insert (m_waveServiceIdsToShutdown.begin (), prismServiceId);
        m_waveServiceIdsToUninstall.insert (m_waveServiceIdsToUninstall.begin (), prismServiceId);
        m_waveServiceIdsToUninitialize.insert (m_waveServiceIdsToUninitialize.begin (), prismServiceId);
        m_waveServiceIdsToDisable.insert (m_waveServiceIdsToDisable.begin (), prismServiceId);
    }
    else
    {
        m_waveServiceIdsToInitializeDuringPrePhase.push_back (prismServiceId);
        m_waveServiceIdsToEnableDuringPrePhase.push_back (prismServiceId);
        m_waveServiceIdsToInstallDuringPrePhase.push_back (prismServiceId);
        m_waveServiceIdsToBootDuringPrePhase.push_back (prismServiceId);
        m_waveServiceIdsToShutdownDuringPostPhase.insert (m_waveServiceIdsToShutdownDuringPostPhase.begin (), prismServiceId);
        m_waveServiceIdsToUninstallDuringPostPhase.insert (m_waveServiceIdsToUninstallDuringPostPhase.begin (), prismServiceId);
        m_waveServiceIdsToUninitializeDuringPostPhase.insert (m_waveServiceIdsToUninitializeDuringPostPhase.begin (), prismServiceId);
        m_waveServiceIdsToDisableDuringPostPhase.insert (m_waveServiceIdsToDisableDuringPostPhase.begin (), prismServiceId);
    }

    m_waveServiceIdsToFailover.push_back   (prismServiceId);
    m_waveServiceIdsToZeroize.push_back    (prismServiceId);
    
}

void FrameworkSequenceGenerator::addWaveServiceIdToInitialize (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToInitialize.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToEnable (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToEnable.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToInstall (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToInstall.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToBoot (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToBoot.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToShutdown (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToShutdown.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToUninstall (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToUninstall.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToUninitialize (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToUninitialize.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToDisable (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToDisable.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToFailover (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToFailover.push_back (prismServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToZeroize (const WaveServiceId &prismServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToZeroize.push_back(prismServiceId);
}

}
