/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S
 ***************************************************************************/

#ifndef PRISMZEROIZEAGENT_H
#define PRISMZEROIZEAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Zeroize/PrismZeroizeAgentContext.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

class PrismZeroizeAgentContext;

class PrismZeroizeAgent : protected WaveWorker
{
    private :
        bool                isZeroizeAtBoot             ();
        bool                needsZeroize                ( const PrismServiceId &prismServiceId );
    protected :
    public :
                            PrismZeroizeAgent           (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
                            PrismZeroizeAgent           (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator, bool zeroizeAtBoot);
        virtual            ~PrismZeroizeAgent           ();
        virtual ResourceId  execute                     ();
        ResourceId          shutdownServicesStep        (PrismZeroizeAgentContext *pContext);
        ResourceId          executeZeroizeStep          (PrismZeroizeAgentContext *pContext);
        ResourceId          completeFIPSZeroizeStep     (PrismZeroizeAgentContext *pContext);
        ResourceId          prepareFIPSZeroizeStep      (PrismZeroizeAgentContext *pContext);


    // Now the data members

    private :
        FrameworkSequenceGenerator  &m_currentFrameworkSequenceGenerator;
        WaveObjectManager           *m_pWaveObjectManager;
        bool                        m_zeroizeAtBoot;

    protected :
    public :
};

}

#endif // PRISMZEROIZEAGENT_H
