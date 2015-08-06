/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Synchronization;

import java.util.concurrent.locks.Condition;

public class WaveCondition
{
    private WaveMutex m_waveMutex;
    private Condition m_condition;

    public WaveCondition (WaveMutex waveMutex)
    {
        m_waveMutex = waveMutex;

        if (null != m_waveMutex)
        {
            m_condition = m_waveMutex.newCondition ();
        }
        else
        {
            throw (new NullPointerException ());
        }
    }

    WaveConditionStatus awaitUninterruptibly ()
    {
        m_condition.awaitUninterruptibly ();

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }

    WaveConditionStatus signal ()
    {
        m_condition.signal ();

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }

    WaveConditionStatus signalAll ()
    {
        m_condition.signalAll ();

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }
}
