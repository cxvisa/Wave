/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMULTICASTRECEIVEROBJECTMANAGER_H
#define WAVEMULTICASTRECEIVEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class WaveMulticastReceiverObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
    protected :
    public :
                                                WaveMulticastReceiverObjectManager ();
        virtual                                ~WaveMulticastReceiverObjectManager ();

        static  WaveMulticastReceiverObjectManager *getInstance                    ();
        static  WaveServiceId                  getWaveServiceId                  ();
        static  string                          getServiceName                     ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMULTICASTRECEIVEROBJECTMANAGER_H
