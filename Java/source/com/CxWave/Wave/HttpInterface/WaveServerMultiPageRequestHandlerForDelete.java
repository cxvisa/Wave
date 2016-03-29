/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;

public class WaveServerMultiPageRequestHandlerForDelete extends WaveServerMultiPageRequestHandler
{

    public WaveServerMultiPageRequestHandlerForDelete (final String relativePath)
    {
        super (relativePath);
    }

    @Override
    protected Method getMethodForWaveServerMultiPageHandler (final String waveJavaClassName, final String relativePath)
    {
        return (WaveJavaSourceRepository.getMethodForWaveServerMultiPageHandlerForDeleteInWaveJavaClass (waveJavaClassName, relativePath));
    }

}
