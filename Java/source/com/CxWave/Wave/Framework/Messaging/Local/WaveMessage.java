/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local;

import java.util.Arrays;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.MessageFactory.WaveMessageFactory;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.MultiThreading.WaveThreadId;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;
import com.CxWave.Wave.Framework.Type.WaveResourceId;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessagePriority;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageType;

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

    private WaveMessageType              m_type                                    = WaveMessageType.WAVE_MESSAGE_TYPE_REQUEST;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         // WaveMessageType
    private WaveMessagePriority          m_priority                                = WaveMessagePriority.WAVE_MESSAGE_PRIORITY_NORMAL;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       // WaveMessagePriority
    private WaveServiceId                m_serviceCode;
    private UI32                         m_operationCode;
    private UI32                         m_waveClientMessageId;
    private UI32                         m_messageId;
    private UI32                         m_messageIdAtOriginatingLocation;
    private WaveServiceId                m_senderServiceCode;
    private LocationId                   m_senderLocationId;
    private LocationId                   m_receiverLocationId;
    private boolean                      m_isOneWayMessage                         = false;;
    private boolean                      m_isSynchronousMessage                    = false;
    @NonSerializable
    private WaveMutex                    m_synchronizingMutex                      = new WaveMutex ();
    @NonSerializable
    private WaveCondition                m_synchronizingCondition                  = new WaveCondition (m_synchronizingMutex);
    private boolean                      m_isLastReply                             = true;
    private boolean                      m_isACopy                                 = false;
    private UI32                         m_originalMessageId;
    private ResourceId                   m_completionStatus                        = ResourceId.WAVE_MESSAGE_ERROR;
    private LocationId                   m_waveClientOriginatingLocationId         = LocationId.NullLocationId;
    private UI32                         m_waveNativeClientId                      = new UI32 (0);
    private UI32                         m_waveUserClientId                        = new UI32 (0);
    @NonSerializable
    private Map<UI32, WaveMessageBuffer> m_buffers;
    private boolean                      m_dropReplyAcrossLocations                = false;
    private String                       m_messageString;
    private boolean                      m_isConfigurationChanged                  = false;
    private boolean                      m_isConfigurationFlagSetByUser            = false;
    private String                       m_nestedSql;
    private UI32                         m_transactionCounter                      = new UI32 (0);
    private WaveThreadId                 m_waveMessageCreatorThreadId              = WaveThread.getSelf ();
    private LocationId                   m_surrogatingForLocationId                = LocationId.NullLocationId;
    private boolean                      m_needSurrogateSupportFlag                = false;
    private boolean                      m_isMessageBeingSurrogatedFlag            = false;

    private Vector<LocationId>           m_locationsForStatusPropagation;
    private Vector<WaveResourceId>       m_completionStatusForStatusPropagation;
    private Vector<String>               m_localizedCompletionStatusForStatusPropagation;
    private boolean                      m_isMessageSupportedWhenServiceIsPaused   = false;

    private Vector<String>               m_xPathStringsVectorForTimestampUpdate;

    // Multi Partition.
    private String                       m_partitionName;
    private LocationId                   m_partitionLocationIdForPropagation       = LocationId.NullLocationId;
    private boolean                      m_isPartitionContextPropagated            = false;
    private boolean                      m_isPartitionNameSetByUser                = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           // Not
    // serialized.
    // Only to prevent copy of partitionName from
    // m_pInputMessage during propagation.

    private boolean                      m_isConfigurationTimeChanged              = false;

    private boolean                      m_isAConfigurationIntent                  = false;
    private boolean                      m_isConfigurationIntentStored             = false;
    private boolean                      m_isALastConfigReplay                     = false;
    private UI32                         m_timeOutInMilliSeconds                   = new UI32 (6000);
    private boolean                      m_disconnectFromNodeAfterReply            = false;
    private boolean                      m_removeNodeFromKnownLocationAfterReply   = false;
    private boolean                      m_sendForOneWayConnection                 = false;

    private static UI32                  s_numberOfMessagesInTheSystemSoFar        = new UI32 (0);
    private static UI32                  s_numberOfMessagesDeletedInTheSystemSoFar = new UI32 (0);
    private static WaveMutex             s_messageCreationMutex                    = new WaveMutex ();

    protected WaveMessage (final WaveServiceId serviceCode, final WaveOperationCodeInterface operationCode)
    {
        m_serviceCode = serviceCode;
        m_operationCode = operationCode.getOperationCode ();

        s_messageCreationMutex.lock ();

        s_numberOfMessagesInTheSystemSoFar.increment ();

        s_messageCreationMutex.unlock ();
    }

    protected WaveMessage (final WaveServiceId serviceCode)
    {
        final UI32 operationCode = WaveMessage.getOperationCodeForMessageClass (getClass ());

        m_serviceCode = serviceCode;
        m_operationCode = operationCode;

        s_messageCreationMutex.lock ();

        s_numberOfMessagesInTheSystemSoFar.increment ();

        s_messageCreationMutex.unlock ();
    }

    private WaveMessage (final WaveMessage waveMessage)
    {
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveMessage::WaveMessage : Copy Constructing a WaveMessage does not make sense and hence not allowed.");
        WaveAssertUtils.waveAssert ();
    }

    public WaveMessageType getType ()
    {
        return m_type;
    }

    public void setType (final WaveMessageType type)
    {
        m_type = type;
    }

    public WaveMessagePriority getPriority ()
    {
        return m_priority;
    }

    public void setPriority (final WaveMessagePriority priority)
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

    public void setIsOneWayMessage (final boolean isOneWayMessage)
    {
        m_isOneWayMessage = isOneWayMessage;
    }

    public boolean getIsSynchronousMessage ()
    {
        return m_isSynchronousMessage;
    }

    private void setIsSynchronousMessage (final boolean isSynchronousMessage)
    {
        m_isSynchronousMessage = isSynchronousMessage;
    }

    public WaveMutex getSynchronizingMutex ()
    {
        return m_synchronizingMutex;
    }

    private void setSynchronizingMutex (final WaveMutex synchronizingMutex)
    {
        m_synchronizingMutex = synchronizingMutex;
    }

    public WaveCondition getSynchronizingCondition ()
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

    public ResourceId getCompletionStatus ()
    {
        return m_completionStatus;
    }

    public void setCompletionStatus (final ResourceId completionStatus)
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

    public WaveThreadId getWaveMessageCreatorThreadId ()
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

    public static UI32 getOperationCodeForMessageClass (final Class<?> messageClass)
    {
        WaveAssertUtils.waveAssert (null != messageClass);

        Object object = null;

        try
        {
            object = messageClass.newInstance ();
        }
        catch (final Exception exception)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveMessage.getOperationCodeForMessageClass : %s message class could not be instantiated.  Details : %s", messageClass.getName (), exception.toString ());

            WaveAssertUtils.waveAssert ();
        }

        final WaveMessage waveMessage = (WaveMessage) object;

        WaveAssertUtils.waveAssert (null != waveMessage);

        final UI32 operationCode = waveMessage.getOperationCode ();

        WaveAssertUtils.waveAssert (null != operationCode);

        return (operationCode);
    }

    public WaveMessage cloneThisMessage ()
    {
        final WaveMessage clonedWaveMessage = WaveMessageFactory.getMessageInstance (m_serviceCode, m_operationCode);
        final String serializedData;
        UI32 messageIdAtOriginatingLocation = new UI32 (0);
        UI32 originalMessageId = new UI32 (0);
        UI32 waveClientMessageId = new UI32 (0);

        WaveAssertUtils.waveAssert (null != clonedWaveMessage);

        if (null == clonedWaveMessage)
        {
            return (null);
        }

        // Prepare for serialization on this message.

        prepareForSerialization ();

        // Prepare for serialization and load the attributes from this message into the cloned message.

        messageIdAtOriginatingLocation = clonedWaveMessage.getMessageIdAtOriginatingLocation ();
        originalMessageId = clonedWaveMessage.getOriginalMessageId ();
        waveClientMessageId = clonedWaveMessage.getWaveClientMessageId ();

        clonedWaveMessage.prepareForSerialization ();
        clonedWaveMessage.loadFromSerializableObject (this);

        clonedWaveMessage.setMessageIdAtOriginatingLocation (messageIdAtOriginatingLocation);
        clonedWaveMessage.setOriginalMessageId (originalMessageId);
        clonedWaveMessage.setWaveClientMessageId (waveClientMessageId);

        clonedWaveMessage.m_isACopy = true;

        clonedWaveMessage.copyBuffersFrom (this);

        return (clonedWaveMessage);
    }

    void copyBuffersFrom (final WaveMessage waveMessage)
    {
        final Vector<UI32> bufferTagsVector = new Vector<UI32> ();
        int numberOfBuffers = 0;
        int i = 0;

        waveMessage.getBufferTags (bufferTagsVector);

        numberOfBuffers = bufferTagsVector.size ();

        for (i = 0; i < numberOfBuffers; i++)
        {
            byte[] buffer = null;
            int bufferSize = 0;
            WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_ERROR;

            buffer = waveMessage.findBuffer (bufferTagsVector.get (i));
            bufferSize = buffer.length;

            WaveAssertUtils.waveAssert (null != buffer);
            WaveAssertUtils.waveAssert (0 != bufferSize);

            status = addBuffer (bufferTagsVector.get (i), buffer, false);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveMessage::copyBuffersFrom : Copying a Buffer Failed.  Status : %s", (FrameworkToolKit.localize (status)));
                WaveAssertUtils.waveAssert (false);
            }
        }
    }
}
