/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class WaveJavaSourceRepository
{
    private static WaveJavaSourceRepository s_waveJavaSourceRepository = new WaveJavaSourceRepository ();

    private final Map<String, WaveJavaClass>      s_classes     = new HashMap<String, WaveJavaClass> ();
    private final Map<String, WaveJavaInterface>  s_interfaces  = new HashMap<String, WaveJavaInterface> ();
    private final Map<String, WaveJavaEnum>       s_enums       = new HashMap<String, WaveJavaEnum> ();
    private final Map<String, WaveJavaAnnotation> s_annotations = new HashMap<String, WaveJavaAnnotation> ();

    private WaveJavaSourceRepository ()

    {
    }

    public static WaveJavaSourceRepository getInstance ()
    {
        WaveAssertUtils.waveAssert (null != s_waveJavaSourceRepository);

        return (s_waveJavaSourceRepository);
    }

    private WaveJavaClass getWaveJavaClassInternal (final String waveJavaClassName)
    {
        return (s_classes.get (waveJavaClassName));
    }

    public static WaveJavaClass getWaveJavaClass (final String waveJavaClassName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaClassInternal (waveJavaClassName));
    }

    private WaveJavaInterface getWaveJavaInterfaceInternal (final String waveJavaInterfaceName)
    {
        return (s_interfaces.get (waveJavaInterfaceName));
    }

    public static WaveJavaInterface getWaveJavaInterface (final String waveJavaInterfaceName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaInterfaceInternal (waveJavaInterfaceName));
    }

    private WaveJavaEnum getWaveJavaEnumInternal (final String waveJavaEnumName)
    {
        return (s_enums.get (waveJavaEnumName));
    }

    public static WaveJavaEnum getWaveJavaEnum (final String waveJavaEnumName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaEnumInternal (waveJavaEnumName));
    }

    private WaveJavaAnnotation getWaveJavaAnnotationInternal (final String waveJavaAnnotationName)
    {
        return (s_annotations.get (waveJavaAnnotationName));
    }

    public static WaveJavaAnnotation getWaveJavaAnnotation (final String waveJavaAnnotationName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaAnnotationInternal (waveJavaAnnotationName));
    }
}
