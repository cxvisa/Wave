/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Stack;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public final class WaveStackUtils
{
    private WaveStackUtils ()
    {
    }

    public StackTraceElement getCallerStackTraceElement ()
    {
        final Throwable throwable = new Throwable ();
        final String thisClassName = (getClass ()).getName ();

        final StackTraceElement[] stackTrace = throwable.getStackTrace ();

        final int stackLength = stackTrace.length;
        int i = 0;

        // First skip all of the stack entries that do not correspond to this class.

        for (i = 0; i < stackLength; i++)
        {
            if (!((stackTrace[i].getClassName ()).equals (thisClassName)))
            {
                continue;
            }
            else
            {
                break;
            }
        }

        // Next skip all of the entries that correspond to this class.

        for (; i < stackLength; i++)
        {
            if ((stackTrace[i].getClassName ()).equals (thisClassName))
            {
                continue;
            }
            else
            {
                break;
            }
        }

        if (i < stackLength)
        {
            return (stackTrace[i]);
        }
        else
        {
            return (null);
        }
    }

    public String getCallerFileName ()
    {
        final StackTraceElement stackTraceElement = getCallerStackTraceElement ();

        if (null != stackTraceElement)
        {
            return (stackTraceElement.getFileName ());
        }
        else
        {
            return (null);
        }
    }

    public String getCallerClassName ()
    {
        final StackTraceElement stackTraceElement = getCallerStackTraceElement ();

        if (null != stackTraceElement)
        {
            return (stackTraceElement.getClassName ());
        }
        else
        {
            return (null);
        }
    }

    public int getCallerLineNumber ()
    {
        final StackTraceElement stackTraceElement = getCallerStackTraceElement ();

        if (null != stackTraceElement)
        {
            return (stackTraceElement.getLineNumber ());
        }
        else
        {
            return (0);
        }
    }

    public static String getStackString (final Throwable throwable)
    {
        if (null == throwable)
        {
            return ("");
        }

        final StringWriter stringWriter = new StringWriter ();
        final PrintWriter printWriter = new PrintWriter (stringWriter);

        throwable.printStackTrace (printWriter);

        return (stringWriter.toString ());
    }

    public static String getStackTraceForCurrentThread ()
    {
        final StringBuilder stackTraceString = new StringBuilder ();

        final StackTraceElement[] stackTraceElements = Thread.currentThread ().getStackTrace ();

        for (final StackTraceElement stackTraceElement : stackTraceElements)
        {
            stackTraceString.append (stackTraceElement.toString ());

            stackTraceString.append ("\n");
        }

        return (stackTraceString.toString ());
    }

    public static boolean isMainThread ()
    {
        final StackTraceElement[] stackTraceElements = Thread.currentThread ().getStackTrace ();
        final int numberOfStackTraceElements = stackTraceElements.length;

        if (0 < numberOfStackTraceElements)
        {
            final String methodName = stackTraceElements[numberOfStackTraceElements - 1].getMethodName ();

            if (methodName.equals ("main"))
            {
                return (true);
            }
            else
            {
                return (false);
            }
        }
        else
        {
            return (false);
        }
    }

    public static String getMainClassNameForThisThread ()
    {
        final StackTraceElement[] stackTraceElements = Thread.currentThread ().getStackTrace ();
        final int numberOfStackTraceElements = stackTraceElements.length;

        if (0 < numberOfStackTraceElements)
        {
            final String methodName = stackTraceElements[numberOfStackTraceElements - 1].getMethodName ();

            if (methodName.equals ("main"))
            {
                return (stackTraceElements[numberOfStackTraceElements - 1].getClassName ());
            }
            else
            {
                return ("");
            }
        }
        else
        {
            return ("");
        }
    }

    public static String getMainClassCompactNameForThisThread ()
    {
        final String mainClassNameForThisThread = getMainClassNameForThisThread ();

        final Vector<String> mainClassNameForThisThreadTokens = new Vector<String> ();

        WaveStringUtils.tokenize (mainClassNameForThisThread, mainClassNameForThisThreadTokens, '.');

        final int numberOfTokens = mainClassNameForThisThreadTokens.size ();

        String mainClassCompactNameForThisThread = "";

        if (0 < numberOfTokens)
        {
            mainClassCompactNameForThisThread = mainClassNameForThisThreadTokens.lastElement ();
        }

        return (mainClassCompactNameForThisThread);
    }
}
