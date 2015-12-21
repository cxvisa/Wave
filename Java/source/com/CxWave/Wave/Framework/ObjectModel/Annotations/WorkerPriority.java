/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;

@Retention (RetentionPolicy.RUNTIME)
@Target (
    { ElementType.TYPE
    })
public @interface WorkerPriority
{
    public WaveWorkerPriority value () default WaveWorkerPriority.WAVE_WORKER_PRIORITY_0;
}
