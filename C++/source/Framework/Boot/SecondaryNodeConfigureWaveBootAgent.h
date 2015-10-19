/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECONDARYNODECONFIGUREWAVEBOOTAGENT_H
#define SECONDARYNODECONFIGUREWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{

class SecondaryNodeConfigureWaveBootAgent : public WaveBootAgent
{
    private :
        virtual bool           isAPersistentBoot                            ();
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId& waveServiceId);
        virtual bool           willBeAPrimaryLocation                       ();
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInstall                    (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (WaveServiceId waveServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &waveServiceId);
        virtual WaveBootReason getReason                                    () const;

    protected :
    public :
                            SecondaryNodeConfigureWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~SecondaryNodeConfigureWaveBootAgent ();
        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);

    // now the data members

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // SECONDARYNODECONFIGUREWAVEBOOTAGENT_H
