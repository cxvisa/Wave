/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "WaveCondition.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

WaveCondition::WaveCondition (WaveMutex *pAssociatedWaveMutex)
{
    waveAssert (NULL != pAssociatedWaveMutex, __FILE__, __LINE__);

    pthread_cond_init (&m_condition, NULL);
    m_pAssociatedWaveMutex = pAssociatedWaveMutex;
}

WaveCondition::WaveCondition (const WaveCondition &waveCondition)
{
    trace (TRACE_LEVEL_FATAL, "WaveCondition::WaveCondition : Copy constructing WaveCondition does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);
}

WaveCondition::~WaveCondition ()
{
    pthread_cond_destroy (&m_condition);
}

WaveCondition &WaveCondition::operator = (const WaveCondition &waveCondition)
{
    trace (TRACE_LEVEL_FATAL, "WaveCondition::operator = : Assigning to a WaveCondition does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);

    return (*this);
}

WaveConditionStatus WaveCondition::wait ()
{
    int status = pthread_cond_wait (&m_condition, &(m_pAssociatedWaveMutex->m_mutex));

    if (0 == status)
    {
        return (WAVE_CONDITION_SUCCESS);
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
        return (WAVE_CONDITION_ERROR);
    }
}

WaveConditionStatus WaveCondition::resume ()
{
    int status = pthread_cond_signal (&m_condition);

    if (0 == status)
    {
        return (WAVE_CONDITION_SUCCESS);
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
        return (WAVE_CONDITION_ERROR);
    }
}

WaveConditionStatus WaveCondition::resumeAll ()
{
    int status = pthread_cond_broadcast (&m_condition);

    if (0 == status)
    {
        return (WAVE_CONDITION_SUCCESS);
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);
        return (WAVE_CONDITION_ERROR);
    }
}

}
