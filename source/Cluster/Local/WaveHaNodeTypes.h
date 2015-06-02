/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef WAVEHANODETYPES_H
#define WAVEHANODETYPES_H

namespace WaveNs
{

typedef enum
{
    WAVE_HA_NODE_ACTIVE = 0,
    WAVE_HA_NODE_STANDBY_CONFIRMED = 1,
    WAVE_HA_NODE_STANDBY_UNCONFIRMED = 2
} WaveHaNodeRole;

}

#endif // WAVEHANODETYPES_H
