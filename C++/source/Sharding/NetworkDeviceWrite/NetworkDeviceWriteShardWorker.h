/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEWRITESHARDWORKER_H
#define NETWORKDEVICEWRITESHARDWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class NetworkDeviceWriteShardWorker : public WaveWorker
{
    private :
        void install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    protected :
    public :
                 NetworkDeviceWriteShardWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceWriteShardWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // NETWORKDEVICEWRITESHARDWORKER_H
