/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Regression;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.UI32;

public class WaveTestObjectManager extends WaveLocalObjectManager
{
    private final Vector<String> m_testParameters  = new Vector<String> ();
    private final Vector<String> m_regressionInput = new Vector<String> ();

    public WaveTestObjectManager (final String waveLocalObjectManagerName)
    {
        super (waveLocalObjectManagerName);
    }

    public WaveTestObjectManager (final String waveLocalObjectManagerName, final UI32 stackSize)
    {
        super (waveLocalObjectManagerName, stackSize);
    }
}
