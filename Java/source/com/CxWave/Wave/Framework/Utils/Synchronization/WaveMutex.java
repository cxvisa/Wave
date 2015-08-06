/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Synchronization;

import java.util.concurrent.locks.ReentrantLock;

public class WaveMutex extends ReentrantLock
{
    private static final long serialVersionUID = 7701954014021005458L;

    public WaveMutexStatus tryLockWithStatus ()
    {
        boolean succeeded = super.tryLock ();

        if (succeeded)
        {
            return (WaveMutexStatus.WAVE_MUTEX_SUCCESS);
        }
        else
        {
            return (WaveMutexStatus.WAVE_MUTEX_COULD_NOT_LOCK);
        }
    }
}
