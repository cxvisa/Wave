/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECONDARYNODECONFIGUREPRISMBOOTAGENT_H
#define SECONDARYNODECONFIGUREPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{

class SecondaryNodeConfigurePrismBootAgent : public PrismBootAgent
{
    private :
        virtual bool           isAPersistentBoot                            ();
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId& prismServiceId);
        virtual bool           willBeAPrimaryLocation                       ();
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInstall                    (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (WaveServiceId prismServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &prismServiceId);
        virtual WaveBootReason getReason                                    () const;

    protected :
    public :
                            SecondaryNodeConfigurePrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~SecondaryNodeConfigurePrismBootAgent ();
        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);

    // now the data members

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // SECONDARYNODECONFIGUREPRISMBOOTAGENT_H
