/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef FILEREPLAYENDAGENT_H
#define FILEREPLAYENDAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class FileReplayEndAgentContext;

class FileReplayEndAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            FileReplayEndAgent                  (WaveObjectManager *pWaveObjectManager);
        virtual            ~FileReplayEndAgent                  ();
        virtual ResourceId  execute                             ();

                ResourceId  getListOfEnabledServicesStep        (FileReplayEndAgentContext *pFileReplayEndAgentContext);
                ResourceId  sendFileReplayEndStep               (FileReplayEndAgentContext *pFileReplayEndAgentContext);

                bool        requiresFileReplayEndNotification   (const PrismServiceId &prismServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // FileReplayEndAgent_H
