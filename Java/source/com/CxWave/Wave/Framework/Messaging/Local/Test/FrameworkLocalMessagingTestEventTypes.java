/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local.Test;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public enum FrameworkLocalMessagingTestEventTypes implements WaveOperationCodeInterface
{
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT1,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT2,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT3,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT4,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT5,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT6,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT7,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT8,
    FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT9;

    @Override
    public UI32 getOperationCode ()
    {
        return (new UI32 (ordinal ()));
    }

    @Override
    public int getOperationCodeIntValue ()
    {
        return (ordinal ());
    }
}
