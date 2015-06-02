/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKOBJECTMANAGERSERVICECONTROLWORKER_H
#define PRISMFRAMEWORKOBJECTMANAGERSERVICECONTROLWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class FrameworkObjectManagerServiceControlListMessage;
class FrameworkObjectManagerServiceSetCpuAffinityMessage;

class PrismFrameworkObjectManagerServiceControlWorker : public WaveWorker
{
    private :
        virtual PrismMessage *createMessageInstance               (const UI32 &operationCode);

                void          serviceControlListMessageHandler    (FrameworkObjectManagerServiceControlListMessage *pFrameworkObjectManagerServiceControlListMessage);
                void          serviceSetCpuAffinityMessageHandler (FrameworkObjectManagerServiceSetCpuAffinityMessage *pFrameworkObjectManagerServiceSetCpuAffinityMessage);

    protected :
    public :
                 PrismFrameworkObjectManagerServiceControlWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~PrismFrameworkObjectManagerServiceControlWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKOBJECTMANAGERSERVICECONTROLWORKER_H
