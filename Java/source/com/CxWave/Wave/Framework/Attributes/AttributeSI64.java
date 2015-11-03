/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashSet;
import java.util.Set;

public class AttributeSI64 extends Attribute
{
    public AttributeSI64 ()
    {
        super ();
    }

    public AttributeSI64 (final ReflectionAttribute reflectionAttribute)
    {
        super (reflectionAttribute);
    }

    @Override
    public Set<Class<?>> getSupportedDataTypes ()
    {
        final Set<Class<?>> supportedDataTypes = new HashSet<Class<?>> ();

        supportedDataTypes.add (long.class);
        supportedDataTypes.add (Long.class);

        return (supportedDataTypes);
    }
}
