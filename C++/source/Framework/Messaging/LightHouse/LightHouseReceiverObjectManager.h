/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSERECEIVEROBJECTMANAGER_H
#define LIGHTHOUSERECEIVEROBJECTMANAGER_H

#include <string>

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

using namespace std;

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;
class BootCompleteForThisLocationEvent;

class LightHouseReceiverObjectManager : public WaveLocalObjectManager
{
    private :
                    LightHouseReceiverObjectManager         ();

               void initialize                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
               void listenForEvents                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
               void boot                                    (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

               void bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);

        static UI32 sendMessageToMulticastGroup              (UI32 argc, vector<string> argv);
        static UI32 receiveMessageFromMulticastGroup         (UI32 argc, vector<string> argv);

    protected :
    public :
        virtual                                 ~LightHouseReceiverObjectManager ();
        static  LightHouseReceiverObjectManager *getInstance                     ();
        static  string                           getServiceName                  ();
        static  WaveServiceId                    getWaveServiceId                ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // LIGHTHOUSERECEIVEROBJECTMANAGER_H
