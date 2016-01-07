/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Contexts;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;

public class RegressionPrepareAsynchronousContext extends WaveAsynchronousContext
{
    Vector<String> m_inputStrings = new Vector<String> ();

    public RegressionPrepareAsynchronousContext (final WaveElement caller, final String callbackMethodName, final Object callerContext)
    {
        super (caller, callbackMethodName, callerContext);
    }

    public Vector<String> getInputStrings ()
    {
        return (m_inputStrings);
    }

    public void setInputStrings (final Vector<String> inputStrings)
    {
        m_inputStrings = inputStrings;
    }
}
