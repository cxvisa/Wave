/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKCONFIGURATIONCONTEXT_H
#define WAVEFRAMEWORKCONFIGURATIONCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include <string>

using namespace std;

namespace WaveNs
{

class WaveFrameworkConfigurationContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                     WaveFrameworkConfigurationContext     (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const string &waveFrameworkConfigurationFileName);
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

#endif // WAVEFRAMEWORKCONFIGURATIONCONTEXT_H
