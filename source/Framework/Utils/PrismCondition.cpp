/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "PrismCondition.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

PrismCondition::PrismCondition (PrismMutex *pAssociatedPrismMutex)
{
    prismAssert (NULL != pAssociatedPrismMutex, __FILE__, __LINE__);

    pthread_cond_init (&m_condition, NULL);
    m_pAssociatedPrismMutex = pAssociatedPrismMutex;
}

PrismCondition::PrismCondition (const PrismCondition &prismCondition)
{
    trace (TRACE_LEVEL_FATAL, "PrismCondition::PrismCondition : Copy constructing PrismCondition does not make sense and hence not allowed.");
    prismAssert (false, __FILE__, __LINE__);
}

PrismCondition::~PrismCondition ()
{
    pthread_cond_destroy (&m_condition);
}

PrismCondition &PrismCondition::operator = (const PrismCondition &prismCondition)
{
    trace (TRACE_LEVEL_FATAL, "PrismCondition::operator = : Assigning to a PrismCondition does not make sense and hence not allowed.");
    prismAssert (false, __FILE__, __LINE__);

    return (*this);
}

PrismConditionStatus PrismCondition::wait ()
{
    int status = pthread_cond_wait (&m_condition, &(m_pAssociatedPrismMutex->m_mutex));

    if (0 == status)
    {
        return (WAVE_CONDITION_SUCCESS);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_CONDITION_ERROR);
    }
}

PrismConditionStatus PrismCondition::resume ()
{
    int status = pthread_cond_signal (&m_condition);

    if (0 == status)
    {
        return (WAVE_CONDITION_SUCCESS);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_CONDITION_ERROR);
    }
}

PrismConditionStatus PrismCondition::resumeAll ()
{
    int status = pthread_cond_broadcast (&m_condition);

    if (0 == status)
    {
        return (WAVE_CONDITION_SUCCESS);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
        return (WAVE_CONDITION_ERROR);
    }
}

}
