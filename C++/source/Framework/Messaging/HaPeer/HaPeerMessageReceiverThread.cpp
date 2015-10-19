/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/HaPeer/HaPeerMessageReceiverThread.h"
#include "Framework/Messaging/HaPeer/HaPeerMessageReceiverObjectManager.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FixedSizeBuffer.h"
#include "Framework/Messaging/HaPeer/HaPeerMessageTransportObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManagerHaSyncWorker.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/LocationManagement/WaveNodeConnectionInformation.h"
#include "Framework/ObjectModel/ServiceIndependentMessageHandlerMap.h"
#include "Framework/Messaging/Local/WaveServiceIndependentMessage.h"

namespace WaveNs
{

HaPeerMessageReceiverThread::HaPeerMessageReceiverThread (ServerStreamingSocket *pServerStreamingSocket)
    : WavePosixThread (),
      m_pServerStreamingSocket (pServerStreamingSocket),
      m_peerServerPort (0),
      m_peerServerMessageVersion (""),
      m_peerServerSerializationType (SERIALIZE_WITH_UNKNOWN)
{
    if (NULL == m_pServerStreamingSocket)
    {
        waveAssert (NULL != m_pServerStreamingSocket, __FILE__, __LINE__);
        trace (TRACE_LEVEL_FATAL, "HaPeerMessageReceiverThread::HaPeerMessageReceiverThread : Cannot create a HaPeerMessageReceiverThread with a NULL socket");
    }
}

HaPeerMessageReceiverThread::~HaPeerMessageReceiverThread ()
{
    if (NULL != m_pServerStreamingSocket)
    {
        m_peerServerMutex.lock ();

        if (0 != m_peerServerPort)
        {
            tracePrintf (TRACE_LEVEL_WARN, "HaPeerMessageReceiverThread::~HaPeerMessageReceiverThread : Disconnecting From Ip Address : %s, Port %d", m_peerServerIpAddress.c_str (), m_peerServerPort);
            (WaveFrameworkObjectManagerHaSyncWorker::getInstance ())->disconnectFromHaPeer (m_peerServerIpAddress, m_peerServerPort, false);
            tracePrintf (TRACE_LEVEL_WARN, "HaPeerMessageReceiverThread::~HaPeerMessageReceiverThread : Disconnected  From Ip Address : %s, Port %d", m_peerServerIpAddress.c_str (), m_peerServerPort);
        }

        delete m_pServerStreamingSocket;
        m_pServerStreamingSocket = NULL;

        m_peerServerMutex.unlock ();

        // delete this thread from the cache of HaPeerMessageReceiverThread if those details were not already removed.

        if (0 != m_peerServerPort)
        {
            HaPeerMessageReceiverObjectManager::removeHaPeerMessageReceiverThreadFromCache (m_peerServerIpAddress, m_peerServerPort);
        }
    }
}

WaveThreadStatus HaPeerMessageReceiverThread::start ()
{
    trace (TRACE_LEVEL_DEVEL, "HaPeerMessageReceiverThread::start : Starting ...");

    ResourceId connectionStatus                       = FRAMEWORK_ERROR;
    UI32       sizeOfConnectionInformation            = 0;
    string     peerIpAddress                          = m_pServerStreamingSocket->getPeerIpAddress ();
    string     peerServerConnectionInformationString;
    string     peerServerIpAddress;
    UI32       peerServerPort                         = 0;
    bool       isSuccessful                           = false;
    string     messageVersion                         = "";

    // Validate the client first

    isSuccessful = authorizeClient ();

    // If the client is authorized, then read the peer's Connection Information (ipaddress and server port).

    if (true == isSuccessful)
    {
        isSuccessful = (*m_pServerStreamingSocket) >> sizeOfConnectionInformation;

        if (true == isSuccessful)
        {
            if (0 == sizeOfConnectionInformation)
            {
                trace (TRACE_LEVEL_FATAL, "WaveThreadStatus HaPeerMessageReceiverThread::start : If we have read the size successfully, it cannot be zero.");
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
        WaveHaNodeConnectionInformation peerServerConnectionInformation;

        peerConnectionInformationBuffer.toString (peerServerConnectionInformationString);
        peerServerConnectionInformation.loadFromSerializedData2 (peerServerConnectionInformationString, SERIALIZE_WITH_ATTRIBUTE_ORDER);

        peerServerIpAddress = peerServerConnectionInformation.getThisLocationServerIpAddress ();
        peerServerPort      = peerServerConnectionInformation.getThisLocationServerPort ();
        messageVersion      = peerServerConnectionInformation.getMessageVersion ();

        trace (TRACE_LEVEL_DEBUG, string ("                message Version                 : \"") + messageVersion + "\"");

        if (true == messageVersion.empty())
        {
            messageVersion = string ("0.0.0");
        }

        trace (TRACE_LEVEL_INFO, string ("HA Location Ip Address                      : \"") + peerServerIpAddress + "\"");
        trace (TRACE_LEVEL_INFO, string ("                Port                            : \"") + peerServerPort + "\"");
        trace (TRACE_LEVEL_INFO, string ("                Message Version             : \"") + messageVersion + "\"");
        trace (TRACE_LEVEL_INFO, string ("HA Location Connection Interface Ip Address : \"") + peerIpAddress + "\"");
    }

    if (0 != (strcmp (peerIpAddress.c_str (),  peerServerIpAddress.c_str ())))
    {
        // Reset the value in peer Ip Address.

        peerIpAddress = peerServerIpAddress;
    }

    if (true == isSuccessful)
    {
        // The following must be assigned before we call addHaPeerMessageReceiverThreadToCache.

        setPeerServerDetails (peerServerIpAddress, (SI32) peerServerPort, messageVersion);

        // Make sure that there is no other thread handling the same location.  If there is another one,
        // wait till it exits.

        HaPeerMessageReceiverThread *pTempHaPeerMessageReceiverThread = this;


        bool cacheStatus = HaPeerMessageReceiverObjectManager::addHaPeerMessageReceiverThreadToCache (m_peerServerIpAddress, m_peerServerPort, pTempHaPeerMessageReceiverThread);

        if (true == cacheStatus)
        {
            // Before starting to do anything, let us make sure that we are connected to the peer.

            connectionStatus = (WaveFrameworkObjectManagerHaSyncWorker::getInstance ())->connectToHaPeer (m_peerServerIpAddress, m_peerServerPort);

            if (FRAMEWORK_SUCCESS != connectionStatus)
            {
                trace (TRACE_LEVEL_WARN, "HaPeerMessageReceiverThread::start : We could not connect back to " + m_peerServerIpAddress + ":" + m_peerServerPort);
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

            //trace (TRACE_LEVEL_DEVEL, string ("HaPeerMessageReceiverThread::start : received a message size indicator : ") + messageSize + ".");

            if (NULL == pNewFixedSizeBuffer)
            {
                trace (TRACE_LEVEL_FATAL, string ("HaPeerMessageReceiverThread::start : Could not allocate a new FixedSizeBuffer of size ") + messageSize + ".");
                waveAssert (false, __FILE__, __LINE__);
            }

            isSuccessful = (*m_pServerStreamingSocket) >> (*pNewFixedSizeBuffer);

            trace (TRACE_LEVEL_DEVEL, "HaPeerMessageReceiverThread::start : Completed reading the buffer.");

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

                UI8                 serializationType               = m_peerServerSerializationType;
                UI32                messageIdAtOriginatingLocation  = WaveMessage::getMessageIdAtOriginatingLocation (messageString, serializationType); 
                WaveMessageType     messageType                     = WaveMessage::getType (messageString, serializationType); 
                WaveMessage       *pWaveMessage                   = NULL;

                if (WAVE_MESSAGE_TYPE_REQUEST == messageType)
                {
                    pWaveMessage = WaveMessage::createAndLoadFromSerializedData2 (messageString, 0, serializationType); 
                }
                else if (WAVE_MESSAGE_TYPE_RESPONSE == messageType)
                {
                    pWaveMessage = (HaPeerMessageTransportObjectManager::getInstance ())->getPendingMessage (messageIdAtOriginatingLocation);

                    if (NULL != pWaveMessage)
                    {
                        pWaveMessage->removeAllBuffers ();
                        pWaveMessage->loadFromSerializedData2 (messageString, serializationType); 
                    }
                }
                else
                {
                    waveAssert (false, __FILE__, __LINE__);
                }

                //waveAssert (NULL != pWaveMessage, __FILE__, __LINE__);

                // Now read the buffer data

                UI32 numberOfBuffers = 0;
                UI32 i               = 0;

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

                        // If we have a message at hand then attach the buffer to the message.
                        // Otherwise destroy the buffer.

                        if (NULL != pWaveMessage)
                        {
                            if (WAVE_MESSAGE_TYPE_REQUEST == messageType)
                            {
                                pWaveMessage->addBuffer (bufferTag, bufferSize, pBuffer, true);
                            }
                            else if (WAVE_MESSAGE_TYPE_RESPONSE == messageType)
                            {
                                pWaveMessage->addBuffer (bufferTag, bufferSize, pBuffer, true);
                            }
                            else
                            {
                                trace (TRACE_LEVEL_FATAL, "HaPeerMessageReceiverThread::start : Currently, Only Messages and their Responses can be transported across Locations.");
                                waveAssert (false, __FILE__, __LINE__);
                            }
                        }
                        else
                        {
                            delete[] (reinterpret_cast<UI8 *> (pBuffer));
                        }
                    }
                }

                // if we have a message at hand
                // Now depending on the message type process it.

                if (NULL != pWaveMessage)
                {
                    if (WAVE_MESSAGE_TYPE_REQUEST == messageType)
                    {
                        trace (TRACE_LEVEL_DEVEL, "HaPeerMessageReceiverThread::start : We received a Remote message destined to this location and delivering it to corresponding service.");

                        WaveServiceIndependentMessage *pWaveServiceIndependentMessage = dynamic_cast<WaveServiceIndependentMessage *> (pWaveMessage);

                        if (NULL != pWaveServiceIndependentMessage)
                        {
                            ServiceIndependentMessageHandlerMap::execute (pWaveServiceIndependentMessage);

                            pWaveServiceIndependentMessage->setType (WAVE_MESSAGE_TYPE_RESPONSE);

                            ResourceId status = (HaPeerMessageTransportObjectManager::getInstance ())->postToHaPeerLocation (pWaveServiceIndependentMessage);

                            if (WAVE_MESSAGE_SUCCESS != status)
                            {
                                trace (TRACE_LEVEL_DEVEL, "HaPeerMessageReceiverThread::start: We could not deliver a response destined for the HA peer.");
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
                                (HaPeerMessageTransportObjectManager::getInstance ())->sendToBeUsedByReceiverThreads (pWaveMessage);
                            }
                            else
                            {
                                delete pWaveMessage;
                            }
                        }
                    }
                    else if (WAVE_MESSAGE_TYPE_RESPONSE == messageType)
                    {
                        //trace (TRACE_LEVEL_DEVEL, "HaPeerMessageReceiverThread::start : We received a Remote message response from a remote location.");

                        // If we successfully read the entire message and its buffers then process the message response normally.
                        // Otherwise indicate that the message buffers could not be read properly.

                        if (false == isSuccessful)
                        {
                            pWaveMessage->setCompletionStatus (WAVE_MESSAGE_ERROR_INCOMPLETE_BUFFER_READ_FROM_REMOTE_LOCATION);
                        }

                        (HaPeerMessageTransportObjectManager::getInstance ())->replyToBeUsedByReceiverThreads (pWaveMessage);
                    }
                    else
                    {
                        trace (TRACE_LEVEL_FATAL, "HaPeerMessageReceiverThread::start : Currently, Only Messages and their Responses can be transported across Locations.");
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

bool HaPeerMessageReceiverThread::authorizeClient ()
{
    // Try to read the Wave connection Pass Phrase.  If the connected client does not supply the
    // proper pass phrase, then we know it is a rogue client.  We must drop the client.

    bool            isSuccessful              = false;
    string          waveHaPassPhrase           = FrameworkToolKit::getWaveHaConnectionPassPhrase ();
    FixedSizeBuffer passphraseFixedSizeBuffer (waveHaPassPhrase.size ());

    isSuccessful = (*m_pServerStreamingSocket) >> (passphraseFixedSizeBuffer);

    if ((false == isSuccessful) || (0 == (passphraseFixedSizeBuffer.getCurrentSize ())))
    {
        trace (TRACE_LEVEL_WARN, "HaPeerMessageReceiverThread::start : A client could not supply proper credentials.  Ignoring client.");
    }
    else
    {
        string passPhraseGivenByClient;

        passphraseFixedSizeBuffer.toString (passPhraseGivenByClient);

        if (passPhraseGivenByClient != waveHaPassPhrase)
        {
            isSuccessful = false;

            trace (TRACE_LEVEL_WARN, "HaPeerMessageReceiverThread::start : A client supplied improper credentials.  Ignoring client.");
        }
    }

    return (isSuccessful);
}

void HaPeerMessageReceiverThread::setPeerServerDetails (const string &peerServerIpAddress, const SI32 &peerServerPort, const string& messageVersion)
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

void HaPeerMessageReceiverThread::closePeerServerStreamingSocket (void)
{
    m_peerServerMutex.lock ();

    if (NULL != m_pServerStreamingSocket)
    {
        m_pServerStreamingSocket->close ();
    }

    m_peerServerMutex.unlock ();
}

string HaPeerMessageReceiverThread::getPeerServerMessageVersion () const
{
    return (m_peerServerMessageVersion);
}

UI8 HaPeerMessageReceiverThread::getPeerServerSerializationType () const
{
    return (m_peerServerSerializationType);
}
}
