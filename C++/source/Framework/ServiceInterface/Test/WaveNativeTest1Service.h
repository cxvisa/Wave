/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVENATIVETEST1SERVICE_H
#define WAVENATIVETEST1SERVICE_H

#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ServiceInterface/Test/WaveNativeTest1ServiceMessages.h"

namespace WaveNs
{

class WaveNativeTest1Service : public WaveObjectManager
{
    private :
        WaveNativeTest1Service ();

    protected :
    public :
                                       ~WaveNativeTest1Service                ();

        static WaveNativeTest1Service *getInstance                            ();
        static WaveServiceId           getWaveServiceId                      ();

               void                     waveNativeTest1ServiceMessage1Handler (WaveNativeTest1ServiceMessage1 *pMsg);

    // Now the Data Memebers

    private :
    protected :
    public :
};

}

#endif // WAVENATIVETEST1SERVICE_H
