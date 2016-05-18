/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.text.DateFormat;
import java.text.FieldPosition;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class AttributeDateTime extends Attribute
{
    static final DateFormat s_dateFormat    = new SimpleDateFormat ("yyyy-MM-dd HH:mm:ss");
    final FieldPosition     s_fieldPosition = new FieldPosition (DateFormat.Field.SECOND);

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

    @Override
    public void toWaveString (final SerializableObject thisSerializableObject, final StringBuffer value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        final Date data = (Date) object;

        WaveAssertUtils.waveAssert (null != data);

        final StringBuffer newValue = s_dateFormat.format (data, value, s_fieldPosition);
    }

    @Override
    public void fromWaveString (final SerializableObject thisSerializableObject, final String value)
    {
        Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            if (WaveStringUtils.isNotBlank (value))
            {
                object = new Date ();
            }
            else
            {
                return;
            }
        }

        final Date data = (Date) object;

        final String valueString = value;

        try
        {
            final Date parsedDate = s_dateFormat.parse (valueString);

            setValue (thisSerializableObject, parsedDate);
        }
        catch (final ParseException e)
        {
            WaveTraceUtils.fatalTracePrintf ("AttributeDateTime.fromWaveString : Could not parse the input Date : %s, Details : %s", valueString, e.toString ());
        }
    }
}
