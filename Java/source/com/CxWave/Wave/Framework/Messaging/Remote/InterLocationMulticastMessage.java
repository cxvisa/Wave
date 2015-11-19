/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Remote;

import java.util.Map;
import java.util.Set;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@NonSerializable
public class InterLocationMulticastMessage extends WaveMessage
{
    String                      m_serializeString;
    Map<LocationId, ResourceId> m_locationStatus;
    Map<LocationId, LocationId> m_locationReplied;
    Set<LocationId>             m_locationsId;
    UI32                        m_numberOfMessagesSent = new UI32 (0);
    UI32                        m_originalMessageId;
    WaveMutex                   m_accessMutex          = new WaveMutex ();
    WaveMutex                   m_messageAccessMutex   = new WaveMutex ();

    public InterLocationMulticastMessage ()
    {
        super (InterLocationMessageTransportObjectManager.getWaveServiceId (), InterLocationTypes.INTERLOCATION_MESSAGE_FOR_MULTICAST_SEND);
    }
}
