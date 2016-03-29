/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.HttpInterface.Annotations.Path;
import com.CxWave.Wave.HttpInterface.Annotations.PathMapping;

public abstract class WaveServerMultiPageRequestHandler
{
    private final String        m_relativePath;
    private Method              m_method              = null;
    private WaveServerMultiPage m_waveServerMultiPage = null;

    public WaveServerMultiPageRequestHandler (final String relativePath)
    {
        m_relativePath = relativePath;
    }

    public String getRelativePath ()
    {
        return (m_relativePath);
    }

    protected abstract Method getMethodForWaveServerMultiPageHandler (final String waveJavaClassName, final String relativePath);

    public void validateAndCompute (final WaveServerMultiPage waveServerMultiPage)
    {
        WaveAssertUtils.waveAssert (null != waveServerMultiPage);

        m_waveServerMultiPage = waveServerMultiPage;

        final Class<?> waveServerMultiPageClass = waveServerMultiPage.getClass ();

        WaveAssertUtils.waveAssert (null != waveServerMultiPageClass);

        final Method waveServerMultiPageHandler = getMethodForWaveServerMultiPageHandler (waveServerMultiPageClass.getTypeName (), m_relativePath);

        if (null == waveServerMultiPageHandler)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandler.validateAndCompute : Could not compute the wave server multipage handler in class %s formethod relative path %s.", waveServerMultiPageClass.getTypeName (), m_relativePath);
            WaveAssertUtils.waveAssert ();
        }

        m_method = waveServerMultiPageHandler;
    }

    void execute (final HttpRequest httpRequest)
    {
        WaveAssertUtils.waveAssert (null != m_method);

        final Class<?> parameterTypes[] = m_method.getParameterTypes ();
        final int numberOfParameters = parameterTypes.length;
        final Object[] paramterValues = new Object[numberOfParameters];

        for (int i = 0; i < numberOfParameters; i++)
        {
            final Class<?> parameterType = parameterTypes[i];

            if (String.class.equals (parameterType))
            {

            }
            else if (HttpRequest.class.equals (parameterType))
            {

            }
            else
            {

            }
        }

        try
        {
            m_method.invoke (m_waveServerMultiPage, httpRequest);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandler.execute : Failed to invoke method : %s, Details : %s", m_method.getName (), e.toString ());

            final Throwable cause = e.getCause ();

            if (null != cause)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandler.execute : Cause : %s", cause.toString ());

                WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (cause));
            }

            WaveTraceUtils.fatalTracePrintf ("%s", WaveStackUtils.getStackString (e));
        }
    }

    public String getAnnotatedPathMapping ()
    {
        WaveAssertUtils.waveAssert (null != m_method);

        final Path pathAnnotation = m_method.getAnnotation (Path.class);
        String annotatedPath = "";
        String path = "";

        if (null != pathAnnotation)
        {
            annotatedPath = pathAnnotation.name ();
        }

        if (WaveStringUtils.isNotBlank (annotatedPath))
        {
            path = annotatedPath;
        }

        path = path.trim ();

        if (path.endsWith ("/"))
        {
            path = path.substring (0, path.length () - 1);
        }

        final PathMapping pathMappingAnnotation = m_method.getAnnotation (PathMapping.class);
        String annotatedPathMapping = "";
        String pathMapping = path;

        if (null != pathMappingAnnotation)
        {
            annotatedPathMapping = pathMappingAnnotation.name ();
        }

        if (WaveStringUtils.isNotBlank (annotatedPathMapping))
        {
            pathMapping = annotatedPathMapping;
        }

        pathMapping = pathMapping.trim ();

        if (pathMapping.endsWith ("/"))
        {
            pathMapping = pathMapping.substring (0, path.length () - 1);
        }

        return (pathMapping);
    }
}
