/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Remote/InterLocationMessageReceiverThread.h"
#include "Framework/Messaging/Remote/InterLocationMessageReceiverObjectManager.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FixedSizeBuffer.h"
#include "Framework/Messaging/Remote/InterLocationMessageTransportObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/LocationManagement/WaveNodeConnectionInformation.h"
#include "Framework/Messaging/Remote/InterLocationTypes.h"
#include "Framework/Messaging/Remote/InterLocationMulticastMessage.h"
#include "Framework/ObjectModel/ServiceIndependentMessageHandlerMap.h"
#include "Framework/Messaging/Local/WaveServiceIndependentMessage.h"

namespace WaveNs
{

InterLocationMessageReceiverThread::InterLocationMessageReceiverThread (ServerStreamingSocket *pServerStreamingSocket)
    : WavePosixThread (),
      m_pServerStreamingSocket (pServerStreamingSocket),
      m_peerServerPort (0),
      m_peerServerMessageVersion (""),
      m_peerServerSerializationType (SERIALIZE_WITH_UNKNOWN)

{
    if (NULL == m_pServerStreamingSocket)
    {
        waveAssert (NULL != m_pServerStreamingSocket, __FILE__, __LINE__);
        trace (TRACE_LEVEL_FATAL, "InterLocationMessageReceiverThread::InterLocationMessageReceiverThread : Cannot create a InterLocationMessageReceiverThread with a NULL socket");
    }
}

InterLocationMessageReceiverThread::~InterLocationMessageReceiverThread ()
{
    if (NULL != m_pServerStreamingSocket)
    {
        // delete this thread from the cache of InterLocationMessageReceiverThread if those details were not already removed.

        if (0 != m_peerServerPort)
        {
            InterLocationMessageReceiverObjectManager::removeInterLocationMessageReceiverThreadFromCache (m_peerServerIpAddress, m_peerServerPort);
        }

		ResourceId failureStatus;
        m_peerServerMutex.lock ();

        if (0 != m_peerServerPort)
        {

            tracePrintf (TRACE_LEVEL_WARN, "InterLocationMessageReceiverThread::~InterLocationMessageReceiverThread : Invalidating Client Streaming socket for Ip Address : %s, Port %d", m_peerServerIpAddress.c_str (), m_peerServerPort);
            //(WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (m_peerServerIpAddress, m_peerServerPort, false);
            LocationId  peerServerLocationId = FrameworkToolKit::getLocationIdForIpAddressAndPort(m_peerServerIpAddress, m_peerServerPort);

			// Identify who went down and return status accordingly.
			failureStatus= ((FrameworkToolKit::getClusterPrimaryLocationId () == peerServerLocationId)?
											WAVE_MESSAGE_ERROR_REMOTE_LOCATION_UNAVAILABLE_DUE_TO_PRINCIPAL_FAILOVER:
											WAVE_MESSAGE_ERROR_REMOTE_LOCATION_UNAVAILABLE);

            (WaveFrameworkObjectManager::getInstance ())->invalidateClientStreamingSocketForRemoteLocation (peerServerLocationId);
            (InterLocationMessageTransportObjectManager::getInstance ())->replyToRemoteMessagesPendingOnLocation (peerServerLocationId, failureStatus);
            tracePrintf (TRACE_LEVEL_WARN, "InterLocationMessageReceiverThread::~InterLocationMessageReceiverThread : Invalidated client streaming socket for Ip Address : %s, Port %d reason %s", m_peerServerIpAddress.c_str (), m_peerServerPort,FrameworkToolKit::localize(failureStatus).c_str());


#if 0
            tracePrintf (TRACE_LEVEL_WARN, "InterLocationMessageReceiverThread::~InterLocationMessageReceiverThread : Disconnecting From Ip Address : %s, Port %d", m_peerServerIpAddress.c_str (), m_peerServerPort);
            (WaveFrameworkObjectManager::getInstance ())->disconnectFromLocation (m_peerServerIpAddress, m_peerServerPort, false);
            tracePrintf (TRACE_LEVEL_WARN, "InterLocationMessageReceiverThread::~InterLocationMessageReceiverThread : Disconnected  From Ip Address : %s, Port %d", m_peerServerIpAddress.c_str (), m_peerServerPort);
#endif


       }

        delete m_pServerStreamingSocket;
        m_pServerStreamingSocket = NULL;

        m_peerServerMutex.unlock ();

    }
}

WaveThreadStatus InterLocationMessageReceiverThread::start ()
{
    trace (TRACE_LEVEL_DEVEL, "InterLocationMessageReceiverThread::start : Starting ...");

    ResourceId connectionStatus                       = FRAMEWORK_ERROR;
    UI32       sizeOfConnectionInformation            = 0;
    string     peerIpAddress                          = m_pServerStreamingSocket->getPeerIpAddress ();
    string     peerServerConnectionInformationString;
    string     peerServerIpAddress;
    UI32       peerServerPort                         = 0;
    bool       isSuccessful                           = false;
    LocationId myExpectedLocationId                   = 0;
    bool       isMulticastMessage                     = false;
    string     messageVersion                         = "";

    // This is InterLocation receive socket. Set custom Keep Alive timeout settings.

    isSuccessful = m_pServerStreamingSocket->setCustomKeepAliveTimeouts ();

    // Need a trace message to indicate if 'Set custom Keep Alive timeout settings' failed.

    if (false == isSuccessful)
    {
        trace (TRACE_LEVEL_ERROR, string ("InterLocationMessageReceiverThread::start : \"setCustomKeepAliveTimeouts ()\" failed. peerIpAddress [") + peerIpAddress + string ("]"));
    }

    // Validate the client first

    if (true == isSuccessful)
    {
        isSuccessful = authorizeClient ();
    }

    // If the client is authorized, then read the peer's Connection Information (ipaddress and server port).

    if (true == isSuccessful)
    {
        isSuccessful = (*m_pServerStreamingSocket) >> sizeOfConnectionInformation;

        if (true == isSuccessful)
        {
            if (0 == sizeOfConnectionInformation)
            {
                trace (TRACE_LEVEL_FATAL, "WaveThreadStatus InterLocationMessageReceiverThread::start : If we have read the size successfully, it cannot be zero.");
                waveAssert (0 != sizeOfConnectionInformation, __FILE__, __LINE__);
            }
        }

        if (0 == sizeOfConnectionInformation)
        {
            // Indicate that the size could not be read

            isSuccessful = false;
        }
    }

    // By the time we reach here the sizeOfConnectionInformation should not be 0.  If it is still zero, set it to a min value so that the fixed size buffer will be created without assert.
    // In any case the client will not be accepted.

    if (0 == sizeOfConnectionInformation)
    {
        sizeOfConnectionInformation = 1;
    }

    FixedSizeBuffer peerConnectionInformationBuffer (sizeOfConnectionInformation);

    if (true == isSuccessful)
    {
        isSuccessful = (*m_pServerStreamingSocket) >> peerConnectionInformationBuffer;
    }

    if (true == isSuccessful)
    {
        if (0 == (peerConnectionInformationBuffer.getCurrentSize ()))
        {
            isSuccessful = false;
        }
    }

    if (true == isSuccessful)
    {
        WaveNodeConnectionInformation peerServerConnectionInformation;

        peerConnectionInformationBuffer.toString (peerServerConnectionInformationString);
        peerServerConnectionInformation.loadFromSerializedData2 (peerServerConnectionInformationString, SERIALIZE_WITH_ATTRIBUTE_NAME);

        peerServerIpAddress = peerServerConnectionInformation.getThisLocationServerIpAddress ();
        peerServerPort      = peerServerConnectionInformation.getThisLocationServerPort ();
        myExpectedLocationId    = peerServerConnectionInformation.getExpectedLocationId ();
        messageVersion      = peerServerConnectionInformation.getMessageVersion ();

        trace (TRACE_LEVEL_INFO, string ("                message Version                 : \"") + messageVersion + "\"");
        if (true == messageVersion.empty())
        {
            messageVersion = string ("0.0.0");
        }

        trace (TRACE_LEVEL_INFO, string ("Remote Location Ip Address                      : \"") + peerServerIpAddress + "\"");
        trace (TRACE_LEVEL_INFO, string ("                Port                            : \"") + peerServerPort + "\"");
        trace (TRACE_LEVEL_INFO, string ("                message Version                 : \"") + messageVersion + "\"");
        trace (TRACE_LEVEL_INFO, string ("Remote Location Connection Interface Ip Address : \"") + peerIpAddress + "\"");
        trace (TRACE_LEVEL_INFO, string ("                Expected LocationId             : \"") + myExpectedLocationId + "\"");
    }

    if (0 != (strcmp (peerIpAddress.c_str (),  peerServerIpAddress.c_str ())))
    {
        // Reset the value in peer Ip Address.

        peerIpAddress = peerServerIpAddress;
    }

    if (true == isSuccessful)
    {
        // The following must be assigned before we call addInterLocationMessageReceiverThreadToCache.

        setPeerServerDetails (peerServerIpAddress, (SI32) peerServerPort, messageVersion);

        // Make sure that there is no other thread handling the same location.  If there is another one,
        // wait till it exits.

        InterLocationMessageReceiverThread *pTempInterLocationMessageReceiverThread = this;

        bool cacheStatus = InterLocationMessageReceiverObjectManager::addInterLocationMessageReceiverThreadToCache (m_peerServerIpAddress, m_peerServerPort, pTempInterLocationMessageReceiverThread);

        if (true == cacheStatus)
        {
            // If the location role is secondary unconfirmed or primary unconfirmed do not connect back immediately.
            // We will connect back during phase 0 after shutting down all the services
            // This is done to avoid global services active in the rejoining secondary nodes writing to the primary
            // Only after shutting down these services we must connect back to the primary.

            if ((LOCATION_PRIMARY == FrameworkToolKit::getThisLocationRole ()) || (LOCATION_SECONDARY_UNCONFIRMED == FrameworkToolKit::getThisLocationRole ()) || (LOCATION_PRIMARY_UNCONFIRMED == FrameworkToolKit::getThisLocationRole ()) || (myExpectedLocationId != FrameworkToolKit::getThisLocationId ()))
            {
                connectionStatus = FRAMEWORK_UNKNOWN_LOCATION;
            }
            else
            {
                // Before starting to do anything, let us make sure that we are connected to the peer.
                if (false  == InterLocationMessageReceiverObjectManager::isACurrentlyConnectedLocation (FrameworkToolKit::getClusterPrimaryIpAddress (), FrameworkToolKit::getClusterPrimaryPort ()))
                {
                    connectionStatus = FRAMEWORK_UNKNOWN_LOCATION;
                }
                else
                {

                    connectionStatus = (WaveFrameworkObjectManager::getInstance ())->connectToLocation (m_peerServerIpAddress, m_peerServerPort);

                    if (FRAMEWORK_SUCCESS != connectionStatus)
                    {
                        trace (TRACE_LEVEL_WARN, "InterLocationMessageReceiverThread::start : We could not connect back to " + m_peerServerIpAddress + ":" + m_peerServerPort);
                    }
                }
            }
        }

        UI32 messageSize = 0;

        while ((FRAMEWORK_SUCCESS == connectionStatus) || (FRAMEWORK_UNKNOWN_LOCATION == connectionStatus))
        {
            isSuccessful = (*m_pServerStreamingSocket) >> messageSize;

            // Message size of 0xFFFFFFFF indicates that the peer is shutting down the connection.

            if ((false == isSuccessful) || (0xFFFFFFFF == messageSize) || (0 == messageSize))
            {
                break;
            }

            FixedSizeBuffer *pNewFixedSizeBuffer = new FixedSizeBuffer (messageSize);

            //trace (TRACE_LEVEL_DEVEL, string ("InterLocationMessageReceiverThread::start : received a message size indicator : ") + messageSize + ".");

            if (NULL == pNewFixedSizeBuffer)
            {
                trace (TRACE_LEVEL_FATAL, string ("InterLocationMessageReceiverThread::start : Could not allocate a new FixedSizeBuffer of size ") + messageSize + ".");
                waveAssert (false, __FILE__, __LINE__);
            }

            isSuccessful = (*m_pServerStreamingSocket) >> (*pNewFixedSizeBuffer);

            trace (TRACE_LEVEL_DEVEL, "InterLocationMessageReceiverThread::start : Completed reading the buffer.");

            if ((false == isSuccessful) || (0 == (pNewFixedSizeBuffer->getCurrentSize ())))
            {
                delete pNewFixedSizeBuffer;
                break;
            }
            else
            {
                // First create a WaveMessage from the contents of the FixedBuffer that we have read from the network.
                // Now depending on the contents of the message that arrived decide if it is a new request or a response to a request
                // this location sent out.

                // We can safely cast from SerializableObject pointer to WaveMessage pointer since we know that only object that
                // travels brtween two nodes in a Wave based cluster is a WaveMessage;
                // FIXME : sagar : enforce that the object type that was returned is indeed a WaveMessage or a specialization of
                //                 WaveMessage.

                string messageString;

                pNewFixedSizeBuffer->toString (messageString);

                // We do not need the Fixed Size Buffer anymore.  So delete it.

                delete pNewFixedSizeBuffer;

                //trace (TRACE_LEVEL_DEVEL, messageString);

                // Now read the buffer data

                UI32          numberOfBuffers = 0;
                UI32          i               = 0;
                vector<UI32>  bufferTags;
                vector<UI32>  bufferSizes;
                vector<UI8 *> buffers;

                isSuccessful = (*m_pServerStreamingSocket) >> numberOfBuffers;

                if (true == isSuccessful)
                {
                    for (i = 0; i < numberOfBuffers; i++)
                    {
                        UI32  bufferTag  = 0;
                        UI32  bufferSize = 0;
                        void *pBuffer    = NULL;

                        isSuccessful = (*m_pServerStreamingSocket) >> bufferTag;

                        if (false == isSuccessful)
                        {
                            break;
                        }

                        isSuccessful = (*m_pServerStreamingSocket) >> bufferSize;

                        if ((false == isSuccessful) || (0 == bufferSize))
                        {
                            break;
                        }

                        waveAssert (0 != bufferSize, __FILE__, __LINE__);

                        pBuffer = new UI8[bufferSize];

                        waveAssert (NULL != pBuffer, __FILE__, __LINE__);

                        FixedSizeBuffer tempBuffer (bufferSize, pBuffer, false);

                        isSuccessful = (*m_pServerStreamingSocket) >> tempBuffer;

                        if ((false == isSuccessful) || (0 == (tempBuffer.getCurrentSize ())))
                        {
                            delete[] (reinterpret_cast<UI8 *> (pBuffer));
                            break;
                        }

                        bufferTags.push_back  (bufferTag);
                        bufferSizes.push_back (bufferSize);
                        buffers.push_back     (reinterpret_cast<UI8 *> (pBuffer));
                    }
                }

                UI8              serializationType              = m_peerServerSerializationType;
                UI32             messageIdAtOriginatingLocation = WaveMessage::getMessageIdAtOriginatingLocation (messageString, serializationType);
                WaveMessageType  messageType                    = WaveMessage::getType (messageString, serializationType);
                WaveMessage    *pWaveMessage                  = NULL;

                if (WAVE_MESSAGE_TYPE_REQUEST == messageType)
                {
                    pWaveMessage = WaveMessage::createAndLoadFromSerializedData2 (messageString, 0, serializationType);
                }
                else if (WAVE_MESSAGE_TYPE_RESPONSE == messageType)
                {
                    (InterLocationMessageTransportObjectManager::getInstance ())->lockGlobalAccessMutexForMulticastMessaging ();

                    pWaveMessage = (InterLocationMessageTransportObjectManager::getInstance ())->getPendingMessageWithoutRemove (messageIdAtOriginatingLocation);

                    if (NULL != pWaveMessage)
                    {
                        if ((INTERLOCATION_MESSAGE_FOR_MULTICAST_SEND == pWaveMessage->getOperationCode ()) && (pWaveMessage->getServiceCode () == (InterLocationMessageTransportObjectManager::getInstance ())->getServiceId ()))
                        {
                            ResourceId                     completionStatus               = WaveMessage::getMessageCompletionStatus (messageString);
                            LocationId                     receiverLocationId             = FrameworkToolKit::getLocationIdForIpAddressAndPort (peerServerIpAddress, peerServerPort);
                            InterLocationMulticastMessage *pInterLocationMulticastMessage = dynamic_cast<InterLocationMulticastMessage *>(pWaveMessage);

                            waveAssert (NULL != pInterLocationMulticastMessage, __FILE__, __LINE__);

                            pInterLocationMulticastMessage->messageOperationAccess ();

                            if (true == pInterLocationMulticastMessage->isMessageSentToThisLocationNotReplied (receiverLocationId))
                            {
                                pInterLocationMulticastMessage->setStatusForALocation (receiverLocationId, completionStatus);
                                pInterLocationMulticastMessage->setMessageRepliedToThisLocation (receiverLocationId);

                                --(*pInterLocationMulticastMessage);
                            }

                            isMulticastMessage = true;
                        }
                        else
                        {
                            isMulticastMessage = false;

                            pWaveMessage = (InterLocationMessageTransportObjectManager::getInstance ())->getPendingMessage (messageIdAtOriginatingLocation);

                            (InterLocationMessageTransportObjectManager::getInstance ())->unlockGlobalAccessMutexForMulticastMessaging ();

                            pWaveMessage->removeAllBuffers ();
                            pWaveMessage->loadFromSerializedData2 (messageString, serializationType);
                        }
                    }
                    else
                    {
                        (InterLocationMessageTransportObjectManager::getInstance ())->unlockGlobalAccessMutexForMulticastMessaging ();
                    }
                }
                else
                {
                    waveAssert (false, __FILE__, __LINE__);
                }

                // If we have a message at hand then attach the buffer to the message.
                // Otherwise destroy the buffers.

                // Recompute the actual number of buffers read from the wire at this time

                numberOfBuffers = buffers.size ();

                if (NULL != pWaveMessage)
                {
                    for (i = 0; i < numberOfBuffers; i++)
                    {
                        pWaveMessage->addBuffer (bufferTags[i], bufferSizes[i], buffers[i], true);
                    }
                }
                else
                {
                    for (i = 0; i < numberOfBuffers; i++)
                    {
                        delete[] (reinterpret_cast<UI8 *> (buffers[i]));
                    }
                }


                // if we have a message at hand
                // Now depending on the message type process it.

                if (NULL != pWaveMessage)
                {
                    if (WAVE_MESSAGE_TYPE_REQUEST == messageType)
                    {
                        trace (TRACE_LEVEL_DEVEL, "InterLocationMessageReceiverThread::start : We received a Remote message destined to this location and delivering it to corresponding service.");

                        WaveServiceIndependentMessage *pWaveServiceIndependentMessage = dynamic_cast<WaveServiceIndependentMessage *> (pWaveMessage);

                        if (NULL != pWaveServiceIndependentMessage)
                        {
                            ServiceIndependentMessageHandlerMap::execute (pWaveServiceIndependentMessage);

                            pWaveServiceIndependentMessage->setType (WAVE_MESSAGE_TYPE_RESPONSE);

                            ResourceId status = (InterLocationMessageTransportObjectManager::getInstance ())->postToRemoteLocation (pWaveServiceIndependentMessage);

                            if (WAVE_MESSAGE_SUCCESS != status)
                            {
                                trace (TRACE_LEVEL_DEVEL, "InterLocationMessageReceiverThread::start: We could not deliver a response destined for the remote location.");
                            }

                            if (pWaveServiceIndependentMessage)
                            {
                                delete (pWaveServiceIndependentMessage);
                                pWaveServiceIndependentMessage = NULL;
                            }
                        }
                        else
                        {
                            // If we successfully read the entire message and its buffers then send it.
                            // Otherwise simply destroy it.  We cannot deliver half read messages.

                            if (true == isSuccessful)
                            {
                                (InterLocationMessageTransportObjectManager::getInstance ())->sendToBeUsedByReceiverThreads (pWaveMessage);
                            }
                            else
                            {
                                delete pWaveMessage;
                            }
                        }
                    }
                    else if (WAVE_MESSAGE_TYPE_RESPONSE == messageType)
                    {
                        //trace (TRACE_LEVEL_DEVEL, "InterLocationMessageReceiverThread::start : We received a Remote message response from a remote location.");

                        // If we successfully read the entire message and its buffers then process the message response normally.
                        // Otherwise indicate that the message buffers could not be read properly.

                        if (true == isMulticastMessage)
                        {
                            InterLocationMulticastMessage *pInterLocationMulticastMessage = dynamic_cast<InterLocationMulticastMessage *>(pWaveMessage);

                            waveAssert (NULL != pInterLocationMulticastMessage, __FILE__, __LINE__);

                            if (false == isSuccessful)
                            {
                                LocationId receiverLocationId = FrameworkToolKit::getLocationIdForIpAddressAndPort (peerServerIpAddress, peerServerPort);
                                ResourceId resourceId         = WAVE_MESSAGE_ERROR_INCOMPLETE_BUFFER_READ_FROM_REMOTE_LOCATION;

                                pInterLocationMulticastMessage->setStatusForALocation (receiverLocationId, resourceId);
                            }

                            if (true == pInterLocationMulticastMessage->areAllMessageRepliesReceived ())
                            {
                                WaveMessage *pTempWaveMessage = (InterLocationMessageTransportObjectManager::getInstance ())->getPendingMessage (messageIdAtOriginatingLocation);

                                waveAssert (pTempWaveMessage == pWaveMessage, __FILE__, __LINE__);

                                (InterLocationMessageTransportObjectManager::getInstance ())->unlockGlobalAccessMutexForMulticastMessaging ();

                                pInterLocationMulticastMessage->messageOperationReleaseAccess ();

                                (InterLocationMessageTransportObjectManager::getInstance ())->replyToBeUsedByReceiverThreads (pWaveMessage);
                            }
                            else
                            {
                                (InterLocationMessageTransportObjectManager::getInstance ())->unlockGlobalAccessMutexForMulticastMessaging ();

                                pInterLocationMulticastMessage->messageOperationReleaseAccess ();
                            }
                        }
                        else
                        {
                            if (false == isSuccessful)
                            {
                                pWaveMessage->setCompletionStatus (WAVE_MESSAGE_ERROR_INCOMPLETE_BUFFER_READ_FROM_REMOTE_LOCATION);
                            }

                            (InterLocationMessageTransportObjectManager::getInstance ())->replyToBeUsedByReceiverThreads (pWaveMessage);
                        }
                    }
                    else
                    {
                        trace (TRACE_LEVEL_FATAL, "InterLocationMessageReceiverThread::start : Currently, Only Messages and their Responses can be transported across Locations.");
                        waveAssert (false, __FILE__, __LINE__);
                    }
                }

                // In any case if the buffer related information is not read successfully, bail out from here.
                // Some thing is wrong with the connection.

                if (false == isSuccessful)
                {
                    break;
                }
            }
        }
    }

    delete this;

    //pthread_exit (NULL);

    return (WAVE_THREAD_SUCCESS);
}

bool InterLocationMessageReceiverThread::authorizeClient ()
{
    // Try to read the Wave connection Pass Phrase.  If the connected client does not supply the
    // proper pass phrase, then we know it is a rogue client.  We must drop the client.

    bool            isSuccessful              = false;
    string          wavePassPhrase           = FrameworkToolKit::getWaveConnectionPassPhrase ();
    FixedSizeBuffer passphraseFixedSizeBuffer (wavePassPhrase.size ());

    isSuccessful = (*m_pServerStreamingSocket) >> (passphraseFixedSizeBuffer);

    if ((false == isSuccessful) || (0 == (passphraseFixedSizeBuffer.getCurrentSize ())))
    {
        trace (TRACE_LEVEL_DEBUG, "InterLocationMessageReceiverThread::start : A client could not supply proper credentials.  Ignoring client.");
    }
    else
    {
        string passPhraseGivenByClient;

        passphraseFixedSizeBuffer.toString (passPhraseGivenByClient);

        if (passPhraseGivenByClient != wavePassPhrase)
        {
            isSuccessful = false;

            trace (TRACE_LEVEL_WARN, "InterLocationMessageReceiverThread::start : A client supplied improper credentials.  Ignoring client.");
        }
    }

    return (isSuccessful);
}

void InterLocationMessageReceiverThread::setPeerServerDetails (const string &peerServerIpAddress, const SI32 &peerServerPort, const string& messageVersion)
{
    m_peerServerMutex.lock ();

    m_peerServerIpAddress           = peerServerIpAddress;
    m_peerServerPort                = (SI32) peerServerPort;
    m_peerServerMessageVersion      = messageVersion;

    if (messageVersion.empty ())
    {
        m_peerServerSerializationType = SERIALIZE_WITH_UNKNOWN;
    }
    else
    {
        m_peerServerSerializationType = ((0 == messageVersion.compare ("0.0.0")) ? SERIALIZE_WITH_ATTRIBUTE_ORDER : SERIALIZE_WITH_ATTRIBUTE_NAME);
    }

    m_peerServerMutex.unlock ();
}

string InterLocationMessageReceiverThread::getPeerServerMessageVersion () const
{
    return (m_peerServerMessageVersion);
}

UI8 InterLocationMessageReceiverThread::getPeerServerSerializationType () const
{
    return (m_peerServerSerializationType);
}

void InterLocationMessageReceiverThread::closePeerServerStreamingSocket (void)
{
    m_peerServerMutex.lock ();

    if (NULL != m_pServerStreamingSocket)
    {
        m_pServerStreamingSocket->close ();
    }

    m_peerServerMutex.unlock ();
}

}
