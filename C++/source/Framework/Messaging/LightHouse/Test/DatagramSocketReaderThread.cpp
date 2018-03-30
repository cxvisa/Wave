/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/Test/DatagramSocketReaderThread.h"
#include "Framework/Utils/ServerDatagramSocket.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

DatagramSocketReaderThread::DatagramSocketReaderThread (ServerDatagramSocket *pServerDatagramSocket)
    : WavePosixThread         (),
      m_pServerDatagramSocket (pServerDatagramSocket)
{
    WaveNs::waveAssert (NULL != m_pServerDatagramSocket, __FILE__, __LINE__);
}

DatagramSocketReaderThread::~DatagramSocketReaderThread ()
{
    if (NULL != m_pServerDatagramSocket)
    {
        delete m_pServerDatagramSocket;
    }
}

WaveThreadStatus DatagramSocketReaderThread::start ()
{
    ReadReadyStatus readReadyStatus = READ_READY_FATAL_ERROR;

    m_pServerDatagramSocket->setNonBlocking ();

    const UI32 maxNumberOfSecureSocketAcceptAttemps = 10;
          UI32 attemptCount                         = 0;
          bool isAccepted                           = false;

    if (true == (m_pServerDatagramSocket->isSecurityEnabled ()))
    {
        while (attemptCount < maxNumberOfSecureSocketAcceptAttemps)
        {
            readReadyStatus = m_pServerDatagramSocket->isDataAvailableToRead ();

            if (READ_READY_FATAL_ERROR == readReadyStatus)
            {
                break;
            }
            else if (READ_READY_TIMEOUT == readReadyStatus)
            {
                attemptCount++;
                continue;
            }

            isAccepted = m_pServerDatagramSocket->accept ();

            if (true == isAccepted)
            {
                break;
            }
            else
            {
                attemptCount++;
            }
        }
    }
    else
    {
        isAccepted = true;
    }

    if (! isAccepted)
    {
        delete this;

        return (WAVE_THREAD_SUCCESS);
    }

    while (true)
    {
        readReadyStatus = m_pServerDatagramSocket->isDataAvailableToRead ();

        if (READ_READY_FATAL_ERROR == readReadyStatus)
        {
            break;
        }
        else if (READ_READY_TIMEOUT == readReadyStatus)
        {
            break;
        }

        string messageReceived;

        bool isSuccessful = m_pServerDatagramSocket->receive (messageReceived);

        if (true == isSuccessful)
        {
            WaveNs::trace (TRACE_LEVEL_DEBUG, "DatagramSocketReaderThread::serverDatagramTest : Successfully received : " + messageReceived);

            if (messageReceived.empty())
            {
                break;
            }
        }
        else
        {
            if (EAGAIN == errno)
            {
                continue;
            }

            WaveNs::trace (TRACE_LEVEL_ERROR, "DatagramSocketReaderThread::serverDatagramTest : Failed to receive.");

            break;
        }
    }


    delete this;

    return (WAVE_THREAD_SUCCESS);
}

}
