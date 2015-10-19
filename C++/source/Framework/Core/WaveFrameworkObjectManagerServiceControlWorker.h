/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKOBJECTMANAGERSERVICECONTROLWORKER_H
#define WAVEFRAMEWORKOBJECTMANAGERSERVICECONTROLWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class FrameworkObjectManagerServiceControlListMessage;
class FrameworkObjectManagerServiceSetCpuAffinityMessage;

class WaveFrameworkObjectManagerServiceControlWorker : public WaveWorker
{
    private :
        virtual WaveMessage *createMessageInstance               (const UI32 &operationCode);

                void          serviceControlListMessageHandler    (FrameworkObjectManagerServiceControlListMessage *pFrameworkObjectManagerServiceControlListMessage);
                void          serviceSetCpuAffinityMessageHandler (FrameworkObjectManagerServiceSetCpuAffinityMessage *pFrameworkObjectManagerServiceSetCpuAffinityMessage);

    protected :
    public :
                 WaveFrameworkObjectManagerServiceControlWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~WaveFrameworkObjectManagerServiceControlWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // WAVEFRAMEWORKOBJECTMANAGERSERVICECONTROLWORKER_H
