/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENT_H
#define WAVECLIENT_H

#include "Framework/Types/Types.h"

#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveClientConfiguration.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"                                 
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

typedef        WaveObjectManager *  (* NativeWaveServiceInstantiator) ();
typedef vector<WaveObjectManager *> (* NativeMultipleWaveServiceInstantiator) ();
typedef        SI32                 (* UpdateClientStatusFunctionPtr)( ManagementInterfaceMessage *pManagementInterfaceMessage );

class WaveClient
{
    private :
        static void   instantiateNativeWaveServices ();

    protected :
    public :
        static void   initialize                        (const WaveClientConfiguration &waveClientConfiguration);
        static string getTraceFileDirectory             ();
        static string getConfigurationFileDirectory     ();
        static string getProfileFileDirectory           ();

        static void   registerNativeService             (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase = true);
        static void   registerNativeServiceInternal     (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase = true);
        static void   registerNativeService             (NativeMultipleWaveServiceInstantiator pNativeMultipleWaveServiceInstantiator);
        static void   registerUpdateClientStatusFunction(UpdateClientStatusFunctionPtr pUpdateClientStatusFunctionPtr);
        static SI32   updateClientStatusFunction        (ManagementInterfaceMessage *pManagementInterfaceMessage);

    // Now the data members

    private :
        static vector<NativeWaveServiceInstantiator>         m_nativeWaveServiceInstantiators;
        static vector<bool>                                   m_nativeWaveServiceInstantiatorIsForNormalPhase;
        static vector<NativeMultipleWaveServiceInstantiator> m_nativeMultipleWaveServiceInstantiators;
        static UpdateClientStatusFunctionPtr                  m_updateClientStatusFunctionPtr;
        static WaveMutex                                     m_updateClientStatusFunctionPtrMutex;

    protected :
    public :
};

}

#endif // WAVECLIENT_H
