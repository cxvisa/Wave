/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashSet;
import java.util.Set;

public class AttributeSI8 extends Attribute
{
    public AttributeSI8 ()
    {
        super ();
    }

    public AttributeSI8 (final ReflectionAttribute reflectionAttribute)
    {
        super (reflectionAttribute);
    }

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        supportedDataTypes.add (byte.class.getTypeName ());
        supportedDataTypes.add (Byte.class.getTypeName ());

        return (supportedDataTypes);
    }
}
