/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGEFACTORY_H
#define WAVEMESSAGEFACTORY_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveMessage;
class WaveObjectManager;

class WaveMessageFactory
{
    private :
    protected :
    public :
        static WaveMessage      *getMessageInstance                    (const WaveServiceId &serviceId, const UI32 &opcode);
        static WaveObjectManager *getWaveObjectManagerForMessage        (const WaveServiceId &serviceId, const UI32 &opcode);
        static WaveObjectManager *getWaveObjectManagerForEvent          (const WaveServiceId &serviceId, const UI32 &eventOpcode);
        static WaveObjectManager *getWaveObjectManagerForEventListener  (const LocationId &locationId, const WaveServiceId &serviceId, const UI32 &eventOpcode);
        static WaveMessage      *getManagementInterfaceMessageInstance (const string &waveClientName, const WaveServiceId &serviceId, const UI32 &opcode);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMESSAGEFACTORY_H
