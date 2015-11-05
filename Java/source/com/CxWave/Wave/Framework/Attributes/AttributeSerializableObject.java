/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;

public class AttributeSerializableObject extends Attribute
{
    @Override
    public Set<String> getSupportedDataTypes ()
    {
        return (WaveJavaSourceRepository.getAllDescendantsTypeNamesForClass (SerializableObject.class.getName ()));
    }

}
