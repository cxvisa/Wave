/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/

#ifndef CLUSTERPHASE3STARTEVENT_H
#define CLUSTERPHASE3STARTEVENT_H
#include "Framework/Messaging/Local/WaveEvent.h"

namespace WaveNs
{

class ClusterPhase3StartEvent : public WaveEvent
{
    private :

    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 ClusterPhase3StartEvent ();
        virtual ~ClusterPhase3StartEvent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CLUSTERPHASE3STARTEVENT_H

