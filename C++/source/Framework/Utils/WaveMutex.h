/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef PRISMMUTEX_H
#define PRISMMUTEX_H

#include "pthread.h"

namespace WaveNs
{

class WaveCondition;

typedef enum
{
    WAVE_MUTEX_SUCCESS = 0,
    WAVE_MUTEX_COULD_NOT_LOCK,
    WAVE_MUTEX_COULD_NOT_UNLOCK,
    WAVE_MUTEX_ALREADY_LOCKED
} WaveMutexStatus;

class WaveMutex
{
    private :
    protected :
    public :
                       WaveMutex ();
                       ~WaveMutex ();
        WaveMutexStatus lock     ();
        WaveMutexStatus unlock   ();
        WaveMutexStatus tryLock  ();

    // Now the data members

    private :
        pthread_mutex_t m_mutex;

    protected :
    public :

    friend class WaveCondition;
};

}

#endif //PRISMMUTEX_H
