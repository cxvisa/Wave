/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Remote;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@NonSerializable
public class InterLocationMulticastMessage extends WaveMessage
{
    String                      m_serializedStringToSend;
    Map<LocationId, ResourceId> m_locationStatus                     = new HashMap<LocationId, ResourceId> ();
    Map<LocationId, LocationId> m_locationsReplied                   = new HashMap<LocationId, LocationId> ();
    Set<LocationId>             m_locationIdsToSend                  = new HashSet<LocationId> ();
    UI32                        m_numberOfMessagesSentAndOutStanding = new UI32 (0);
    UI32                        m_messageIdForMessageToMulticast;
    WaveMutex                   m_accessMutex                        = new WaveMutex ();
    WaveMutex                   m_messageAccessMutex                 = new WaveMutex ();

    public InterLocationMulticastMessage ()
    {
        super (InterLocationMessageTransportObjectManager.getWaveServiceId (), InterLocationTypes.INTERLOCATION_MESSAGE_FOR_MULTICAST_SEND);
    }

    private void lockAccess ()
    {
        m_accessMutex.lock ();
    }

    private void unlockAccess ()
    {
        m_accessMutex.unlock ();
    }

    public String getSerializedStringToSend ()
    {
        return m_serializedStringToSend;
    }

    public void setSerializedStringToSend (final String serializedStringToSend)
    {
        m_serializedStringToSend = serializedStringToSend;
    }

    ResourceId getStatusForALocation (final LocationId locationId)
    {
        lockAccess ();

        final ResourceId status = m_locationStatus.get (locationId);

        unlockAccess ();

        return (status);
    }

    public void setStatusForALocation (final LocationId locationId, final ResourceId locationStatus)
    {
        lockAccess ();

        m_locationStatus.put (locationId, locationStatus);

        unlockAccess ();
    }

    public Set<LocationId> getLocationIdsToSend ()
    {
        return m_locationIdsToSend;
    }

    public void setLocationIdsToSend (final Set<LocationId> locationIdsToSend)
    {
        m_locationIdsToSend = locationIdsToSend;
    }

    public void increment ()
    {
        m_numberOfMessagesSentAndOutStanding.increment ();
    }

    public void decrement ()
    {
        m_numberOfMessagesSentAndOutStanding.decrement ();
    }

    public UI32 getMessageIdForMessageToMulticast ()
    {
        return m_messageIdForMessageToMulticast;
    }

    public void setMessageIdForMessageToMulticast (final UI32 messageIdForMessageToMulticast)
    {
        m_messageIdForMessageToMulticast = messageIdForMessageToMulticast;
    }

    public boolean areAllMessageRepliesReceived ()
    {
        lockAccess ();

        if (0 == (m_numberOfMessagesSentAndOutStanding.getValue ()))
        {
            unlockAccess ();
            return (true);
        }

        unlockAccess ();
        return (false);
    }

    public void messageOperationAccess ()
    {
        m_messageAccessMutex.lock ();
    }

    public void messageOperationReleaseAccess ()
    {
        m_messageAccessMutex.unlock ();
    }

    public boolean isMessageSentToThisLocation (final LocationId locationId)
    {
        return (m_locationIdsToSend.contains (locationId));
    }

    public boolean isMessageSentToThisLocationNotReplied (final LocationId locationId)
    {
        return (!(m_locationsReplied.containsKey (locationId)));
    }

    public void setMessageRepliedToThisLocation (final LocationId locationId)
    {
        if (!(m_locationsReplied.containsKey (locationId)))
        {
            m_locationsReplied.put (locationId, locationId);
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }
    }
}
