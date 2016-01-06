/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Boot;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.WaveBootReason;

public class WaveAsynchronousContextForBootPhases extends WaveAsynchronousContext
{

    private WaveBootReason m_bootReason;

    public WaveAsynchronousContextForBootPhases (final WaveElement caller, final String callbackMethodName, final Object callerContext)
    {
        super (caller, callbackMethodName, callerContext);
    }

    public WaveBootReason getBootReason ()
    {
        return (m_bootReason);
    }

    public void setBootReason (final WaveBootReason bootReason)
    {
        m_bootReason = bootReason;
    }

}
