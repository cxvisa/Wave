/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "WaveMessage.h"
#include "Framework/Utils/WaveCondition.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Messaging/MessageFactory/WaveMessageFactory.h"
#include "Framework/Messaging/MessageTracker/MessageTracker.h"
#include "Framework/Utils/MemoryUtils.h"
#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

static UI32      s_numberOfMessagesInTheSystemSoFar = 0;
static UI32      s_numberOfMessagesDeletedInTheSystemSoFar = 0;
static WaveMutex *pMessageCreationMutex              = NULL;

WaveMessage::WaveMessageBuffer::WaveMessageBuffer (UI32 size, const void *pBuffer, bool ownedByMessage)
    : m_size (size),
      m_pBuffer ((void *) pBuffer)
{
    if (false == ownedByMessage)
    {
        m_pBuffer = new UI8[size];
        memcpy (m_pBuffer, pBuffer, size);
    }
}

WaveMessage::WaveMessageBuffer::WaveMessageBuffer (const WaveMessage::WaveMessageBuffer &waveMessagebuffer)
{
    m_size    = waveMessagebuffer.m_size;

    m_pBuffer = new UI8[m_size];
    memcpy (m_pBuffer, waveMessagebuffer.m_pBuffer, m_size);
}

WaveMessage::WaveMessageBuffer::~WaveMessageBuffer ()
{
    destroy ();
}

WaveMessage::WaveMessageBuffer &WaveMessage::WaveMessageBuffer::operator = (const WaveMessage::WaveMessageBuffer &waveMessagebuffer)
{
    destroy ();

    m_size    = waveMessagebuffer.m_size;

    m_pBuffer = new UI8[m_size];
    memcpy (m_pBuffer, waveMessagebuffer.m_pBuffer, m_size);

    return (*this);
}

void WaveMessage::WaveMessageBuffer::destroy ()
{
    m_size = 0;

    if (NULL != m_pBuffer)
    {
        delete[] (reinterpret_cast<UI8 *> (m_pBuffer));
        m_pBuffer = NULL;
    }
}

void WaveMessage::WaveMessageBuffer::invalidateBuffer ()
{
    m_size    = 0;
    m_pBuffer = NULL;
}

UI32 WaveMessage::WaveMessageBuffer::getSize () const
{
    return (m_size);
}

void *WaveMessage::WaveMessageBuffer::getPBuffer () const
{
    return (m_pBuffer);
}

void WaveMessage::WaveMessageBuffer::setPBuffer (void *pBuffer)
{
    m_pBuffer = pBuffer;
}

WaveMessage::WaveMessage (WaveServiceId serviceCode, UI32 operationCode)
    : m_serviceCode                             (serviceCode),
      m_operationCode                           (operationCode),
      m_senderLocationId                        (FrameworkToolKit::getThisLocationId ()),
      m_receiverLocationId                      (FrameworkToolKit::getThisLocationId ()),
      m_isOneWayMessage                         (false),
      m_isSynchronousMessage                    (false),
      m_pSynchronizingMutex                     (NULL),
      m_pSynchronizingCondition                 (NULL),
      m_isLastReply                             (true),
      m_isACopy                                 (false),
      m_completionStatus                        (WAVE_MESSAGE_ERROR),
      m_waveClientOriginatingLocationId         (0),
      m_waveNativeClientId                      (0),
      m_waveUserClientId                        (0),
      m_dropReplyAcrossLocations                (false),
      m_isConfigurationChanged                  (false),
      m_isConfigurationFlagSetByUser            (false),
      m_nestedSql                               (""),
      m_transactionCounter                      (0),
      m_surrogatingForLocationId                (0),
      m_needSurrogateSupportFlag                (false),
      m_isMessageBeingSurrogatedFlag            (false),
      m_isMessageSupportedWhenServiceIsPaused   (false),
      m_partitionLocationIdForPropagation       (0),
      m_isPartitionContextPropagated            (false),
      m_isPartitionNameSetByUser                (false),
      m_isConfigurationTimeChanged              (false),
      m_isAConfigurationIntent                  (false),
      m_isConfigurationIntentStored             (false),
      m_isALastConfigReplay                     (false),
      m_timeOutInMilliSeconds                   (600000),
      m_disconnectFromNodeAfterReply            (false),
      m_removeNodeFromKnownLocationAfterReply   (false),
      m_sendForOneWayConnection                 (false)
{
    setIsPreparedForSerialization (false);

    if (NULL == pMessageCreationMutex)
    {
        pMessageCreationMutex = new WaveMutex ();

        waveAssert (NULL != pMessageCreationMutex, __FILE__, __LINE__);
    }

    pMessageCreationMutex->lock ();
    s_numberOfMessagesInTheSystemSoFar++;
    m_waveClientMessageId = m_originalMessageId = m_messageIdAtOriginatingLocation = m_messageId = s_numberOfMessagesInTheSystemSoFar;
    pMessageCreationMutex->unlock ();

    m_type     = WAVE_MESSAGE_TYPE_REQUEST;
    m_priority = WAVE_MESSAGE_PRIORITY_NORMAL;

    MessageTracker::addToMessageTracker (this);

    m_waveMessageCreatorThreadId = WaveThread::getSelf ();
}

WaveMessage::WaveMessage (const WaveMessage &waveMessage)
{
    trace (TRACE_LEVEL_FATAL, "WaveMessage::WaveMessage : Copy Constructing a WaveMessage does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);
}

WaveMessage::~WaveMessage ()
{
    removeAllBuffers ();

    MessageTracker::deleteFromMessageTracker (this);

    pMessageCreationMutex->lock ();

    s_numberOfMessagesDeletedInTheSystemSoFar++;

    if (0 == (s_numberOfMessagesDeletedInTheSystemSoFar % 10000))
    {
        MemoryUtils::releaseUnusedMemoryToSystem ();
    }

    pMessageCreationMutex->unlock ();
}

WaveMessage &WaveMessage::operator = (const WaveMessage &waveMessage)
{
    trace (TRACE_LEVEL_FATAL, "WaveMessage::operator = : Assigning to a WaveMessage does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);

    return (*this);
}

WaveMessageType WaveMessage::getType () const
{
    return (static_cast<WaveMessageType> (m_type));
}

void WaveMessage::setType (WaveMessageType type)
{
    m_type = type;
}

WaveMessagePriority WaveMessage::getPriority () const
{
    return (static_cast<WaveMessagePriority> (m_priority));
}

void WaveMessage::setPriority (WaveMessagePriority priority)
{
    m_priority = priority;
}

WaveServiceId WaveMessage::getServiceCode () const
{
    return (m_serviceCode);
}

void WaveMessage::setServiceCode (const WaveServiceId &serviceCode)
{
    m_serviceCode = serviceCode;
}

UI32 WaveMessage::getOperationCode () const
{
    return (m_operationCode);
}

WaveServiceId WaveMessage::getSenderServiceCode () const
{
    return (m_senderServiceCode);
}

UI32 WaveMessage::getMessageId () const
{
    return (m_messageId);
}

UI32 WaveMessage::getMessageIdAtOriginatingLocation () const
{
    return (m_messageIdAtOriginatingLocation);
}

bool WaveMessage::getIsOneWayMessage () const
{
    return (m_isOneWayMessage);
}

void WaveMessage::setIsOneWayMessage (bool isOneWayMessage)
{
    m_isOneWayMessage = isOneWayMessage;
}

bool WaveMessage::getIsSynchronousMessage () const
{
    return (m_isSynchronousMessage);
}

void WaveMessage::setIsSynchronousMessage (bool isSynchronousMessage)
{
    m_isSynchronousMessage = isSynchronousMessage;
}

ResourceId WaveMessage::getCompletionStatus () const
{
    return (m_completionStatus);
}

WaveMutex *WaveMessage::getPSynchronizingMutex () const
{
    return (m_pSynchronizingMutex);
}

void WaveMessage::setPSynchronizingMutex (WaveMutex *pSynchronizingMutex)
{
    m_pSynchronizingMutex = pSynchronizingMutex;
}

void WaveMessage::setCompletionStatus (const ResourceId completionStatus)
{
    m_completionStatus = completionStatus;
}

WaveCondition *WaveMessage::getPSynchronizingCondition () const
{
    return (m_pSynchronizingCondition);
}

void WaveMessage::setPSynchronizingCondition (WaveCondition *pWaveCondition)
{
    m_pSynchronizingCondition = pWaveCondition;
}

LocationId WaveMessage::getSenderLocationId () const
{
    return (m_senderLocationId);
}

void WaveMessage::setSenderLocationId (const LocationId &locationId)
{
    m_senderLocationId = locationId;
}

LocationId WaveMessage::getReceiverLocationId () const
{
    return (m_receiverLocationId);
}

bool WaveMessage::getIsLastReply () const
{
    return (m_isLastReply);
}

void WaveMessage::setIsLastReply (bool isLastReply)
{
    m_isLastReply = isLastReply;
}

WaveMessageStatus WaveMessage::addBuffer (UI32 tag, UI32 size, const void *pBuffer, bool bufferWillBeOwnedByMessage)
{
    UI32  tempSize;
    void *pTempBuffer = NULL;

    if (NULL == pBuffer)
    {
        cout << "WaveMessage::addBuffer : Cannot add NULL buffer to a WaveMessage." << endl;
        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR_ADDING_NULL_BUFFER);
    }

    pTempBuffer = findBuffer (tag, tempSize);

    if (NULL != pTempBuffer)
    {
        cout << "WaveMessage::addBuffer : A buffer already exists with the tag (" << tag << ")." << endl;
        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR_BUFFER_WITH_TAG_EXISTS);
    }
    else
    {
        WaveMessageBuffer *pWaveMessageBuffer = new WaveMessageBuffer (size, pBuffer, bufferWillBeOwnedByMessage);

        m_buffers[tag] = pWaveMessageBuffer;
        return (WAVE_MESSAGE_SUCCESS);
    }
}

void *WaveMessage::findBuffer (UI32 tag, UI32 &size) const
{
    map<UI32, WaveMessageBuffer *>::const_iterator limitingElement = m_buffers.end ();
    map<UI32, WaveMessageBuffer *>::const_iterator element         = m_buffers.find (tag);

    if (limitingElement != element)
    {
        WaveMessageBuffer *pWaveMessageBuffer = element->second;

        size = pWaveMessageBuffer->getSize ();

        return (pWaveMessageBuffer->getPBuffer ());
    }
    else
    {
        size = 0;

        return (NULL);
    }
}

void *WaveMessage::transferBufferToUser (UI32 tag, UI32 &size)
{
    map<UI32, WaveMessageBuffer *>::iterator limitingElement = m_buffers.end ();
    map<UI32, WaveMessageBuffer *>::iterator element         = m_buffers.find (tag);

    if (limitingElement != element)
    {
        WaveMessageBuffer *pWaveMessageBuffer = element->second;
        void             *pTempBuffer       = pWaveMessageBuffer->getPBuffer ();

        m_buffers.erase (element);
        size = pWaveMessageBuffer->getSize ();
        pWaveMessageBuffer->invalidateBuffer ();
        delete pWaveMessageBuffer;

        return (pTempBuffer);
    }
    else
    {
        size = 0;

        return (NULL);
    }
}

WaveMessageStatus WaveMessage::removeBuffer (UI32 tag)
{
    UI32  tempSize;
    void *pTempBuffer = NULL;

    pTempBuffer = findBuffer (tag, tempSize);

    if (NULL == pTempBuffer)
    {
        cout << "WaveMessage::addBuffer : A buffer does not exist with the tag (" << tag << ")." << endl;
        waveAssert (false, __FILE__, __LINE__);

        return (WAVE_MESSAGE_ERROR_BUFFER_WITH_TAG_DOES_NOT_EXIST);
    }
    else
    {
        map<UI32, WaveMessageBuffer *>::iterator element = m_buffers.find (tag);

        WaveMessageBuffer *pWaveMessageBuffer = element->second;
        m_buffers.erase (element);
        delete pWaveMessageBuffer;

        return (WAVE_MESSAGE_SUCCESS);
    }
}

void WaveMessage::setupAttributesForSerializationInAttributeOrderFormat ()
{
    addAttributeNameForOrderToNameMapping ("waveMessageType");
    addAttributeNameForOrderToNameMapping ("messagePriority");
    addAttributeNameForOrderToNameMapping ("messageIdAtOriginatingLocation");
    addAttributeNameForOrderToNameMapping ("serviceId");
    addAttributeNameForOrderToNameMapping ("operationCode");
    addAttributeNameForOrderToNameMapping ("waveClientMessageId");
    addAttributeNameForOrderToNameMapping ("senderLocationId");
    addAttributeNameForOrderToNameMapping ("receiverLocationId");
    addAttributeNameForOrderToNameMapping ("isOneWayMessage");
    addAttributeNameForOrderToNameMapping ("isACopy");
    addAttributeNameForOrderToNameMapping ("originalMessageId");
    addAttributeNameForOrderToNameMapping ("isLastReply");
    addAttributeNameForOrderToNameMapping ("completionStatus");
    addAttributeNameForOrderToNameMapping ("waveClientOriginatingLocationId");
    addAttributeNameForOrderToNameMapping ("waveNativeClientId");
    addAttributeNameForOrderToNameMapping ("waveUserClientId");
    addAttributeNameForOrderToNameMapping ("messageString");
    addAttributeNameForOrderToNameMapping ("isConfigurationChanged");
    addAttributeNameForOrderToNameMapping ("isConfigurationFlagSetByUser");
    addAttributeNameForOrderToNameMapping ("nestedSql");
    addAttributeNameForOrderToNameMapping ("transactionCounter");
    addAttributeNameForOrderToNameMapping ("surrogatingForLocationId");
    addAttributeNameForOrderToNameMapping ("needSurrogateSupportFlag");
    addAttributeNameForOrderToNameMapping ("isMessageBeingSurrogatedFlag");
    addAttributeNameForOrderToNameMapping ("locationsForStatusPropagation");
    addAttributeNameForOrderToNameMapping ("completionStatusForStatusPropagation");
    addAttributeNameForOrderToNameMapping ("localizedCompletionStatusForStatusPropagation");
    addAttributeNameForOrderToNameMapping ("isMessageSupportedWhenServiceIsPaused");
    addAttributeNameForOrderToNameMapping ("xPathStringsVectorForTimestampUpdate");
}

void WaveMessage::setupAttributesForSerialization ()
{
    // Currently there is nothing that happens in the SerializableObject::setupAttributesForSerialization ()
    // method.  So we do not need to call it.  If there is somethign at a later time, the following line
    // must be uncommented.

    //SerializableObject::setupAttributesForSerialization ();

    // WARNING !!! WARNING !!! WARNING

    // The order below must not change.  If it is changed, without making corresponding changes to remote messaging
    // related methods, remote messaing will be utterly broken.  The methods that depend on the order are
    //     getType
    //     getMessageIdAtOriginatingLocation
    //     createAndLoadFromSerializedData2

    addSerializableAttribute (new AttributeWaveMessageType      (&m_type,                                           "waveMessageType"));
    addSerializableAttribute (new AttributeWaveMessagePriority  (&m_priority,                                       "messagePriority"));
    addSerializableAttribute (new AttributeUI32                 (&m_messageIdAtOriginatingLocation,                 "messageIdAtOriginatingLocation"));
    addSerializableAttribute (new AttributeWaveServiceId       (&m_serviceCode,                                    "serviceId"));
    addSerializableAttribute (new AttributeUI32                 (&m_operationCode,                                  "operationCode"));
    addSerializableAttribute (new AttributeUI32                 (&m_waveClientMessageId,                            "waveClientMessageId"));
    addSerializableAttribute (new AttributeLocationId           (&m_senderLocationId,                               "senderLocationId"));
    addSerializableAttribute (new AttributeLocationId           (&m_receiverLocationId,                             "receiverLocationId"));
    addSerializableAttribute (new AttributeBool                 (&m_isOneWayMessage,                                "isOneWayMessage"));
    addSerializableAttribute (new AttributeBool                 (&m_isACopy,                                        "isACopy"));
    addSerializableAttribute (new AttributeUI32                 (&m_originalMessageId,                              "originalMessageId"));
    addSerializableAttribute (new AttributeBool                 (&m_isLastReply,                                    "isLastReply"));
    addSerializableAttribute (new AttributeResourceId           (&m_completionStatus,                               "completionStatus"));
    addSerializableAttribute (new AttributeLocationId           (&m_waveClientOriginatingLocationId,                "waveClientOriginatingLocationId"));
    addSerializableAttribute (new AttributeUI32                 (&m_waveNativeClientId,                             "waveNativeClientId"));
    addSerializableAttribute (new AttributeUI32                 (&m_waveUserClientId,                               "waveUserClientId"));
    addSerializableAttribute (new AttributeString               (&m_messageString,                                  "messageString"));
    addSerializableAttribute (new AttributeBool                 (&m_isConfigurationChanged,                         "isConfigurationChanged"));
    addSerializableAttribute (new AttributeBool                 (&m_isConfigurationFlagSetByUser,                   "isConfigurationFlagSetByUser"));
    addSerializableAttribute (new AttributeString               (&m_nestedSql,                                      "nestedSql"));
    addSerializableAttribute (new AttributeUI32                 (&m_transactionCounter,                             "transactionCounter"));
    addSerializableAttribute (new AttributeLocationId           (&m_surrogatingForLocationId,                       "surrogatingForLocationId"));
    addSerializableAttribute (new AttributeBool                 (&m_needSurrogateSupportFlag,                       "needSurrogateSupportFlag"));
    addSerializableAttribute (new AttributeBool                 (&m_isMessageBeingSurrogatedFlag,                   "isMessageBeingSurrogatedFlag"));
    addSerializableAttribute (new AttributeLocationIdVector     (&m_locationsForStatusPropagation,                  "locationsForStatusPropagation"));
    addSerializableAttribute (new AttributeResourceIdVector     (&m_completionStatusForStatusPropagation,           "completionStatusForStatusPropagation"));
    addSerializableAttribute (new AttributeStringVector         (&m_localizedCompletionStatusForStatusPropagation,  "localizedCompletionStatusForStatusPropagation"));
    addSerializableAttribute (new AttributeBool                 (&m_isMessageSupportedWhenServiceIsPaused,          "isMessageSupportedWhenServiceIsPaused"));
    addSerializableAttribute (new AttributeStringVector         (&m_xPathStringsVectorForTimestampUpdate,           "xPathStringsVectorForTimestampUpdate"));

    // Multi-Partition
    addSerializableAttribute (new AttributeString               (&m_partitionName,                                  "wavePartitionName"));
    addSerializableAttribute (new AttributeLocationId           (&m_partitionLocationIdForPropagation,              "partitionLocationIdForPropagation"));
    addSerializableAttribute (new AttributeBool                 (&m_isPartitionContextPropagated,                   "isPartitionContextPropagated"));

    addSerializableAttribute (new AttributeBool                 (&m_isConfigurationTimeChanged,                     "isConfigurationTimeChanged"));

    addSerializableAttribute (new AttributeBool                 (&m_isALastConfigReplay,                            "isALastConfigReplay"));
}

void WaveMessage::copyFromRemoteResponse (WaveMessage *pRemoteWaveMessageResponse)
{
#if 0
//    string serializedData;

//    pRemoteWaveMessageResponse->serialize (serializedData);

//    loadFromSerializedData (serializedData);
#else
    // Locd the values from the remote response.

    loadFromSerializableObject (pRemoteWaveMessageResponse);
#endif
    // Now handle the buffers.
    // Remove all the exisiting buffers and transfer the buffers from the remote messge response to this message.

    removeAllBuffers ();
    pRemoteWaveMessageResponse->transferAllBuffers (this);
}

UI32 WaveMessage::getNumberOfBuffers () const
{
    return (m_buffers.size ());
}

void WaveMessage::getBufferTags (vector<UI32> &bufferTagsVector) const
{
    map<UI32, WaveMessageBuffer *>::const_iterator limitingElement = m_buffers.end ();
    map<UI32, WaveMessageBuffer *>::const_iterator element         = m_buffers.begin ();

    while (element != limitingElement)
    {
        bufferTagsVector.push_back (element->first);

        element++;
    }
}

void WaveMessage::removeAllBuffers ()
{
    map<UI32, WaveMessageBuffer *>::iterator  element           = m_buffers.begin () ;
    map<UI32, WaveMessageBuffer *>::iterator  limitingElement   = m_buffers.end ();
    WaveMessageBuffer                        *pWaveMessageBuffer = NULL;

    while (element != limitingElement)
    {
        pWaveMessageBuffer = element->second;
        delete pWaveMessageBuffer;

        element++;
    }

    m_buffers.clear ();
}

void WaveMessage::transferAllBuffers (WaveMessage *pWaveMessage)
{
    if (this == pWaveMessage)
    {
        waveAssert (false, __FILE__, __LINE__);
        return;
    }

    map<UI32, WaveMessageBuffer *>::iterator  element           = m_buffers.begin () ;
    map<UI32, WaveMessageBuffer *>::iterator  limitingElement   = m_buffers.end ();
    UI32                                     bufferTag;
    WaveMessageBuffer                        *pWaveMessageBuffer = NULL;

    while (element != limitingElement)
    {
        bufferTag         = element->first;
        pWaveMessageBuffer = element->second;

        pWaveMessage->addBuffer (bufferTag, pWaveMessageBuffer->getSize (), pWaveMessageBuffer->getPBuffer (), true);

        pWaveMessageBuffer->setPBuffer (NULL);
        delete pWaveMessageBuffer;

        element++;
    }

    m_buffers.clear ();
}

void WaveMessage::setDropReplyAcrossLocations (const bool &dropReplyAcrossLocations)
{
    m_dropReplyAcrossLocations = dropReplyAcrossLocations;
}

bool WaveMessage::getDropReplyAcrossLocations () const
{
    return (m_dropReplyAcrossLocations);
}

WaveMessageType WaveMessage::getType (const string &serializedData, const UI8 serializationType)  //const string& messageVersion)
{
    // We know the SerializableObjectAttributeId for Message Type is always 1. (This cannot be changed from 1)
    // So the corresponding attribute in the serialized XML will be tagged with A1.  So look for the data
    // tagged between <A1> and </A1>

    SI32 index1            = 0;
    SI32 index2            = 0;
    string attributeTag    = "";

    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        attributeTag = string ("1");
    }
    else
    {
        attributeTag = string ("waveMessageType");
    }
    UI32 startIndexOffset = attributeTag.size () + strlen ("<A>");

    index1    = serializedData.find (string ("<A") + attributeTag + string (">"));
    index2    = serializedData.find (string ("</A") + attributeTag + string (">"));

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);
    //UI32   sot       = strtoul (sotString.c_str (), NULL, 10);
    //
    //return ((WaveMessageType) sot);

    WaveMessageType waveMessageType = WAVE_MESSAGE_TYPE_REQUEST;

    AttributeResourceId attributeResourceId (waveMessageType);
    attributeResourceId.fromString (sotString);

    WaveMessageType *pWaveMessageType = (WaveMessageType *) attributeResourceId.getPData ();

    return (*pWaveMessageType);
}

UI32 WaveMessage::getMessageIdAtOriginatingLocation (const string &serializedData, const UI8 serializationType)
{
    // We now the SerializableObjectAttributeId for Message Id at Originating Location is always 3. (This cannot be changed from 3)
    // So the corresponding attribute in the serialized XML will be tagged with A3.  So look for the data
    // tagged between <A3> and </A3>

    string  attributeTag        = "";
    SI32    index1              = 0;
    SI32    index2              = 0;

    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        attributeTag = string ("3");
    }
    else
    {
        attributeTag = string ("messageIdAtOriginatingLocation");
    }
    UI32 startIndexOffset = attributeTag.size () + strlen ("<A>");

    index1    = serializedData.find (string ("<A") + attributeTag + string (">"));
    index2    = serializedData.find (string ("</A") + attributeTag + string (">"));

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);
    UI32   sot       = strtoul (sotString.c_str (), NULL, 10);

    return (sot);
}

UI32 WaveMessage::getWaveClientMessageId (const string &serializedData, const UI8 serializationType)
{
    // We now the SerializableObjectAttributeId for Message Id at WaveClient is always 6. (This cannot be changed from 6)
    // So the corresponding attribute in the serialized XML will be tagged with A6.  So look for the data
    // tagged between <A6> and </A6>

    string  attributeTag        = "";
    SI32    index1              = 0;
    SI32    index2              = 0;


    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        attributeTag = string ("6");
    }
    else
    {
        attributeTag = string ("waveClientMessageId");
    }
    UI32 startIndexOffset = attributeTag.size () + strlen ("<A>");

    index1    = serializedData.find (string ("<A") + attributeTag + string (">"));
    index2    = serializedData.find (string ("</A") + attributeTag + string (">"));

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);
    UI32   sot       = strtoul (sotString.c_str (), NULL, 10);

    return (sot);
}

UI32 WaveMessage::getMessageCompletionStatus (const string &serializedData, const UI8 serializationType)
{
// Now Completion status of a message is at position 13 (This can not be changed form 13 now).
// So the corresponding attribute in the serialized XML will be tagged with A13. So look for the data
// tagged between <A13> and </A13>

    UI32    startIndexOffset    = 0;
    SI32    index1              = 0;
    SI32    index2              = 0;
    string  attributeTag        = "";

    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        attributeTag = string ("13");
    }
    else
    {
        attributeTag = string ("completionStatus");
    }
    startIndexOffset = attributeTag.size () + strlen ("<A>");

    index1    = serializedData.find (string ("<A") + attributeTag + string (">"));
    index2    = serializedData.find (string ("</A") + attributeTag + string (">"));

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);

    ResourceId  resourceId = WAVE_MESSAGE_SUCCESS;

    AttributeResourceId attributeResourceId (resourceId);
    attributeResourceId.fromString (sotString);

    ResourceId *pResourceId = (ResourceId *) attributeResourceId.getPData ();

    return (*pResourceId);
}

bool WaveMessage::getIsLastReply (const string &serializedData, const UI8 serializationType)
{
    SI32 index1            = 0;
    SI32 index2            = 0;
    string attributeTag    = "";

    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        attributeTag = string ("12");
    }
    else
    {
        attributeTag = string ("isLastReply");
    }
    UI32 startIndexOffset = attributeTag.size () + strlen ("<A>");

    index1    = serializedData.find (string ("<A") + attributeTag + string (">"));
    index2    = serializedData.find (string ("</A") + attributeTag + string (">"));

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);

    if (0 == sotString.compare("true"))
    {
        return(true);
    }

    return (false);
}

WaveMessage *WaveMessage::createAndLoadFromSerializedData2 (const string &serializedData, const WaveServiceId &assumedServiceCode, const UI8 serializationType)
{
    // A4 attribute corresponds to the service code and A5 attribute corresponds to the operation code.
    // We strictly depend on these numbers.  If the order in the setupAttributesForSerialization in WaveMessage
    // changes then these should be adjusted accordingly.

    string  ServiceCodeAttributeTag     = "";
    string  OperationCodeAttributeTag   = "";
    SI32    startIndexForServiceCode    = 0;
    SI32    endIndexForServiceCode      = 0;
    SI32    startIndexForOperationCode  = 0;
    SI32    endIndexForOperationCode    = 0;

    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        ServiceCodeAttributeTag   = string ("4");
        OperationCodeAttributeTag = string ("5");
    }
    else
    {
        ServiceCodeAttributeTag   = string ("serviceId");
        OperationCodeAttributeTag = string ("operationCode");
    }

    startIndexForServiceCode    = serializedData.find (string ("<A") + ServiceCodeAttributeTag + string (">"));
    endIndexForServiceCode      = serializedData.find (string ("</A") + ServiceCodeAttributeTag + string (">"));
    UI32 startIndexOffsetForServiceCode = ServiceCodeAttributeTag.size () + strlen ("<A>");

    startIndexForOperationCode  = serializedData.find (string ("<A") + OperationCodeAttributeTag + string (">"));
    endIndexForOperationCode    = serializedData.find (string ("</A") + OperationCodeAttributeTag + string (">"));
    UI32 startIndexOffsetForOperationCode = OperationCodeAttributeTag.size () + strlen ("<A>");

    string serviceCodeString    = serializedData.substr (startIndexForServiceCode + startIndexOffsetForServiceCode, endIndexForServiceCode - startIndexForServiceCode - startIndexOffsetForServiceCode);
    UI32   serviceId            = strtoul (serviceCodeString.c_str (), NULL, 10);
    string operationCodeString  = serializedData.substr (startIndexForOperationCode + startIndexOffsetForOperationCode, endIndexForOperationCode - startIndexForOperationCode - startIndexOffsetForOperationCode);
    UI32   operationCode        = strtoul (operationCodeString.c_str (), NULL, 10);

    if (0 != assumedServiceCode)
    {
        serviceId = assumedServiceCode;
    }

    WaveMessage *pWaveMessage = WaveMessageFactory::getMessageInstance (serviceId, operationCode);

    waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

    if (NULL == pWaveMessage)
    {
        return (NULL);
    }

    // Prepare for serialization and load the attributes from the serialized data.

    pWaveMessage->prepareForSerialization ();
    pWaveMessage->loadFromSerializedData2 (serializedData, serializationType);

    return (pWaveMessage);
}

WaveMessage *WaveMessage::createAndLoadFromSerializedData2 (const UI8 *pData, const UI32 dataSize)
{
    waveAssert (NULL != pData, __FILE__, __LINE__);
    waveAssert (0 != dataSize, __FILE__, __LINE__);

    if ((NULL == pData) || (0 == dataSize))
    {
        return (NULL);
    }

    char   *pTempString     = new char[dataSize + 1];
    string  serializedData;

    waveAssert (NULL != pTempString, __FILE__, __LINE__);

    if (NULL == pTempString)
    {
        return (NULL);
    }

    strncpy (pTempString, (const char *) pData, dataSize);
    pTempString[dataSize] = '\0';
    serializedData = pTempString;
    delete[] pTempString;

    return (createAndLoadFromSerializedData2 (serializedData));
}

void WaveMessage::setWaveClientOriginatingLocationId (const LocationId &waveClientOriginatingLocationId)
{
    m_waveClientOriginatingLocationId = waveClientOriginatingLocationId;
}

LocationId WaveMessage::getWaveClientOriginatingLocationId () const
{
    return (m_waveClientOriginatingLocationId);
}

void WaveMessage::setWaveNativeClientId (const UI32 &waveNativeClientId)
{
    m_waveNativeClientId = waveNativeClientId;
}

UI32 WaveMessage::getWaveNativeClientId () const
{
    return (m_waveNativeClientId);
}

void WaveMessage::setWaveUserClientId (const UI32 &waveUserClientId)
{
    m_waveUserClientId = waveUserClientId;
}

UI32 WaveMessage::getWaveUserClientId () const
{
    return (m_waveUserClientId);
}

WaveClientSessionContext WaveMessage::getWaveClientSessionContext () const
{
    WaveClientSessionContext waveClientSessionContext;

    waveClientSessionContext.setWaveClientOriginatingLocationId (m_waveClientOriginatingLocationId);
    waveClientSessionContext.setWaveNativeClientId              (m_waveNativeClientId);
    waveClientSessionContext.setWaveUserClientId                (m_waveUserClientId);

    return (waveClientSessionContext);
}

void WaveMessage::setMessageIdAtOriginatingLocation  (const UI32 &messageIdAtOriginatingLocation)
{
    m_messageIdAtOriginatingLocation = messageIdAtOriginatingLocation;
}

UI32 WaveMessage::getOriginalMessageId () const
{
    return (m_originalMessageId);
}

void WaveMessage::setOriginalMessageId (const UI32 &originalMessageId)
{
    m_originalMessageId = originalMessageId;
}

void WaveMessage::copyBuffersFrom (const WaveMessage &waveMessage)
{
    vector<UI32> bufferTagsVector;
    UI32         numberOfBuffers   = 0;
    UI32         i                 = 0;

    waveMessage.getBufferTags (bufferTagsVector);

    numberOfBuffers = bufferTagsVector.size ();

    for (i = 0; i < numberOfBuffers; i++)
    {
        void              *pBuffer    = NULL;
        UI32               bufferSize = 0;
        WaveMessageStatus  status     = WAVE_MESSAGE_ERROR;

        pBuffer = waveMessage.findBuffer (bufferTagsVector[i], bufferSize);

        waveAssert (NULL != pBuffer, __FILE__, __LINE__);
        waveAssert (0 != bufferSize, __FILE__, __LINE__);

        status = addBuffer (bufferTagsVector[i], bufferSize, pBuffer, false);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveMessage::copyBuffersFrom : Copying a Buffer Failed.  Status : " + FrameworkToolKit::localize (status));
            waveAssert (false, __FILE__, __LINE__);
        }
    }
}

WaveMessage *WaveMessage::clone ()
{
    WaveMessage *pClonedWaveMessage            = WaveMessageFactory::getMessageInstance (m_serviceCode, m_operationCode);
    string        serializedData;
    UI32          messageIdAtOriginatingLocation = 0;
    UI32          originalMessageId              = 0;
    UI32          waveClientMessageId            = 0;

    waveAssert (NULL != pClonedWaveMessage, __FILE__, __LINE__);

    if (NULL == pClonedWaveMessage)
    {
        return (NULL);
    }

    // Prepare for serialization on this message.

    prepareForSerialization ();

    // Prepare for serialization and load the attributes from this message into the cloned message.

    messageIdAtOriginatingLocation = pClonedWaveMessage->getMessageIdAtOriginatingLocation ();
    originalMessageId              = pClonedWaveMessage->getOriginalMessageId ();
    waveClientMessageId            = pClonedWaveMessage->getWaveClientMessageId ();

    pClonedWaveMessage->prepareForSerialization ();
    pClonedWaveMessage->loadFromSerializableObject (this);

    pClonedWaveMessage->setMessageIdAtOriginatingLocation (messageIdAtOriginatingLocation);
    pClonedWaveMessage->setOriginalMessageId              (originalMessageId);
    pClonedWaveMessage->setWaveClientMessageId            (waveClientMessageId);

    pClonedWaveMessage->m_isACopy                         = true;


    pClonedWaveMessage->copyBuffersFrom (*this);

    return (pClonedWaveMessage);
}

void WaveMessage::setMessageId (const UI32 &messageId)
{
    m_messageId = messageId;
}


void WaveMessage::setSenderServiceCode(const WaveNs::WaveServiceId& senderServiceCode)
{
    m_senderServiceCode = senderServiceCode;
}

string WaveMessage::getMessageString()
{
    return m_messageString;
}

void WaveMessage::setMessageString(string messageString)
{
    m_messageString = messageString;
}

bool WaveMessage::getIsConfigurationChanged () const
{
    return (m_isConfigurationChanged);
}

void WaveMessage::setIsConfigurationChanged (const bool &isConfigurationChanged)
{
    m_isConfigurationChanged = isConfigurationChanged;
    m_isConfigurationFlagSetByUser = true;
}

bool WaveMessage::getIsConfigurationTimeChanged () const
{
    return (m_isConfigurationTimeChanged);
}

void WaveMessage::setIsConfigurationTimeChanged (const bool &isConfigurationTimeChanged)
{
    m_isConfigurationTimeChanged = isConfigurationTimeChanged;
}

bool WaveMessage::getIsConfigurationFlagSetByUser () const
{
    return (m_isConfigurationFlagSetByUser);
}

void WaveMessage::setWaveClientMessageId (const UI32 &waveClientMessageId)
{
    m_waveClientMessageId = waveClientMessageId;
}

UI32 WaveMessage::getWaveClientMessageId () const
{
    return (m_waveClientMessageId);
}

UI32 WaveMessage::getTransactionCounter () const
{
    return m_transactionCounter;
}

void WaveMessage::setTransactionCounter (const UI32 transactionCounter)
{
    m_transactionCounter = transactionCounter;
}

string WaveMessage::getNestedSql () const
{
    return m_nestedSql;
}

void WaveMessage::setNestedSql (const string &nestedSql)
{
    m_nestedSql = nestedSql;
}

void WaveMessage::appendNestedSql (const string &nestedSql)
{
    m_nestedSql += nestedSql;
}

WaveThreadId  WaveMessage::getWaveMessageCreatorThreadId () const
{
    return (m_waveMessageCreatorThreadId);
}

void WaveMessage::setSurrogatingForLocationId (LocationId disconnectedLocation)
{
    m_surrogatingForLocationId = disconnectedLocation;
}

LocationId WaveMessage::getSurrogatingForLocationId () const
{
    return (m_surrogatingForLocationId);
}

void WaveMessage::setNeedSurrogateSupportFlag (bool needSurrogateSupport)
{
    m_needSurrogateSupportFlag = needSurrogateSupport;
}

bool WaveMessage::getNeedSurrogateSupportFlag () const
{
    return (m_needSurrogateSupportFlag);
}

void WaveMessage::setIsMessageBeingSurrogatedFlag (bool isMessageBeingSurrogated)
{
    m_isMessageBeingSurrogatedFlag = isMessageBeingSurrogated;
}

bool WaveMessage::getIsMessageBeingSurrogatedFlag () const
{
    return (m_isMessageBeingSurrogatedFlag);
}

void WaveMessage::updateForCompletionStatusDuringSurrogacy ()
{
    m_completionStatus = WAVE_MESSAGE_SUCCESS;
}
/**
 * Name:        addStatusPropagation
 * Description: Adds the status resource id and localized status of a different message based on the current location id.
 *              The specific purpose is to facilitate propagating sendToWaveCluster partial success
 *              errors back to WyserConfigurationHandlers where logging these error messages can be handled.
 *
 * @param1:     statusResourceId : Resource id of the message status to be added for propagation
 * @param2:     localizedStatus  : Localized string of the message status to be added for propagation
 *
 * @return:     none
 */
void WaveMessage::addStatusPropagation (ResourceId statusResourceId, const string &localizedStatus)
{
    addStatusPropagation (statusResourceId, localizedStatus, FrameworkToolKit::getThisLocationId ());
}

/**
 * Name:        addStatusPropagation
 * Description: Adds the status resource id and localized status of a different message based on location id.
 *              The specific purpose is to facilitate propagating sendToWaveCluster partial success
 *              errors back to WyserConfigurationHandlers where logging these error messages can be handled.
 *
 * @param1:     statusResourceId : Resource id of the message status to be added for propagation
 * @param2:     localizedStatus  : Localized string of the message status to be added for propagation
 * @param3:     locationId       : Location id of where the message was sent to.
 *
 * @return:     none
 */
void WaveMessage::addStatusPropagation (ResourceId statusResourceId, const string &localizedStatus, LocationId locationId)
{
    //trace (TRACE_LEVEL_DEVEL, "WaveMessage::addStatusPropagation : Entering ...");

    vector<LocationId>::iterator it;
    bool                         locationExists = false;

    for (it = m_locationsForStatusPropagation.begin (); it < m_locationsForStatusPropagation.end (); it++)
    {
        if (*it == locationId)
        {
            locationExists = true;
            break;
        }
    }

    if (true == locationExists)
    {
        trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::addStatusPropagation : Propagated status for location id ") + locationId + " already exists, do not add the propagated status");

        return;
    }

    m_completionStatusForStatusPropagation.push_back (statusResourceId);
    m_localizedCompletionStatusForStatusPropagation.push_back (localizedStatus);
    m_locationsForStatusPropagation.push_back (locationId);

    trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::addStatusPropagation : Resource Id : ") + statusResourceId + ", Localized Status : " + localizedStatus + ", Location : " + locationId);
}

/**
 * Name:        addClusterStatusPropagation
 * Description: Batch adds the status resource id and localized status pulled from the sendToWaveClusterContext.
 *              This allows Partial Success errors to be propagated back to WyserEaGW.
 *
 * @param1:     pWaveSendToClusterContext : pointer to WaveSendToClusterContext
 * @param2:     overAllCompletionStatus : overall completion status for send to wave cluster.
 *
 * @return:     none
 */
void WaveMessage::addClusterStatusPropagation (WaveSendToClusterContext *pWaveSendToClusterContext, ResourceId overAllCompletionStatus)
{
    //trace (TRACE_LEVEL_DEVEL, "WaveMessage::addClusterStatusPropagation : Entering ...");

    bool partialSuccessFlag = pWaveSendToClusterContext->getPartialSuccessFlag ();

    if ((true == partialSuccessFlag) || (WAVE_MESSAGE_ERROR_FAILED_ON_SOME_NODES == overAllCompletionStatus) || (WAVE_MESSAGE_ERROR_FAILED_ON_ALL_NODES == overAllCompletionStatus))
    {
        // Propagate sendToWaveCluster status on this Wave Message for an all error case, partial error case (when partial success is not used), and partial success case.
        // Phase2 Rollback cases are currently not supported.

        vector<LocationId>  locationsSentForPhase1 = pWaveSendToClusterContext->getLocationsToSendToForPhase1 ();

        for (UI32 i = 0; i < static_cast<UI32> (locationsSentForPhase1.size ()); i++)
        {
            WaveMessageStatus sendStatus = pWaveSendToClusterContext->getSendStatusForPhase1 (locationsSentForPhase1[i]);

            if (WAVE_MESSAGE_SUCCESS != sendStatus)
            {
                addStatusPropagation (sendStatus, FrameworkToolKit::localize (sendStatus), locationsSentForPhase1[i]);
            }
            else
            {
                FrameworkStatus frameworkStatus = pWaveSendToClusterContext->getFrameworkStatusForPhase1 (locationsSentForPhase1[i]);

                if (FRAMEWORK_SUCCESS != frameworkStatus)
                {
                    addStatusPropagation (frameworkStatus, FrameworkToolKit::localize (frameworkStatus), locationsSentForPhase1[i]);
                }
                else
                {
                    ResourceId completionStatus = pWaveSendToClusterContext->getCompletionStatusForPhase1 (locationsSentForPhase1[i]);

                    if (WAVE_MESSAGE_SUCCESS != completionStatus)
                    {
                        WaveMessage   *pResultingMessageForPhase1          = pWaveSendToClusterContext->getResultingMessageForPhase1 (locationsSentForPhase1[i]);
                        string          localizedStatus                     = "";
                        bool            locationFound                       = false;
                        ResourceId      status;


                        locationFound = pResultingMessageForPhase1->getStatusPropagationByLocationId (status, localizedStatus, locationsSentForPhase1[i]);

                        if ((true == locationFound) && ("" != localizedStatus))
                        {
                            // Handle the special case where a variable argument list is used in the completion status of the sendToWaveCluster phase 1 message.

                            addStatusPropagation (completionStatus, localizedStatus, locationsSentForPhase1[i]);

                            trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::addClusterStatusPropagation : Propagated localized status with custom attribute(s).  Resource Id : ") + status + ", Localized Status : " + localizedStatus + ", Location Id : " + locationsSentForPhase1[i]);
                        }
                        else
                        {
                            addStatusPropagation (completionStatus, FrameworkToolKit::localize (completionStatus), locationsSentForPhase1[i]);

                            trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::addClusterStatusPropagation : Propagated error status.  Resource Id : ") + completionStatus + ", Localized Status : " + FrameworkToolKit::localize (completionStatus) + ", Location Id : " + locationsSentForPhase1[i]);
                        }
                    }
                    else
                    {
                        // Propagate the WAVE_MESSAGE_SUCCESS case so that successful locations can be grouped later.

                        addStatusPropagation (completionStatus, FrameworkToolKit::localize (completionStatus), locationsSentForPhase1[i]);

                        trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::addClusterStatusPropagation : Propagated success status.  Resource Id : ") + completionStatus + ", Localized Status : " + FrameworkToolKit::localize (completionStatus) + ", Location Id : " + locationsSentForPhase1[i]);
                    }
                }
            }
        }
    }
    else
    {
        // SendToWaveCluster has completely succeeded or completely failed so do nothing
    }
}

/**
 * Name:        getStatusPropagationByLocationId
 * Description: Retrieve the status resource Id and localized status of a different message by location id.
 *              The specific purpose is to facilitate propagating sendToWaveCluster partial success
 *              errors back to WyserConfigurationHandlers where logging these error messages can be handled.
 *
 * @param1:     statusResourceId :  propagated status of a message when corresponding location id is found.
 * @param2:     localizedStatus  :  propagated localized status of a message when corresponding location id is found.
 * @param3:     locationId       :  the location id by which to search for a propagated status resource id and localized status.
 *
 * @return:     true, if propagated status exists and the provided location id was found.  Otherwise false.
 */
bool WaveMessage::getStatusPropagationByLocationId (ResourceId &statusResourceId, string &localizedStatus, LocationId locationId)
{
    //trace (TRACE_LEVEL_DEVEL, "WaveMessage::getStatusPropagationByLocationId : Entering...");

    UI32 numberOfLocations  = m_locationsForStatusPropagation.size ();
    bool isLocationIdFound  = false;
    bool returnStatus       = false;

    trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::getStatusPropagationByLocationId : Number of locations : ") + numberOfLocations);

    if (0 < numberOfLocations)
    {
        for (UI32 i = 0; i < numberOfLocations; i++)
        {
            if (locationId == m_locationsForStatusPropagation[i])
            {
                statusResourceId    = m_completionStatusForStatusPropagation[i];
                localizedStatus     = m_localizedCompletionStatusForStatusPropagation[i];
                isLocationIdFound   = true;
                returnStatus        = true;

                trace (TRACE_LEVEL_DEBUG, string ("WaveMessage::getStatusPropagationByLocationId : Propagated status found : Resource Id : ") + m_completionStatusForStatusPropagation[i] + ", Localized Status : " + m_localizedCompletionStatusForStatusPropagation[i] + ", Location Id : " + locationId);

                break;
            }
        }

        if (false == isLocationIdFound)
        {
            trace (TRACE_LEVEL_ERROR, string ("WaveMessage::getStatusPropagationByLocationId : Propagated status for location id : ") + locationId + " could not be found.");

            returnStatus = false;
        }
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, "WaveMessage::getStatusPropagationByLocationId : Propagated status is currently empty.  Possibly no status has been propagated.");

        returnStatus = false;
    }

    return (returnStatus);
}

/**
 * Name:        getAllStatusPropagation
 * Description: Bulk get of all three vectors where the index number is assumed to be the key
 *              that contains correlated data across the three vectors.
 *              The specific purpose is to facilitate propagating sendToWaveCluster partial success
 *              errors back to WyserConfigurationHandlers where logging these error messages can be handled.
 *
 * @param1:     statusResourceIds : vector of status resource ids where the same index is correlated data from the other two vectors.
 * @param2:     localizedStatus   : vector of localized status where the same index is correlated data from the other two vectors.
 * @param3:     locationIds       : vector of location ids where the same index is correlated data from the other two vectors.
 *
 * @return:     true, if propagated status exists.  Otherwise false.
 */
bool WaveMessage::getAllStatusPropagation (vector<ResourceId> &statusResourceIds, vector<string> &localizedStatus, vector<LocationId> &locationIds)
{
    UI32 numberOfCompletionStatus   = m_completionStatusForStatusPropagation.size ();
    bool returnStatus               = false;

    if (0 < numberOfCompletionStatus)
    {
        statusResourceIds   = m_completionStatusForStatusPropagation;
        localizedStatus     = m_localizedCompletionStatusForStatusPropagation;
        locationIds         = m_locationsForStatusPropagation;

        returnStatus = true;
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, "WaveMessage::getAllStatusPropagation : Propagated status is currently empty.  There is no valid propagated status to return.");

        returnStatus = false;
    }

    return (returnStatus);
}

/**
 * Name:        clearStatusPropagation
 * Description: Bulk clear of all three vectors used for status propagation.
 *
 * @return:     none
 */
void WaveMessage::clearStatusPropagation ()
{
    m_locationsForStatusPropagation.clear ();
    m_completionStatusForStatusPropagation.clear ();
    m_localizedCompletionStatusForStatusPropagation.clear ();
}

/**
 * Name:        getNumberOfStatusPropagation
 * Description: Check to see if any message status has been added for propagation
 *
 * @return:     Size of the status propagation vectors
 */
UI32 WaveMessage::getNumberOfStatusPropagation () const
{
    UI32 numberOfCompletionStatus = m_completionStatusForStatusPropagation.size ();
    UI32 numberOfLocalizedCompletionStatus = m_localizedCompletionStatusForStatusPropagation.size ();
    UI32 numberOfLocations = m_locationsForStatusPropagation.size ();

    if ((numberOfCompletionStatus != numberOfLocalizedCompletionStatus) || (numberOfCompletionStatus != numberOfLocations))
    {
        trace (TRACE_LEVEL_FATAL, string ("WaveMessage::getNumberOfStatusPropagation : There is a mismatch between the size of the three status propagation vectors which should never happen.  Completion Status Vector Size: ") + numberOfCompletionStatus + ", Localized Completion Status Vector Size: " + numberOfLocalizedCompletionStatus + ", Locations Vector: " + numberOfLocations);

        waveAssert (false, __FILE__, __LINE__);
    }

    return (numberOfCompletionStatus);
}

bool WaveMessage::getIsMessageSupportedWhenServiceIsPaused () const
{
    return (m_isMessageSupportedWhenServiceIsPaused);
}

void WaveMessage::setIsMessageSupportedWhenServiceIsPaused (bool isMessageSupportedWhenServiceIsPaused)
{
    m_isMessageSupportedWhenServiceIsPaused = isMessageSupportedWhenServiceIsPaused;
}

void WaveMessage::addXPathStringsVectorForTimestampUpdate (const vector<string> &xPathStringsVectorForTimestampUpdate)
{
    m_xPathStringsVectorForTimestampUpdate.insert (m_xPathStringsVectorForTimestampUpdate.end (), xPathStringsVectorForTimestampUpdate.begin (), xPathStringsVectorForTimestampUpdate.end ());
}

void WaveMessage::addXPathStringForTimestampUpdate (const string &xPathString)
{
    m_xPathStringsVectorForTimestampUpdate.push_back (xPathString);
}

vector<string> WaveMessage::getXPathStringsVectorForTimestampUpdate () const
{
    return m_xPathStringsVectorForTimestampUpdate;
}

// Multi Partition.
void WaveMessage::setPartitionName (const string &partitionName)
{
    m_isPartitionNameSetByUser = true;

    m_partitionName = partitionName;
}

string WaveMessage::getPartitionName (void) const
{
    return m_partitionName;
}

void WaveMessage::setPartitionLocationIdForPropagation (const LocationId &partitionLocationIdForPropagation)
{
    m_partitionLocationIdForPropagation = partitionLocationIdForPropagation;
}

LocationId WaveMessage::getPartitionLocationIdForPropagation () const
{
    return m_partitionLocationIdForPropagation;
}

void WaveMessage::setIsPartitionContextPropagated (const bool &isPartitionContextPropagated)
{
    m_isPartitionContextPropagated = isPartitionContextPropagated;
}

bool WaveMessage::getIsPartitionContextPropagated () const
{
    return m_isPartitionContextPropagated;
}

bool WaveMessage::getIsPartitionNameSetByUser () const
{
    return m_isPartitionNameSetByUser;
}


vector<string> WaveMessage::getlocalizedCompletionStatusForStatusPropagationVector () const
{
    return (m_localizedCompletionStatusForStatusPropagation);
}

vector<ResourceId> WaveMessage::getcompletionStatusForStatusPropagationVector () const
{
    return (m_completionStatusForStatusPropagation);
}

vector<LocationId> WaveMessage::getlocationsForStatusPropagationVector () const
{
    return (m_locationsForStatusPropagation);
}

void WaveMessage::setlocalizedCompletionStatusForStatusPropagationVector (const vector<string> localizedCompletionStatusForStatusPropagation)
{
    m_localizedCompletionStatusForStatusPropagation= localizedCompletionStatusForStatusPropagation;
}

void WaveMessage::setcompletionStatusForStatusPropagationVector (const vector<ResourceId> completionStatusForStatusPropagation)
{
    m_completionStatusForStatusPropagation = completionStatusForStatusPropagation;
}

void WaveMessage::setlocationsForStatusPropagationVector (const vector<LocationId> locationsForStatusPropagation)
{
    m_locationsForStatusPropagation = locationsForStatusPropagation;
}

bool WaveMessage::getIsAConfigurationIntent () const
{
    return (m_isAConfigurationIntent);
}

void WaveMessage::setIsAConfigurationIntent (bool isAConfigurationIntent)
{
    m_isAConfigurationIntent = isAConfigurationIntent;
}

bool WaveMessage::getIsConfigurationIntentStored () const
{
    return (m_isConfigurationIntentStored);
}

void WaveMessage::setIsConfigurationIntentStored (bool isConfigurationIntentStored)
{
    m_isConfigurationIntentStored = isConfigurationIntentStored;
}

bool WaveMessage::getIsALastConfigReplay () const
{
    return (m_isALastConfigReplay);
}

void WaveMessage::setIsALastConfigReplay (bool isALastConfigReplay)
{
    m_isALastConfigReplay = isALastConfigReplay;
}

void WaveMessage::setTimeOutInMilliSeconds (const UI32 timeOutInMilliSeconds)
{
    m_timeOutInMilliSeconds = timeOutInMilliSeconds;
}

UI32 WaveMessage::getTimeOutInMilliSeconds () const
{
    return (m_timeOutInMilliSeconds);
}

bool WaveMessage::checkToDisconnectNodeFromLocationAfterReply () const
{
    return (m_disconnectFromNodeAfterReply);
}

void WaveMessage::setDisconnectFromLocationAfterReply (const bool &disconnectFlag)
{
    m_disconnectFromNodeAfterReply = disconnectFlag;
}

bool WaveMessage::checkToRemoveNodeFromKnownLocationAfterReply () const
{
    return (m_removeNodeFromKnownLocationAfterReply);
}

void WaveMessage::setRemoveNodeFromKnownLocationAfterReply (const bool &removeLocation)
{
    m_removeNodeFromKnownLocationAfterReply = removeLocation;
}

bool WaveMessage::checkToSendForOneWayCommunication () const
{
    return (m_sendForOneWayConnection);
}

void WaveMessage::setToAllowSendForOneWayCommunication (const bool &allowSend)
{
    m_sendForOneWayConnection = allowSend;
}

}
