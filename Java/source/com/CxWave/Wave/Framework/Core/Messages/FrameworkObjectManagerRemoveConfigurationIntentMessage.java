/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Messages;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Messaging.Local.WaveServiceIndependentMessage;
import com.CxWave.Wave.Framework.Type.UI32;

public class FrameworkObjectManagerRemoveConfigurationIntentMessage extends WaveServiceIndependentMessage
{
    private UI32 m_configurationIntentMessageId;

    public FrameworkObjectManagerRemoveConfigurationIntentMessage ()
    {
        super (WaveFrameworkObjectManager.getWaveServiceId (), FrameworkObjectManagerOperationCodes.FRAMEWORK_OBJECT_MANAGER_REMOVE_CONFIGURATION_INTENT);
    }

    public UI32 getConfigurationIntentMessageId ()
    {
        return m_configurationIntentMessageId;
    }

    public void setConfigurationIntentMessageId (final UI32 configurationIntentMessageId)
    {
        m_configurationIntentMessageId = configurationIntentMessageId;
    }
}
