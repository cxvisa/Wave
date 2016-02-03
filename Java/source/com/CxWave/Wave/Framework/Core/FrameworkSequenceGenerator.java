/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import java.util.Vector;

import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class FrameworkSequenceGenerator
{
    private final Vector<WaveServiceId> m_waveServiceIdsToInitializeDuringPrePhase    = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToEnableDuringPrePhase        = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToInstallDuringPrePhase       = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToBootDuringPrePhase          = new Vector<WaveServiceId> ();

    private final Vector<WaveServiceId> m_waveServiceIdsToInitialize                  = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToEnable                      = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToInstall                     = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToBoot                        = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToShutdown                    = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToUninstall                   = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToUninitialize                = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToDisable                     = new Vector<WaveServiceId> ();

    private final Vector<WaveServiceId> m_waveServiceIdsToShutdownDuringPostPhase     = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToUninstallDuringPostPhase    = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToUninitializeDuringPostPhase = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToDisableDuringPostPhase      = new Vector<WaveServiceId> ();

    private final Vector<WaveServiceId> m_waveServiceIdsToFailover                    = new Vector<WaveServiceId> ();
    private final Vector<WaveServiceId> m_waveServiceIdsToZeroize                     = new Vector<WaveServiceId> ();

    public FrameworkSequenceGenerator ()
    {

    }

    public void getInitializeSequenceDuringPrePhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToInitializeDuringPrePhase);
    }

    public void getEnableSequenceDuringPrePhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToEnableDuringPrePhase);
    }

    public void getInstallSequenceDuringPrePhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToInstallDuringPrePhase);
    }

    public void getBootSequenceDuringPrePhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToBootDuringPrePhase);
    }

    public void getShutdownSequenceDuringPostPhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToShutdownDuringPostPhase);
    }

    public void getUninstallSequenceDuringPostPhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToUninstallDuringPostPhase);
    }

    public void getUninitializeSequenceDuringPostPhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToUninitializeDuringPostPhase);
    }

    public void getDisableSequenceDuringPostPhase (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToDisableDuringPostPhase);
    }

    public void getInitializeSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToInitialize);
    }

    public void getEnableSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToEnable);
    }

    public void getInstallSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToInstall);
    }

    public void getBootSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToBoot);
    }

    public void getShutdownSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToShutdown);
    }

    public void getUninstallSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToUninstall);
    }

    public void getUninitializeSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToUninitialize);
    }

    public void getDisableSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToDisable);
    }

    public void getFailoverSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToFailover);
    }

    public void getZeroizeSequence (final Vector<WaveServiceId> serviceIds)
    {
        serviceIds.addAll (m_waveServiceIdsToZeroize);
    }

    public void addWaveServiceIdToAll (final WaveServiceId waveServiceId)
    {
        addWaveServiceIdToAll (waveServiceId, true);
    }

    public void addWaveServiceIdToAll (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        if (true == isForNormalPhase)
        {
            m_waveServiceIdsToInitialize.add (waveServiceId);
            m_waveServiceIdsToEnable.add (waveServiceId);
            m_waveServiceIdsToInstall.add (waveServiceId);
            m_waveServiceIdsToBoot.add (waveServiceId);
            m_waveServiceIdsToShutdown.add (0, waveServiceId);
            m_waveServiceIdsToUninstall.add (0, waveServiceId);
            m_waveServiceIdsToUninitialize.add (0, waveServiceId);
            m_waveServiceIdsToDisable.add (0, waveServiceId);
        }
        else
        {
            m_waveServiceIdsToInitializeDuringPrePhase.add (waveServiceId);
            m_waveServiceIdsToEnableDuringPrePhase.add (waveServiceId);
            m_waveServiceIdsToInstallDuringPrePhase.add (waveServiceId);
            m_waveServiceIdsToBootDuringPrePhase.add (waveServiceId);
            m_waveServiceIdsToShutdownDuringPostPhase.add (0, waveServiceId);
            m_waveServiceIdsToUninstallDuringPostPhase.add (0, waveServiceId);
            m_waveServiceIdsToUninitializeDuringPostPhase.add (0, waveServiceId);
            m_waveServiceIdsToDisableDuringPostPhase.add (0, waveServiceId);
        }

        m_waveServiceIdsToFailover.add (waveServiceId);
        m_waveServiceIdsToZeroize.add (waveServiceId);
    }

    public void addWaveServiceIdToInitialize (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToInitialize.add (waveServiceId);
    }

    public void addWaveServiceIdToEnable (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToEnable.add (waveServiceId);
    }

    public void addWaveServiceIdToInstall (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToInstall.add (waveServiceId);
    }

    public void addWaveServiceIdToBoot (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToBoot.add (waveServiceId);
    }

    public void addWaveServiceIdToShutdown (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToShutdown.add (waveServiceId);
    }

    public void addWaveServiceIdToUninstall (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToUninstall.add (waveServiceId);
    }

    public void addWaveServiceIdToUninitialize (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToUninitialize.add (waveServiceId);
    }

    public void addWaveServiceIdToDisable (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToDisable.add (waveServiceId);
    }

    public void addWaveServiceIdToFailover (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToFailover.add (waveServiceId);
    }

    public void addWaveServiceIdToZeroize (final WaveServiceId waveServiceId, final boolean isForNormalPhase)
    {
        m_waveServiceIdsToZeroize.add (waveServiceId);
    }
}
