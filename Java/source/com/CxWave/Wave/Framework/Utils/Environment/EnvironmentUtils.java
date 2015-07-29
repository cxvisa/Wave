/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Environment;

import java.lang.management.ManagementFactory;
import java.lang.management.RuntimeMXBean;
import java.util.ArrayList;
import java.util.List;

public class EnvironmentUtils
{
    static List<String> s_virtualMachinecommandLineArguments;
    static List<String> s_classPathCommandLineArguments;

    EnvironmentUtils ()
    {
    }

    public static void recordAllCommandLineArguments ()
    {
        RuntimeMXBean runtimeMXBean = ManagementFactory.getRuntimeMXBean ();

        s_virtualMachinecommandLineArguments = runtimeMXBean.getInputArguments ();

        String classPathCommandLineArgumentsString = System.getProperty ("java.class.path");

        s_classPathCommandLineArguments = new ArrayList<String> ();

        if (null != classPathCommandLineArgumentsString)
        {
            for (String classPathComponent : classPathCommandLineArgumentsString.split (":"))
            {
                s_classPathCommandLineArguments.add (classPathComponent);
            }
        }
    }

    public static List<String> getVirtualMachineCommandLineArguments ()
    {
        return (s_virtualMachinecommandLineArguments);
    }

    public static List<String> getClassPathCommandLineArguments ()
    {
        return (s_classPathCommandLineArguments);
    }
}
