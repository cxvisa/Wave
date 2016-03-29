/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;

public class WaveServerMultiPageRequestHandlerForPut extends WaveServerMultiPageRequestHandler
{

    public WaveServerMultiPageRequestHandlerForPut (final String relativePath)
    {
        super (relativePath);
    }

    @Override
    protected Method getMethodForWaveServerMultiPageHandler (final String waveJavaClassName, final String relativePath)
    {
        return (WaveJavaSourceRepository.getMethodForWaveServerMultiPageHandlerForPutInWaveJavaClass (waveJavaClassName, relativePath));
    }

}
