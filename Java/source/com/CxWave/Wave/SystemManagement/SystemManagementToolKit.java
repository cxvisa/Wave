/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.SystemManagement;

import java.util.Vector;

public class SystemManagementToolKit
{
    private static Vector<String> s_yinPaths;
    private static String         s_wyserTagsFilePath;

    private SystemManagementToolKit ()
    {
    }

    public static Vector<String> getYinPaths ()
    {
        return s_yinPaths;
    }

    public static void setYinPaths (final Vector<String> yinPaths)
    {
        s_yinPaths = yinPaths;
    }

    public static String getWyserTagsFilePath ()
    {
        return s_wyserTagsFilePath;
    }

    public static void setWyserTagsFilePath (final String wyserTagsFilePath)
    {
        s_wyserTagsFilePath = wyserTagsFilePath;
    }

}
