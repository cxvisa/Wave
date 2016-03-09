/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKDEVICEREADSHARDWORKER_H
#define NETWORKDEVICEREADSHARDWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class NetworkDeviceReadShardWorker : public WaveWorker
{
    private :
        void install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    protected :
    public :
                 NetworkDeviceReadShardWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~NetworkDeviceReadShardWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // NETWORKDEVICEREADSHARDWORKER_H
