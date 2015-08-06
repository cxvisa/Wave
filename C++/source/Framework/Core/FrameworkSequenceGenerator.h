/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKSEQUENCEGENERATOR_H
#define FRAMEWORKSEQUENCEGENERATOR_H

#include <vector>
#include "Framework/Types/Types.h"

using namespace std;

namespace WaveNs
{

class FrameworkSequenceGenerator
{
    private :
    protected :
        FrameworkSequenceGenerator ();

    public :
        virtual      ~FrameworkSequenceGenerator          ();

        virtual void  getInitializeSequenceDuringPrePhase (vector<WaveServiceId> &serviceIds) const;
        virtual void  getEnableSequenceDuringPrePhase     (vector<WaveServiceId> &serviceIds) const;
        virtual void  getInstallSequenceDuringPrePhase    (vector<WaveServiceId> &serviceIds) const;
        virtual void  getBootSequenceDuringPrePhase       (vector<WaveServiceId> &serviceIds) const;

        virtual void  getInitializeSequence               (vector<WaveServiceId> &serviceIds) const;
        virtual void  getEnableSequence                   (vector<WaveServiceId> &serviceIds) const;
        virtual void  getInstallSequence                  (vector<WaveServiceId> &serviceIds) const;
        virtual void  getBootSequence                     (vector<WaveServiceId> &serviceIds) const;
        virtual void  getShutdownSequence                 (vector<WaveServiceId> &serviceIds) const;
        virtual void  getUninstallSequence                (vector<WaveServiceId> &serviceIds) const;
        virtual void  getUninitializeSequence             (vector<WaveServiceId> &serviceIds) const;
        virtual void  getDisableSequence                  (vector<WaveServiceId> &serviceIds) const;

        virtual void  getShutdownSequenceDuringPostPhase     (vector<WaveServiceId> &serviceIds) const;
        virtual void  getUninstallSequenceDuringPostPhase    (vector<WaveServiceId> &serviceIds) const;
        virtual void  getUninitializeSequenceDuringPostPhase (vector<WaveServiceId> &serviceIds) const;
        virtual void  getDisableSequenceDuringPostPhase      (vector<WaveServiceId> &serviceIds) const;

        virtual void  getFailoverSequence                 (vector<WaveServiceId> &serviceIds) const;
        virtual void  getZeroizeSequence                 (vector<WaveServiceId> &serviceIds) const;

        virtual void  addWaveServiceIdToAll              (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToInitialize       (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToEnable           (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToInstall          (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToBoot             (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToShutdown         (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToUninstall        (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToUninitialize     (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToDisable          (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToFailover         (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);
        virtual void  addWaveServiceIdToZeroize 		  (const WaveServiceId &prismServiceId, const bool &isForNormalPhase = true);

    // Nowe the data members

    private :
    protected :
        vector<WaveServiceId> m_waveServiceIdsToInitializeDuringPrePhase;
        vector<WaveServiceId> m_waveServiceIdsToEnableDuringPrePhase;
        vector<WaveServiceId> m_waveServiceIdsToInstallDuringPrePhase;
        vector<WaveServiceId> m_waveServiceIdsToBootDuringPrePhase;

        vector<WaveServiceId> m_waveServiceIdsToInitialize;
        vector<WaveServiceId> m_waveServiceIdsToEnable;
        vector<WaveServiceId> m_waveServiceIdsToInstall;
        vector<WaveServiceId> m_waveServiceIdsToBoot;
        vector<WaveServiceId> m_waveServiceIdsToShutdown;
        vector<WaveServiceId> m_waveServiceIdsToUninstall;
        vector<WaveServiceId> m_waveServiceIdsToUninitialize;
        vector<WaveServiceId> m_waveServiceIdsToDisable;

        vector<WaveServiceId> m_waveServiceIdsToShutdownDuringPostPhase;
        vector<WaveServiceId> m_waveServiceIdsToUninstallDuringPostPhase;
        vector<WaveServiceId> m_waveServiceIdsToUninitializeDuringPostPhase;
        vector<WaveServiceId> m_waveServiceIdsToDisableDuringPostPhase;

        vector<WaveServiceId> m_waveServiceIdsToFailover;
        vector<WaveServiceId> m_waveServiceIdsToZeroize;

    public :
};

}

#endif // FRAMEWORKSEQUENCEGENERATOR_H
