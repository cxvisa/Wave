/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMAPPERLOCALBOOTCOMPLETIONWORKER_H
#define NETWORKMAPPERLOCALBOOTCOMPLETIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Boot/BootCompleteForThisLocationEvent.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkMapperLocalObjectManager;

class NetworkMapperLocalBootCompletionWorker : public WaveWorker
{
    private :
        virtual void initialize                                (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void boot                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void   listenForEvents                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void   bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);
    protected :
    public :
                 NetworkMapperLocalBootCompletionWorker (NetworkMapperLocalObjectManager *pNetworkMapperLocalObjectManager);
        virtual ~NetworkMapperLocalBootCompletionWorker ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // NETWORKMAPPERLOCALBOOTCOMPLETIONWORKER_H
