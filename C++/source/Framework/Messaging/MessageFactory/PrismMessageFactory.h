/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMMESSAGEFACTORY_H
#define PRISMMESSAGEFACTORY_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class PrismMessage;
class WaveObjectManager;

class PrismMessageFactory
{
    private :
    protected :
    public :
        static PrismMessage      *getMessageInstance                    (const WaveServiceId &serviceId, const UI32 &opcode);
        static WaveObjectManager *getWaveObjectManagerForMessage        (const WaveServiceId &serviceId, const UI32 &opcode);
        static WaveObjectManager *getWaveObjectManagerForEvent          (const WaveServiceId &serviceId, const UI32 &eventOpcode);
        static WaveObjectManager *getWaveObjectManagerForEventListener  (const LocationId &locationId, const WaveServiceId &serviceId, const UI32 &eventOpcode);
        static PrismMessage      *getManagementInterfaceMessageInstance (const string &waveClientName, const WaveServiceId &serviceId, const UI32 &opcode);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMMESSAGEFACTORY_H
