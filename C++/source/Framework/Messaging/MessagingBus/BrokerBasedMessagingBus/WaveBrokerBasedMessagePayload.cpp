/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/BrokerBasedMessagingBus/WaveBrokerBasedMessagePayload.h"

namespace WaveNs
{

WaveBrokerBasedMessagePayload::WaveBrokerBasedMessagePayload ()
    : m_messageBodySize            (0),
      m_pMessageBody               (NULL),
      m_numberOfBuffers            (0),
      m_isPreparedForPostingOnWire (false),
      m_pIoVector                  (NULL),
      m_ioVectorCount              (0)
{
}

WaveBrokerBasedMessagePayload::~WaveBrokerBasedMessagePayload ()
{
    UI32 numberOfBuffers = m_buffers.size ();
    UI32 i               = 0;

    if (NULL != m_pMessageBody)
    {
        delete[] m_pMessageBody;
    }

    for (i = 0; i < numberOfBuffers; i++)
    {
        delete[] m_buffers[i];
    }

    if (NULL != m_pIoVector)
    {
        delete[] m_pIoVector;
    }
}

UI32 &WaveBrokerBasedMessagePayload::getMessageBodySize ()
{
    return (m_messageBodySize);
}

char *&WaveBrokerBasedMessagePayload::getMessageBody ()
{
    return (m_pMessageBody);
}

vector<UI32> &WaveBrokerBasedMessagePayload::getBufferTags ()
{
    return (m_bufferTags);
}

vector<UI32> &WaveBrokerBasedMessagePayload::getBufferSizes ()
{
    return (m_bufferSizes);
}

vector<UI8 *> &WaveBrokerBasedMessagePayload::getBuffers ()
{
    return (m_buffers);
}

void WaveBrokerBasedMessagePayload::prepareAndGetIovecToPostOnWire (struct iovec **pIoVector, UI32 &ioVectorCount)
{
    if (NULL == m_pIoVector)
    {
        m_messageBodySize = htonl (m_messageBodySize);
        m_numberOfBuffers = htonl (m_buffers.size ());

        m_ioVectorCount = 3;

        m_pIoVector = new struct iovec[m_ioVectorCount];

        m_pIoVector[0].iov_base = &m_messageBodySize;
        m_pIoVector[0].iov_len  = sizeof (m_messageBodySize);

        m_pIoVector[1].iov_base = (void *) (m_pMessageBody);
        m_pIoVector[1].iov_len  = ntohl (m_messageBodySize);

        m_pIoVector[2].iov_base = &m_numberOfBuffers;
        m_pIoVector[2].iov_len  = sizeof (m_numberOfBuffers);
    }

    *pIoVector     = m_pIoVector;
     ioVectorCount = m_ioVectorCount;

    return;
}

}
