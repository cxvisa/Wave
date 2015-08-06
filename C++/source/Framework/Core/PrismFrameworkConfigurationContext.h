/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKCONFIGURATIONCONTEXT_H
#define PRISMFRAMEWORKCONFIGURATIONCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/Core/PrismFrameworkConfiguration.h"
#include <string>

using namespace std;

namespace WaveNs
{

class PrismFrameworkConfigurationContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                     PrismFrameworkConfigurationContext     (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const string &prismFrameworkConfigurationFileName);
                                    ~PrismFrameworkConfigurationContext     ();

        string                      &getPrismFrameworkConfigurationFileName ();
        PrismFrameworkConfiguration &getPrismFrameworkConfigurationObject   ();
        bool                         getSyncToStandby                       ();
        void                         setSyncToStandby                       (const bool &syncToStandby);

    // Now the data members

    private :
        string                      m_prismFrameworkConfigurationFileName;
        PrismFrameworkConfiguration m_prismFrameworkConfigurationObject;
        bool                        m_syncToStandby;

    protected :
    public :
};

}

#endif // PRISMFRAMEWORKCONFIGURATIONCONTEXT_H
