/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef WAVECONDITION_H
#define WAVECONDITION_H

#include <pthread.h>
#include "WaveMutex.h"

namespace WaveNs
{

typedef enum
{
    WAVE_CONDITION_SUCCESS = 0,
    WAVE_CONDITION_ERROR
} WaveConditionStatus;

class WaveCondition
{
    private :
    protected :
    public :
                              WaveCondition (WaveMutex *pAssociatedWaveMutex);
                              WaveCondition (const WaveCondition &waveCondition);
                             ~WaveCondition ();
        WaveCondition       &operator = (const WaveCondition &waveCondition);
        WaveConditionStatus  wait           ();
        WaveConditionStatus  resume         ();
        WaveConditionStatus  resumeAll      ();

    // Now the member variables

    private :
        pthread_cond_t  m_condition;
        WaveMutex     *m_pAssociatedWaveMutex;

    protected :
    public :

};

}

#endif //WAVECONDITION_H
