/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Messages;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveBootReason;

public class WaveInitializeObjectManagerMessage extends WaveMessage
{
    private final WaveBootReason m_reason;

    public WaveInitializeObjectManagerMessage (final WaveServiceId id, final WaveBootReason reason)
    {
        super (id, FrameworkOpCodes.WAVE_OBJECT_MANAGER_INITIALIZE);

        m_reason = reason;
    }

    public WaveBootReason getReason ()
    {
        return m_reason;
    }
}
