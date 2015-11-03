/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashSet;
import java.util.Set;

public class AttributeSI16 extends Attribute
{
    public AttributeSI16 ()
    {
        super ();
    }

    public AttributeSI16 (final ReflectionAttribute reflectionAttribute)
    {
        super (reflectionAttribute);
    }

    @Override
    public Set<Class<?>> getSupportedDataTypes ()
    {
        final Set<Class<?>> supportedDataTypes = new HashSet<Class<?>> ();

        supportedDataTypes.add (short.class);
        supportedDataTypes.add (Short.class);

        return (supportedDataTypes);
    }
}
