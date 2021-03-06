/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Contexts;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;

public class RegressionTestAsynchronousContext extends WaveAsynchronousContext
{
    public RegressionTestAsynchronousContext (final WaveElement caller, final String callbackMethodName, final Object callerContext)
    {
        super (caller, callbackMethodName, callerContext);
    }
}
