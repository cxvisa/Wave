/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef PRISMMUTEX_H
#define PRISMMUTEX_H

#include "pthread.h"

namespace WaveNs
{

class PrismCondition;

typedef enum
{
    WAVE_MUTEX_SUCCESS = 0,
    WAVE_MUTEX_COULD_NOT_LOCK,
    WAVE_MUTEX_COULD_NOT_UNLOCK,
    WAVE_MUTEX_ALREADY_LOCKED
} PrismMutexStatus;

class PrismMutex
{
    private :
    protected :
    public :
                       PrismMutex ();
                       ~PrismMutex ();
        PrismMutexStatus lock     ();
        PrismMutexStatus unlock   ();
        PrismMutexStatus tryLock  ();

    // Now the data members

    private :
        pthread_mutex_t m_mutex;

    protected :
    public :

    friend class PrismCondition;
};

}

#endif //PRISMMUTEX_H
