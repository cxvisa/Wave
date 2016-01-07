/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Messages;

import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Message;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Regression.WaveTestObjectManager;

@Message (om = WaveTestObjectManager.class)
public class RegressionPrepareMessage2 extends WaveMessage
{
    private final Vector<String> m_inputStrings = new Vector<String> ();

    public RegressionPrepareMessage2 ()
    {
        super (WaveServiceId.NullServiceId, FrameworkOpCodes.WAVE_OBJECT_MANAGER_PREPARE_FOR_REGRESSION2);
    }

    public RegressionPrepareMessage2 (final WaveServiceId id)
    {
        super (id);
    }

    public void addInputStrings (final Vector<String> inputStrings)
    {
        m_inputStrings.addAll (inputStrings);
    }

    public Vector<String> getInputStrings ()
    {
        return (m_inputStrings);
    }
}
