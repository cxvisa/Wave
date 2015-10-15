/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Trace;

import com.CxWave.Wave.Framework.ObjectModel.ReservedWaveLocalObjectManager;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.ManagementInterface.ClientInterface.WaveUserInterfaceObjectManager;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveManagementInterfaceRole;

public class WaveTraceUtils
{
    public static class _Internal_
    {
        private _Internal_ ()
        {

        }
    }

    private static _Internal_ s__Internal_ = new _Internal_ ();

    private WaveTraceUtils ()
    {
    }

    public static void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        WaveManagementInterfaceRole waveManagementInterfceRole = FrameworkToolKit.getWaveManagementInterfaceRole ();

        if (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_SERVER == waveManagementInterfceRole)
        {
            (ReservedWaveLocalObjectManager.getInstance ()).traceReservedForUtils (s__Internal_, requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
        }
        else if (WaveManagementInterfaceRole.WAVE_MGMT_INTF_ROLE_CLIENT == waveManagementInterfceRole)
        {
            (WaveUserInterfaceObjectManager.getInstance ()).traceReservedForUtils (s__Internal_, requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
        }
    }
}
