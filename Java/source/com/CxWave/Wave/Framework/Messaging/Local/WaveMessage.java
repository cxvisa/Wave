/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local;

import java.util.Arrays;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.MultiThreading.WaveThreadId;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveResourceId;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

public class WaveMessage extends SerializableObject
{
    private class WaveMessageBuffer
    {
        byte[] m_buffer = null;

        public WaveMessageBuffer (final byte[] buffer, final boolean isBufferOwnedByMessage)
        {
            if (false == isBufferOwnedByMessage)
            {
                m_buffer = Arrays.copyOf (buffer, buffer.length);
            }
            else
            {
                m_buffer = buffer;
            }
        }

        public WaveMessageBuffer (final WaveMessageBuffer waveMessageBuffer)
        {
            m_buffer = Arrays.copyOf (waveMessageBuffer.m_buffer, waveMessageBuffer.m_buffer.length);
        }

        public void invalidate ()
        {
            m_buffer = null;
        }

        public UI32 getSize ()
        {
            int bufferSize = 0;

            if (null != m_buffer)
            {
                bufferSize = m_buffer.length;
            }

            return (new UI32 (bufferSize));
        }

        public byte[] getBuffer ()
        {
            return (m_buffer);
        }

        public void setBuffer (final byte[] buffer)
        {
            m_buffer = buffer;
        }
    }

    private WaveResourceId               m_type;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          // WaveMessageType
    private WaveResourceId               m_priority;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      // WaveMessagePriority
    private WaveServiceId                m_serviceCode;
    private UI32                         m_operationCode;
    private UI32                         m_waveClientMessageId;
    private UI32                         m_messageId;
    private UI32                         m_messageIdAtOriginatingLocation;
    private WaveServiceId                m_senderServiceCode;
    private LocationId                   m_senderLocationId;
    private LocationId                   m_receiverLocationId;
    private boolean                      m_isOneWayMessage;
    private boolean                      m_isSynchronousMessage;
    @NonSerializable
    private WaveMutex                    m_synchronizingMutex;
    @NonSerializable
    private WaveCondition                m_synchronizingCondition;
    private boolean                      m_isLastReply;
    private boolean                      m_isACopy;
    private UI32                         m_originalMessageId;
    private WaveResourceId               m_completionStatus;
    private LocationId                   m_waveClientOriginatingLocationId;
    private UI32                         m_waveNativeClientId;
    private UI32                         m_waveUserClientId;
    @NonSerializable
    private Map<UI32, WaveMessageBuffer> m_buffers;
    private boolean                      m_dropReplyAcrossLocations;
    private String                       m_messageString;
    private boolean                      m_isConfigurationChanged;
    private boolean                      m_isConfigurationFlagSetByUser;
    private String                       m_nestedSql;
    private UI32                         m_transactionCounter;
    private WaveThreadId                 m_waveMessageCreatorThreadId;
    private LocationId                   m_surrogatingForLocationId;
    private boolean                      m_needSurrogateSupportFlag;
    private boolean                      m_isMessageBeingSurrogatedFlag;

    private Vector<LocationId>           m_locationsForStatusPropagation;
    private Vector<WaveResourceId>       m_completionStatusForStatusPropagation;
    private Vector<String>               m_localizedCompletionStatusForStatusPropagation;
    private boolean                      m_isMessageSupportedWhenServiceIsPaused;

    private Vector<String>               m_xPathStringsVectorForTimestampUpdate;

    // Multi Partition.
    private String                       m_partitionName;
    private LocationId                   m_partitionLocationIdForPropagation;
    private boolean                      m_isPartitionContextPropagated;
    private boolean                      m_isPartitionNameSetByUser;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      // Not
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          // serialized.
    // Only to prevent copy of partitionName from
    // m_pInputMessage during propagation.

    private boolean                      m_isConfigurationTimeChanged;

    private boolean                      m_isAConfigurationIntent;
    private boolean                      m_isConfigurationIntentStored;
    private boolean                      m_isALastConfigReplay;
    private UI32                         m_timeOutInMilliSeconds;
    private boolean                      m_disconnectFromNodeAfterReply;
    private boolean                      m_removeNodeFromKnownLocationAfterReply;
    private boolean                      m_sendForOneWayConnection;

    protected <E extends Enum<E>> WaveMessage (final WaveServiceId serviceCode, final E operationCode)
    {
        m_serviceCode = serviceCode;
        m_operationCode = new UI32 (operationCode.ordinal ());
    }

    private WaveMessage (final WaveMessage waveMessage)
    {
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveMessage::WaveMessage : Copy Constructing a WaveMessage does not make sense and hence not allowed.");
        WaveAssertUtils.waveAssert ();
    }

    public WaveResourceId getType ()
    {
        return m_type;
    }

    public void setType (final WaveResourceId type)
    {
        m_type = type;
    }

    public WaveResourceId getPriority ()
    {
        return m_priority;
    }

    public void setPriority (final WaveResourceId priority)
    {
        m_priority = priority;
    }

    public WaveServiceId getServiceCode ()
    {
        return m_serviceCode;
    }

    public void setServiceCode (final WaveServiceId serviceCode)
    {
        m_serviceCode = serviceCode;
    }

    public UI32 getOperationCode ()
    {
        return m_operationCode;
    }

    public void setOperationCode (final UI32 operationCode)
    {
        m_operationCode = operationCode;
    }

    public UI32 getWaveClientMessageId ()
    {
        return m_waveClientMessageId;
    }

    public void setWaveClientMessageId (final UI32 waveClientMessageId)
    {
        m_waveClientMessageId = waveClientMessageId;
    }

    public UI32 getMessageId ()
    {
        return m_messageId;
    }

    public void setMessageId (final UI32 messageId)
    {
        m_messageId = messageId;
    }

    public UI32 getMessageIdAtOriginatingLocation ()
    {
        return m_messageIdAtOriginatingLocation;
    }

    public void setMessageIdAtOriginatingLocation (final UI32 messageIdAtOriginatingLocation)
    {
        m_messageIdAtOriginatingLocation = messageIdAtOriginatingLocation;
    }

    public WaveServiceId getSenderServiceCode ()
    {
        return m_senderServiceCode;
    }

    public void setSenderServiceCode (final WaveServiceId senderServiceCode)
    {
        m_senderServiceCode = senderServiceCode;
    }

    public LocationId getSenderLocationId ()
    {
        return m_senderLocationId;
    }

    public void setSenderLocationId (final LocationId senderLocationId)
    {
        m_senderLocationId = senderLocationId;
    }

    public LocationId getReceiverLocationId ()
    {
        return m_receiverLocationId;
    }

    public void setReceiverLocationId (final LocationId receiverLocationId)
    {
        m_receiverLocationId = receiverLocationId;
    }

    public boolean getIsOneWayMessage ()
    {
        return m_isOneWayMessage;
    }

    private void setIsOneWayMessage (final boolean isOneWayMessage)
    {
        m_isOneWayMessage = isOneWayMessage;
    }

    private boolean getIsSynchronousMessage ()
    {
        return m_isSynchronousMessage;
    }

    private void setIsSynchronousMessage (final boolean isSynchronousMessage)
    {
        m_isSynchronousMessage = isSynchronousMessage;
    }

    private WaveMutex getSynchronizingMutex ()
    {
        return m_synchronizingMutex;
    }

    private void setSynchronizingMutex (final WaveMutex synchronizingMutex)
    {
        m_synchronizingMutex = synchronizingMutex;
    }

    private WaveCondition getSynchronizingCondition ()
    {
        return m_synchronizingCondition;
    }

    private void setSynchronizingCondition (final WaveCondition synchronizingCondition)
    {
        m_synchronizingCondition = synchronizingCondition;
    }

    public boolean getIsLastReply ()
    {
        return m_isLastReply;
    }

    public void setIsLastReply (final boolean isLastReply)
    {
        m_isLastReply = isLastReply;
    }

    public boolean getIsACopy ()
    {
        return m_isACopy;
    }

    public void setIsACopy (final boolean isACopy)
    {
        m_isACopy = isACopy;
    }

    public UI32 getOriginalMessageId ()
    {
        return m_originalMessageId;
    }

    public void setOriginalMessageId (final UI32 originalMessageId)
    {
        m_originalMessageId = originalMessageId;
    }

    public WaveResourceId getCompletionStatus ()
    {
        return m_completionStatus;
    }

    public void setCompletionStatus (final WaveResourceId completionStatus)
    {
        m_completionStatus = completionStatus;
    }

    public LocationId getWaveClientOriginatingLocationId ()
    {
        return m_waveClientOriginatingLocationId;
    }

    public void setWaveClientOriginatingLocationId (final LocationId waveClientOriginatingLocationId)
    {
        m_waveClientOriginatingLocationId = waveClientOriginatingLocationId;
    }

    public UI32 getWaveNativeClientId ()
    {
        return m_waveNativeClientId;
    }

    public void setWaveNativeClientId (final UI32 waveNativeClientId)
    {
        m_waveNativeClientId = waveNativeClientId;
    }

    public UI32 getWaveUserClientId ()
    {
        return m_waveUserClientId;
    }

    public void setWaveUserClientId (final UI32 waveUserClientId)
    {
        m_waveUserClientId = waveUserClientId;
    }

    public Map<UI32, WaveMessageBuffer> getBuffers ()
    {
        return m_buffers;
    }

    public void setBuffers (final Map<UI32, WaveMessageBuffer> buffers)
    {
        m_buffers = buffers;
    }

    public boolean getDropReplyAcrossLocations ()
    {
        return m_dropReplyAcrossLocations;
    }

    public void setDropReplyAcrossLocations (final boolean dropReplyAcrossLocations)
    {
        m_dropReplyAcrossLocations = dropReplyAcrossLocations;
    }

    public String getMessageString ()
    {
        return m_messageString;
    }

    public void setMessageString (final String messageString)
    {
        m_messageString = messageString;
    }

    public boolean getIsConfigurationChanged ()
    {
        return m_isConfigurationChanged;
    }

    public void setIsConfigurationChanged (final boolean isConfigurationChanged)
    {
        m_isConfigurationChanged = isConfigurationChanged;
    }

    public boolean getIsConfigurationFlagSetByUser ()
    {
        return m_isConfigurationFlagSetByUser;
    }

    public void setIsConfigurationFlagSetByUser (final boolean isConfigurationFlagSetByUser)
    {
        m_isConfigurationFlagSetByUser = isConfigurationFlagSetByUser;
    }

    public String getNestedSql ()
    {
        return m_nestedSql;
    }

    public void setNestedSql (final String nestedSql)
    {
        m_nestedSql = nestedSql;
    }

    public UI32 getTransactionCounter ()
    {
        return m_transactionCounter;
    }

    public void setTransactionCounter (final UI32 transactionCounter)
    {
        m_transactionCounter = transactionCounter;
    }

    private WaveThreadId getWaveMessageCreatorThreadId ()
    {
        return m_waveMessageCreatorThreadId;
    }

    public void setWaveMessageCreatorThreadId (final WaveThreadId waveMessageCreatorThreadId)
    {
        m_waveMessageCreatorThreadId = waveMessageCreatorThreadId;
    }

    public LocationId getSurrogatingForLocationId ()
    {
        return m_surrogatingForLocationId;
    }

    public void setSurrogatingForLocationId (final LocationId surrogatingForLocationId)
    {
        m_surrogatingForLocationId = surrogatingForLocationId;
    }

    public boolean getNeedSurrogateSupportFlag ()
    {
        return m_needSurrogateSupportFlag;
    }

    public void setNeedSurrogateSupportFlag (final boolean needSurrogateSupportFlag)
    {
        m_needSurrogateSupportFlag = needSurrogateSupportFlag;
    }

    public boolean getIsMessageBeingSurrogatedFlag ()
    {
        return m_isMessageBeingSurrogatedFlag;
    }

    public void setIsMessageBeingSurrogatedFlag (final boolean isMessageBeingSurrogatedFlag)
    {
        m_isMessageBeingSurrogatedFlag = isMessageBeingSurrogatedFlag;
    }

    public Vector<LocationId> getLocationsForStatusPropagation ()
    {
        return m_locationsForStatusPropagation;
    }

    public void setLocationsForStatusPropagation (final Vector<LocationId> locationsForStatusPropagation)
    {
        m_locationsForStatusPropagation = locationsForStatusPropagation;
    }

    public Vector<WaveResourceId> getCompletionStatusForStatusPropagation ()
    {
        return m_completionStatusForStatusPropagation;
    }

    public void setCompletionStatusForStatusPropagation (final Vector<WaveResourceId> completionStatusForStatusPropagation)
    {
        m_completionStatusForStatusPropagation = completionStatusForStatusPropagation;
    }

    public Vector<String> getLocalizedCompletionStatusForStatusPropagation ()
    {
        return m_localizedCompletionStatusForStatusPropagation;
    }

    public void setLocalizedCompletionStatusForStatusPropagation (final Vector<String> localizedCompletionStatusForStatusPropagation)
    {
        m_localizedCompletionStatusForStatusPropagation = localizedCompletionStatusForStatusPropagation;
    }

    public boolean getIsMessageSupportedWhenServiceIsPaused ()
    {
        return m_isMessageSupportedWhenServiceIsPaused;
    }

    public void setIsMessageSupportedWhenServiceIsPaused (final boolean isMessageSupportedWhenServiceIsPaused)
    {
        m_isMessageSupportedWhenServiceIsPaused = isMessageSupportedWhenServiceIsPaused;
    }

    public Vector<String> getxPathStringsVectorForTimestampUpdate ()
    {
        return m_xPathStringsVectorForTimestampUpdate;
    }

    public void setxPathStringsVectorForTimestampUpdate (final Vector<String> xPathStringsVectorForTimestampUpdate)
    {
        m_xPathStringsVectorForTimestampUpdate = xPathStringsVectorForTimestampUpdate;
    }

    public String getPartitionName ()
    {
        return m_partitionName;
    }

    public void setPartitionName (final String partitionName)
    {
        m_partitionName = partitionName;
    }

    public LocationId getPartitionLocationIdForPropagation ()
    {
        return m_partitionLocationIdForPropagation;
    }

    public void setPartitionLocationIdForPropagation (final LocationId partitionLocationIdForPropagation)
    {
        m_partitionLocationIdForPropagation = partitionLocationIdForPropagation;
    }

    public boolean getIsPartitionContextPropagated ()
    {
        return m_isPartitionContextPropagated;
    }

    public void setIsPartitionContextPropagated (final boolean isPartitionContextPropagated)
    {
        m_isPartitionContextPropagated = isPartitionContextPropagated;
    }

    public boolean getIsPartitionNameSetByUser ()
    {
        return m_isPartitionNameSetByUser;
    }

    public void setIsPartitionNameSetByUser (final boolean isPartitionNameSetByUser)
    {
        m_isPartitionNameSetByUser = isPartitionNameSetByUser;
    }

    public boolean getIsConfigurationTimeChanged ()
    {
        return m_isConfigurationTimeChanged;
    }

    public void setIsConfigurationTimeChanged (final boolean isConfigurationTimeChanged)
    {
        m_isConfigurationTimeChanged = isConfigurationTimeChanged;
    }

    public boolean getIsAConfigurationIntent ()
    {
        return m_isAConfigurationIntent;
    }

    public void setIsAConfigurationIntent (final boolean isAConfigurationIntent)
    {
        m_isAConfigurationIntent = isAConfigurationIntent;
    }

    public boolean getIsConfigurationIntentStored ()
    {
        return m_isConfigurationIntentStored;
    }

    public void setIsConfigurationIntentStored (final boolean isConfigurationIntentStored)
    {
        m_isConfigurationIntentStored = isConfigurationIntentStored;
    }

    public boolean getIsALastConfigReplay ()
    {
        return m_isALastConfigReplay;
    }

    public void setIsALastConfigReplay (final boolean isALastConfigReplay)
    {
        m_isALastConfigReplay = isALastConfigReplay;
    }

    public UI32 getTimeOutInMilliSeconds ()
    {
        return m_timeOutInMilliSeconds;
    }

    public void setTimeOutInMilliSeconds (final UI32 timeOutInMilliSeconds)
    {
        m_timeOutInMilliSeconds = timeOutInMilliSeconds;
    }

    public boolean getDisconnectFromNodeAfterReply ()
    {
        return m_disconnectFromNodeAfterReply;
    }

    public void setDisconnectFromNodeAfterReply (final boolean disconnectFromNodeAfterReply)
    {
        m_disconnectFromNodeAfterReply = disconnectFromNodeAfterReply;
    }

    public boolean getRemoveNodeFromKnownLocationAfterReply ()
    {
        return m_removeNodeFromKnownLocationAfterReply;
    }

    public void setRemoveNodeFromKnownLocationAfterReply (final boolean removeNodeFromKnownLocationAfterReply)
    {
        m_removeNodeFromKnownLocationAfterReply = removeNodeFromKnownLocationAfterReply;
    }

    public boolean getSendForOneWayConnection ()
    {
        return m_sendForOneWayConnection;
    }

    public void setSendForOneWayConnection (final boolean sendForOneWayConnection)
    {
        m_sendForOneWayConnection = sendForOneWayConnection;
    }

    public WaveMessageStatus addBuffer (final UI32 tag, final byte[] buffer, final boolean bufferWillBeOwnedByMessage)
    {
        byte[] tempBuffer = null;

        if (null == buffer)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveMessage::addBuffer : Cannot add NULL buffer to a WaveMessage.");
            WaveAssertUtils.waveAssert ();

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_ADDING_NULL_BUFFER);
        }

        tempBuffer = findBuffer (tag);

        if (null != tempBuffer)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveMessage::addBuffer : A buffer already exists with the tag : %d", tag);
            WaveAssertUtils.waveAssert ();

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_BUFFER_WITH_TAG_EXISTS);
        }
        else
        {
            final WaveMessageBuffer waveMessageBuffer = new WaveMessageBuffer (buffer, bufferWillBeOwnedByMessage);

            m_buffers.put (tag, waveMessageBuffer);

            return (WaveMessageStatus.WAVE_MESSAGE_SUCCESS);
        }
    }

    public byte[] findBuffer (final UI32 tag)
    {
        final WaveMessageBuffer waveMessageBuffer = m_buffers.get (tag);

        if (null != waveMessageBuffer)
        {
            return (waveMessageBuffer.getBuffer ());
        }
        else
        {
            return (null);
        }
    }

    public byte[] transferBufferToUser (final UI32 tag)
    {
        final WaveMessageBuffer waveMessageBuffer = m_buffers.remove (tag);

        return (waveMessageBuffer.getBuffer ());
    }

    public WaveMessageStatus removeBuffer (final UI32 tag)
    {
        final WaveMessageBuffer waveMessageBuffer = m_buffers.remove (tag);

        if (null == waveMessageBuffer)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveMessage::addBuffer : A buffer does not exist with the tag : %s", tag.toString ());

            return (WaveMessageStatus.WAVE_MESSAGE_ERROR_BUFFER_WITH_TAG_DOES_NOT_EXIST);
        }
        else
        {
            return (WaveMessageStatus.WAVE_MESSAGE_SUCCESS);
        }
    }

    public UI32 getNumberOfBuffers ()
    {
        return (new UI32 (m_buffers.size ()));
    }

    public void removeAllBuffers ()
    {
        m_buffers.clear ();
    }

    public void getBufferTags (final Vector<UI32> bufferTags)
    {
        WaveAssertUtils.waveAssert (null != bufferTags);

        for (final UI32 tag : m_buffers.keySet ())
        {
            bufferTags.add (tag);
        }
    }
}
