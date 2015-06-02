/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef TIMERTYPES_H
#define TIMERTYPES_H

namespace WaveNs
{

#define             MAX_USEC                     1000000

typedef enum
{
    TIMER_ADD_TIMER         = 0,
    TIMER_DELETE_TIMER,
    TIMER_DELETE_ALL_TIMERS_FOR_SERVICE
} TimerOpCodes;

}

#endif //TIMERTYPES_H
