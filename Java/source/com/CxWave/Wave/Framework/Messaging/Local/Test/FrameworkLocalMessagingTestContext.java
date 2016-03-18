/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;

public class FrameworkLocalMessagingTestContext extends WaveLinearSequencerContext
{
    private LocationId m_remoteLocationId;
    private UI32       m_numberOfMessagesToSend;
    private UI32       m_numberOfMessagesSend;

    public FrameworkLocalMessagingTestContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        super (waveAsynchronousContext, waveElement, steps);
    }

    public LocationId getRemoteLocationId ()
    {
        return m_remoteLocationId;
    }

    public void setRemoteLocationId (final LocationId remoteLocationId)
    {
        m_remoteLocationId = remoteLocationId;
    }

    public UI32 getNumberOfMessagesToSend ()
    {
        return m_numberOfMessagesToSend;
    }

    public void setNumberOfMessagesToSend (final UI32 numberOfMessagesToSend)
    {
        m_numberOfMessagesToSend = numberOfMessagesToSend;
    }

    public UI32 getNumberOfMessagesSend ()
    {
        return m_numberOfMessagesSend;
    }

    public void setNumberOfMessagesSend (final UI32 numberOfMessagesSend)
    {
        m_numberOfMessagesSend = numberOfMessagesSend;
    }
}
