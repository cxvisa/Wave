/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "WaveMutex.h"
#include "errno.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

WaveMutex::WaveMutex ()
{
    pthread_mutex_init (&m_mutex, NULL);
}

WaveMutex::~WaveMutex ()
{
    pthread_mutex_destroy (&m_mutex);
}

WaveMutexStatus WaveMutex::lock ()
{
    int status = pthread_mutex_lock (&m_mutex);

    if (0 == status)
    {
        return (WAVE_MUTEX_SUCCESS);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("Could not acquire lock : ") + status);
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MUTEX_COULD_NOT_LOCK);
    }
}

WaveMutexStatus WaveMutex::unlock()
{
    int status = pthread_mutex_unlock (&m_mutex);

    if (0 == status)
    {
        return (WAVE_MUTEX_SUCCESS);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MUTEX_COULD_NOT_UNLOCK);
    }
}

WaveMutexStatus WaveMutex::tryLock ()
{
    int status = pthread_mutex_trylock (&m_mutex);

    if (EBUSY == status)
    {
        return (WAVE_MUTEX_ALREADY_LOCKED);
    }
    else if (0 == status)
    {
        return (WAVE_MUTEX_SUCCESS);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_MUTEX_COULD_NOT_LOCK);
    }
}

}
