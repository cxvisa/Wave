/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENT_H
#define WAVESYSTEMMANAGEMENT_H

#include "Framework/Types/Types.h"

#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Trace/TraceObjectManager.h"
#include "Regression/RegressionTestObjectManager.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"
#include "Shell/ShellObjectManager.h"
#include "Framework/Core/Test/FrameworkTestability4ObjectManager.h"
#include "Framework/Timer/TimerObjectManager.h"
#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Timer/Test/TimerTestObjectManager.h"
#include "Framework/Core/WaveMainConfiguration.h"
#include "Framework/Core/Wave.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveSystemManagement
{
    private :
        static void instantiateNativePrismServices ();
        static void registerNativeServiceInternal      (NativePrismServiceInstantiator pNativePrismServiceInstantiator, const bool &isForNormalPhase = true, const ResourceId &serviceMode = WAVE_SERVICE_ACTIVE);

    protected :
    public :
        static void   initialize                                (const WaveMainConfiguration &waveMainConfiguration);
        static string getTraceFileDirectory                     ();
        static string getConfigurationFileDirectory             ();
        static string getProfileFileDirectory                   ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENT_H
