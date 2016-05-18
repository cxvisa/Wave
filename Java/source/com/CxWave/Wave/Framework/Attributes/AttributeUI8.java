/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashSet;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.UI8;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class AttributeUI8 extends Attribute
{
    public AttributeUI8 ()
    {
        super ();
    }

    public AttributeUI8 (final ReflectionAttribute reflectionAttribute)
    {
        super (reflectionAttribute);
    }

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        return (supportedDataTypes);
    }

    @Override
    public void toWaveString (final SerializableObject thisSerializableObject, final StringBuffer value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        final UI8 data = (UI8) object;

        WaveAssertUtils.waveAssert (null != data);

        value.append (data.toString ());
    }

    @Override
    public void fromWaveString (final SerializableObject thisSerializableObject, final String value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        final UI8 data = (UI8) object;

        final String valueString = value;

        data.fromWaveString (valueString);
    }
}
