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

void FrameworkSequenceGenerator::addWaveServiceIdToAll (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    if (true == isForNormalPhase)
    {
        m_waveServiceIdsToInitialize.push_back (waveServiceId);
        m_waveServiceIdsToEnable.push_back (waveServiceId);
        m_waveServiceIdsToInstall.push_back (waveServiceId);
        m_waveServiceIdsToBoot.push_back (waveServiceId);
        m_waveServiceIdsToShutdown.insert (m_waveServiceIdsToShutdown.begin (), waveServiceId);
        m_waveServiceIdsToUninstall.insert (m_waveServiceIdsToUninstall.begin (), waveServiceId);
        m_waveServiceIdsToUninitialize.insert (m_waveServiceIdsToUninitialize.begin (), waveServiceId);
        m_waveServiceIdsToDisable.insert (m_waveServiceIdsToDisable.begin (), waveServiceId);
    }
    else
    {
        m_waveServiceIdsToInitializeDuringPrePhase.push_back (waveServiceId);
        m_waveServiceIdsToEnableDuringPrePhase.push_back (waveServiceId);
        m_waveServiceIdsToInstallDuringPrePhase.push_back (waveServiceId);
        m_waveServiceIdsToBootDuringPrePhase.push_back (waveServiceId);
        m_waveServiceIdsToShutdownDuringPostPhase.insert (m_waveServiceIdsToShutdownDuringPostPhase.begin (), waveServiceId);
        m_waveServiceIdsToUninstallDuringPostPhase.insert (m_waveServiceIdsToUninstallDuringPostPhase.begin (), waveServiceId);
        m_waveServiceIdsToUninitializeDuringPostPhase.insert (m_waveServiceIdsToUninitializeDuringPostPhase.begin (), waveServiceId);
        m_waveServiceIdsToDisableDuringPostPhase.insert (m_waveServiceIdsToDisableDuringPostPhase.begin (), waveServiceId);
    }

    m_waveServiceIdsToFailover.push_back   (waveServiceId);
    m_waveServiceIdsToZeroize.push_back    (waveServiceId);
    
}

void FrameworkSequenceGenerator::addWaveServiceIdToInitialize (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToInitialize.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToEnable (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToEnable.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToInstall (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToInstall.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToBoot (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToBoot.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToShutdown (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToShutdown.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToUninstall (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToUninstall.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToUninitialize (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToUninitialize.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToDisable (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToDisable.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToFailover (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToFailover.push_back (waveServiceId);
}

void FrameworkSequenceGenerator::addWaveServiceIdToZeroize (const WaveServiceId &waveServiceId, const bool &isForNormalPhase)
{
    m_waveServiceIdsToZeroize.push_back(waveServiceId);
}

}
