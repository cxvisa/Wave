/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

public enum WaveBootMode
{
    WAVE_BOOT_UNKNOWN,
    WAVE_BOOT_FIRST_TIME,
    WAVE_BOOT_PERSISTENT,
    WAVE_BOOT_PERSISTENT_WITH_DEFAULT,
    WAVE_BOOT_SECONDARY_CONFIGURE,
    WAVE_BOOT_SECONDARY_UNCONFIGURE,
    WAVE_BOOT_SECONDARY_REJOIN,
    WAVE_BOOT_HASTANDBY,
    WAVE_BOOT_PREPARE_FOR_HA_BOOT
}
