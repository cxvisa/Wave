/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Stack;

import java.io.PrintWriter;
import java.io.StringWriter;

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
}
