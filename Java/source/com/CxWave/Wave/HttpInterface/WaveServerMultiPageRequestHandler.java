/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.HttpInterface.Annotations.FormParam;
import com.CxWave.Wave.HttpInterface.Annotations.Path;
import com.CxWave.Wave.HttpInterface.Annotations.PathMapping;
import com.CxWave.Wave.HttpInterface.Annotations.PathParam;
import com.CxWave.Wave.HttpInterface.Annotations.QueryParam;

public abstract class WaveServerMultiPageRequestHandler
{
    private final String        m_relativePath;
    private Method              m_method               = null;
    private WaveServerMultiPage m_waveServerMultiPage  = null;
    private String              m_annotatedPathMapping = "";

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

        computeAnnotatedPathMapping ();
    }

    void execute (final HttpRequest httpRequest)
    {
        WaveAssertUtils.waveAssert (null != m_method);

        final Class<?> parameterTypes[] = m_method.getParameterTypes ();
        final int numberOfParameters = parameterTypes.length;
        final Object[] parameterValues = new Object[numberOfParameters];
        final Annotation[][] parameterAnnotations = m_method.getParameterAnnotations ();
        final Type genericParameterTypes[] = m_method.getGenericParameterTypes ();

        for (int i = 0; i < numberOfParameters; i++)
        {
            final Class<?> parameterType = parameterTypes[i];

            if (String.class.equals (parameterType))
            {
                final int numberOfParameterAnnotations = parameterAnnotations[i].length;
                int j = 0;

                for (j = 0; j < numberOfParameterAnnotations; j++)
                {
                    final Class<? extends Annotation> annotationType = (parameterAnnotations[i][j]).annotationType ();

                    if (annotationType.equals (PathParam.class))
                    {
                        final PathParam pathParam = (PathParam) (parameterAnnotations[i][j]);
                        final String pathParamName = pathParam.name ();

                        if (WaveStringUtils.isNotBlank (pathParamName))
                        {
                            parameterValues[i] = httpRequest.getPathParamterValue (pathParamName);
                        }
                        else
                        {
                            parameterValues[i] = null;
                        }

                        break;
                    }
                    else if (annotationType.equals (QueryParam.class))
                    {
                        final QueryParam queryParam = (QueryParam) (parameterAnnotations[i][j]);
                        final String queryParamName = queryParam.name ();

                        if (WaveStringUtils.isNotBlank (queryParamName))
                        {
                            parameterValues[i] = httpRequest.getQueryParamterValue (queryParamName);
                        }
                        else
                        {
                            parameterValues[i] = null;
                        }

                        break;
                    }
                    else if (annotationType.equals (FormParam.class))
                    {
                        final FormParam formParam = (FormParam) (parameterAnnotations[i][j]);
                        final String formParamName = formParam.name ();

                        if (WaveStringUtils.isNotBlank (formParamName))
                        {
                            parameterValues[i] = httpRequest.getFormParamterValue (formParamName);
                        }
                        else
                        {
                            parameterValues[i] = null;
                        }

                        break;
                    }
                }
            }
            else if (HttpRequest.class.equals (parameterType))
            {
                parameterValues[i] = httpRequest;
            }
            else
            {
                final Type genericParameterType = genericParameterTypes[i];

                if (genericParameterType instanceof ParameterizedType)
                {
                    WaveTraceUtils.infoTracePrintf ("ParameterizedType");

                    final ParameterizedType parameterizedType = (ParameterizedType) genericParameterType;

                    WaveAssertUtils.waveAssert (null != parameterizedType);

                    final Type ownerType = parameterizedType.getOwnerType ();
                    final Type rawType = parameterizedType.getRawType ();
                    String rawTypeName = null;

                    if (null != ownerType)
                    {
                        WaveTraceUtils.infoTracePrintf ("Owner Type : %s", ownerType.getTypeName ());
                    }

                    if (null != rawType)
                    {
                        rawTypeName = rawType.getTypeName ();
                        WaveTraceUtils.infoTracePrintf ("Raw   Type : %s", rawTypeName);
                    }
                    else
                    {
                        WaveAssertUtils.waveAssert ();
                    }

                    WaveAssertUtils.waveAssert (null != rawTypeName);

                    final Type[] actualTypeArguments = parameterizedType.getActualTypeArguments ();

                    for (final Type actualTypeArgument : actualTypeArguments)
                    {
                        WaveTraceUtils.infoTracePrintf ("Actual Type Argument : %s", actualTypeArgument.getTypeName ());
                    }

                    WaveAssertUtils.waveAssert (1 == actualTypeArguments.length);
                    WaveAssertUtils.waveAssert ((String.class.getName ()).equals (actualTypeArguments[0].getTypeName ()));

                    final int numberOfParameterAnnotations = parameterAnnotations[i].length;
                    int j = 0;
                    Vector<String> pathParamValues = null;

                    for (j = 0; j < numberOfParameterAnnotations; j++)
                    {
                        final Class<? extends Annotation> annotationType = (parameterAnnotations[i][j]).annotationType ();

                        if (annotationType.equals (PathParam.class))
                        {
                            final PathParam pathParam = (PathParam) (parameterAnnotations[i][j]);
                            final String pathParamName = pathParam.name ();

                            if (WaveStringUtils.isNotBlank (pathParamName))
                            {
                                pathParamValues = httpRequest.getPathParameterValues (pathParamName);
                            }

                            break;
                        }
                        else if (annotationType.equals (QueryParam.class))
                        {
                            final QueryParam queryParam = (QueryParam) (parameterAnnotations[i][j]);
                            final String queryParamName = queryParam.name ();

                            if (WaveStringUtils.isNotBlank (queryParamName))
                            {
                                pathParamValues = httpRequest.getQueryParameterValues (queryParamName);
                            }

                            break;
                        }
                        else if (annotationType.equals (FormParam.class))
                        {
                            final FormParam formParam = (FormParam) (parameterAnnotations[i][j]);
                            final String formParamName = formParam.name ();

                            if (WaveStringUtils.isNotBlank (formParamName))
                            {
                                pathParamValues = httpRequest.getFormParameterValues (formParamName);
                            }

                            break;
                        }
                    }

                    if ((List.class.getName ()).equals (rawTypeName))
                    {
                        final List<String> newList = new Vector<String> ();

                        if (null != pathParamValues)
                        {
                            newList.addAll (pathParamValues);
                        }

                        parameterValues[i] = newList;
                    }
                    else if ((Set.class.getName ()).equals (rawTypeName))
                    {
                        final Set<String> newSet = new HashSet<String> ();

                        if (null != pathParamValues)
                        {
                            newSet.addAll (pathParamValues);
                        }

                        parameterValues[i] = newSet;
                    }
                    else if ((SortedSet.class.getName ()).equals (rawTypeName))
                    {
                        final SortedSet<String> newSortedSet = new TreeSet<String> ();

                        if (null != pathParamValues)
                        {
                            newSortedSet.addAll (pathParamValues);
                        }

                        parameterValues[i] = newSortedSet;
                    }
                }
                else
                {
                    WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandler.execute : Currently we support only the following data types : HttpRequest, String and List<String>/Set<String>/SortedSet<String>");
                    WaveAssertUtils.waveAssert ();
                }
            }
        }

        try
        {
            m_method.invoke (m_waveServerMultiPage, parameterValues);
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

    public void computeAnnotatedPathMapping ()
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

        m_annotatedPathMapping = pathMapping;
    }

    public String getAnnotatedPathMapping ()
    {
        return (m_annotatedPathMapping);
    }
}
