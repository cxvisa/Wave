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
        vector<WaveServiceId> m_prismServiceIdsToInitializeDuringPrePhase;
        vector<WaveServiceId> m_prismServiceIdsToEnableDuringPrePhase;
        vector<WaveServiceId> m_prismServiceIdsToInstallDuringPrePhase;
        vector<WaveServiceId> m_prismServiceIdsToBootDuringPrePhase;

        vector<WaveServiceId> m_prismServiceIdsToInitialize;
        vector<WaveServiceId> m_prismServiceIdsToEnable;
        vector<WaveServiceId> m_prismServiceIdsToInstall;
        vector<WaveServiceId> m_prismServiceIdsToBoot;
        vector<WaveServiceId> m_prismServiceIdsToShutdown;
        vector<WaveServiceId> m_prismServiceIdsToUninstall;
        vector<WaveServiceId> m_prismServiceIdsToUninitialize;
        vector<WaveServiceId> m_prismServiceIdsToDisable;

        vector<WaveServiceId> m_prismServiceIdsToShutdownDuringPostPhase;
        vector<WaveServiceId> m_prismServiceIdsToUninstallDuringPostPhase;
        vector<WaveServiceId> m_prismServiceIdsToUninitializeDuringPostPhase;
        vector<WaveServiceId> m_prismServiceIdsToDisableDuringPostPhase;

        vector<WaveServiceId> m_prismServiceIdsToFailover;
        vector<WaveServiceId> m_prismServiceIdsToZeroize;

    public :
};

}

#endif // FRAMEWORKSEQUENCEGENERATOR_H
