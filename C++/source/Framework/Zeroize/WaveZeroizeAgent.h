/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S
 ***************************************************************************/

#ifndef WAVEZEROIZEAGENT_H
#define WAVEZEROIZEAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Zeroize/WaveZeroizeAgentContext.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

class WaveZeroizeAgentContext;

class WaveZeroizeAgent : protected WaveWorker
{
    private :
        bool                isZeroizeAtBoot             ();
        bool                needsZeroize                ( const WaveServiceId &waveServiceId );
    protected :
    public :
                            WaveZeroizeAgent           (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
                            WaveZeroizeAgent           (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator, bool zeroizeAtBoot);
        virtual            ~WaveZeroizeAgent           ();
        virtual ResourceId  execute                     ();
        ResourceId          shutdownServicesStep        (WaveZeroizeAgentContext *pContext);
        ResourceId          executeZeroizeStep          (WaveZeroizeAgentContext *pContext);
        ResourceId          completeFIPSZeroizeStep     (WaveZeroizeAgentContext *pContext);
        ResourceId          prepareFIPSZeroizeStep      (WaveZeroizeAgentContext *pContext);


    // Now the data members

    private :
        FrameworkSequenceGenerator  &m_currentFrameworkSequenceGenerator;
        WaveObjectManager           *m_pWaveObjectManager;
        bool                        m_zeroizeAtBoot;

    protected :
    public :
};

}

#endif // WAVEZEROIZEAGENT_H
