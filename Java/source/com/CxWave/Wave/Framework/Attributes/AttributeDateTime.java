/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

public class AttributeDateTime extends Attribute
{
    public AttributeDateTime ()
    {
        super ();
    }

    public AttributeDateTime (final ReflectionAttribute reflectionAttribute)
    {
        super (reflectionAttribute);
    }

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        supportedDataTypes.add (Date.class.getTypeName ());

        return (supportedDataTypes);
    }
}
