/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Boot;

import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;

@OwnerOM (om = WaveFrameworkObjectManager.class)
public class BootCompleteForThisLocationEvent extends WaveEvent
{
    private boolean m_logSchemaChangeFlag = false;

    public BootCompleteForThisLocationEvent ()
    {
        super (WaveFrameworkObjectManager.getWaveServiceId (), BootTypes.BOOT_COMPLETE_FOR_THIS_LOCATION);
    }

    public BootCompleteForThisLocationEvent (final boolean logSchemaChangeFlag)
    {
        super (WaveFrameworkObjectManager.getWaveServiceId (), BootTypes.BOOT_COMPLETE_FOR_THIS_LOCATION);

        m_logSchemaChangeFlag = logSchemaChangeFlag;
    }

    public boolean getLogSchemaChangeFlag ()
    {
        return (m_logSchemaChangeFlag);
    }
}
