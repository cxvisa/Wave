/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENT_H
#define WAVECLIENT_H

#include "Framework/Types/Types.h"

#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Core/WaveClientConfiguration.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"                                 
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

typedef        WaveObjectManager *  (* NativePrismServiceInstantiator) ();
typedef vector<WaveObjectManager *> (* NativeMultiplePrismServiceInstantiator) ();
typedef        SI32                 (* UpdateClientStatusFunctionPtr)( ManagementInterfaceMessage *pManagementInterfaceMessage );

class WaveClient
{
    private :
        static void   instantiateNativePrismServices ();

    protected :
    public :
        static void   initialize                        (const WaveClientConfiguration &waveClientConfiguration);
        static string getTraceFileDirectory             ();
        static string getConfigurationFileDirectory     ();
        static string getProfileFileDirectory           ();

        static void   registerNativeService             (NativePrismServiceInstantiator pNativePrismServiceInstantiator, const bool &isForNormalPhase = true);
        static void   registerNativeServiceInternal     (NativePrismServiceInstantiator pNativePrismServiceInstantiator, const bool &isForNormalPhase = true);
        static void   registerNativeService             (NativeMultiplePrismServiceInstantiator pNativeMultiplePrismServiceInstantiator);
        static void   registerUpdateClientStatusFunction(UpdateClientStatusFunctionPtr pUpdateClientStatusFunctionPtr);
        static SI32   updateClientStatusFunction        (ManagementInterfaceMessage *pManagementInterfaceMessage);

    // Now the data members

    private :
        static vector<NativePrismServiceInstantiator>         m_nativePrismServiceInstantiators;
        static vector<bool>                                   m_nativePrismServiceInstantiatorIsForNormalPhase;
        static vector<NativeMultiplePrismServiceInstantiator> m_nativeMultiplePrismServiceInstantiators;
        static UpdateClientStatusFunctionPtr                  m_updateClientStatusFunctionPtr;
        static PrismMutex                                     m_updateClientStatusFunctionPtrMutex;

    protected :
    public :
};

}

#endif // WAVECLIENT_H
