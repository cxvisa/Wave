/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Boot;

public enum WaveBootPhase
{
    WAVE_BOOT_PHASE_PRE_PHASE,
    WAVE_BOOT_PHASE_POST_PHASE,
    WAVE_BOOT_PHASE_AFTER_POST_PHASE,
    WAVE_BOOT_ROLL_BACK_BOOT_PHASE,
    WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2,
    WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE,
    WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0,
    WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE,
    WAVE_BOOT_PHASE_ALL_PHASES
}
