/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Attributes.AttributesMap;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;

public class SerializableObject
{
    @NonSerializable
    protected AttributesMap m_attributesMap = null;

    protected SerializableObject ()
    {
    }

    protected void prepareForSerialization ()
    {
        if (null == m_attributesMap)
        {
            final String className = (getClass ()).getName ();

            final AttributesMap attributesMap = WaveJavaSourceRepository.getAttributesMapForInheritanceHierarchyForClass (className);

            WaveAssertUtils.waveAssert (null != attributesMap);

            m_attributesMap = attributesMap;

            m_attributesMap.setSerializableObject (this);
        }
    }

    public void loadFromWaveConfigurationFile (final String waveConfigurationFilePath)
    {
        prepareForSerialization ();

        m_attributesMap.loadFromWaveConfiguraitonFile (waveConfigurationFilePath);
    }
}
