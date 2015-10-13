/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef CONFIGREPLAYENDAGENT_H
#define CONFIGREPLAYENDAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ConfigReplayEndAgentContext;

class ConfigReplayEndAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            ConfigReplayEndAgent                (WaveObjectManager *pWaveObjectManager);
        virtual            ~ConfigReplayEndAgent                ();
        virtual ResourceId  execute                             ();

                ResourceId  getListOfEnabledServicesStep        (ConfigReplayEndAgentContext *pConfigReplayEndAgentContext);
                ResourceId  sendConfigReplayEndStep             (ConfigReplayEndAgentContext *pConfigReplayEndAgentContext);

                bool        requiresConfigReplayEndNotification (const WaveServiceId &waveServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // ConfigReplayEndAgent_H
