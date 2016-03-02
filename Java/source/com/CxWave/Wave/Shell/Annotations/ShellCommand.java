/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell.Annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import com.CxWave.Wave.Shell.ShellDebug;

@Retention (RetentionPolicy.RUNTIME)
@Target (
    {
                    ElementType.METHOD
    })
public @interface ShellCommand
{
    public String token () default "";

    public Class shell () default ShellDebug.class;

    public String briefHelp () default "";
}
