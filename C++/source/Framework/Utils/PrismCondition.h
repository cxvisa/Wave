/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef PRISMCONDITION_H
#define PRISMCONDITION_H

#include <pthread.h>
#include "PrismMutex.h"

namespace WaveNs
{

typedef enum
{
    WAVE_CONDITION_SUCCESS = 0,
    WAVE_CONDITION_ERROR
} PrismConditionStatus;

class PrismCondition
{
    private :
    protected :
    public :
                              PrismCondition (PrismMutex *pAssociatedPrismMutex);
                              PrismCondition (const PrismCondition &prismCondition);
                             ~PrismCondition ();
        PrismCondition       &operator = (const PrismCondition &prismCondition);
        PrismConditionStatus  wait           ();
        PrismConditionStatus  resume         ();
        PrismConditionStatus  resumeAll      ();

    // Now the member variables

    private :
        pthread_cond_t  m_condition;
        PrismMutex     *m_pAssociatedPrismMutex;

    protected :
    public :

};

}

#endif //PRISMCONDITION_H
