/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEDISPATCHTYPES_H
#define LIGHTPULSEDISPATCHTYPES_H

namespace WaveNs
{

typedef enum
{
    LIGHT_PULSE_DISPATCH_RECEIVED_LIGHT_PULSE       = 0,
    LIGHT_PULSE_DISPATCH_REGISTER_FOR_LIGHT_PULSE   = 1,
    LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE = 2
} LightPulseDispatchTypes;

}
#endif // LIGHTPULSEDISPATCHTYPES_H
