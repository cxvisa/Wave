/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                              *
 ***************************************************************************/

#ifndef CLUSTERPHASE3COMPLETEEVENT_H
#define CLUSTERPHASE3COMPLETEEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class ClusterPhase3CompleteEvent : public PrismEvent
{
    private :

    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 ClusterPhase3CompleteEvent ();
        virtual ~ClusterPhase3CompleteEvent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CLUSTERPHASE3COMPLETEEVENT_H

