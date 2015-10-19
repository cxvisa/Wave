/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKCONFIGURATIONCONTEXT_H
#define PRISMFRAMEWORKCONFIGURATIONCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include <string>

using namespace std;

namespace WaveNs
{

class WaveFrameworkConfigurationContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                     WaveFrameworkConfigurationContext     (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const string &waveFrameworkConfigurationFileName);
                                    ~WaveFrameworkConfigurationContext     ();

        string                      &getWaveFrameworkConfigurationFileName ();
        WaveFrameworkConfiguration &getWaveFrameworkConfigurationObject   ();
        bool                         getSyncToStandby                       ();
        void                         setSyncToStandby                       (const bool &syncToStandby);

    // Now the data members

    private :
        string                      m_waveFrameworkConfigurationFileName;
        WaveFrameworkConfiguration m_waveFrameworkConfigurationObject;
        bool                        m_syncToStandby;

    protected :
    public :
};

}

#endif // PRISMFRAMEWORKCONFIGURATIONCONTEXT_H
