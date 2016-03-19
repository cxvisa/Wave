/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local.Test;

import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Type.UI32;

public class FrameworkTestabilityEvent1 extends WaveEvent
{
    private UI32   m_eventUI32;
    private String m_eventString;

    public FrameworkTestabilityEvent1 ()
    {
        super (FrameworkLocalMessagingTestObjectManager.getWaveServiceId (), FrameworkLocalMessagingTestEventTypes.FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT1);
    }

    public UI32 getEventUI32 ()
    {
        return m_eventUI32;
    }

    public void setEventUI32 (final UI32 eventUI32)
    {
        m_eventUI32 = eventUI32;
    }

    public String getEventString ()
    {
        return m_eventString;
    }

    public void setEventString (final String eventString)
    {
        m_eventString = eventString;
    }
}
