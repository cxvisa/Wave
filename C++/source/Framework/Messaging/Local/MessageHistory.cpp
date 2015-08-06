/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mandar Datar                                                 *
 ***************************************************************************/

#include "Framework/Messaging/Local/MessageHistory.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

#include <sys/time.h>

namespace WaveNs
{

MessageHistory::MessageHistory (WaveMessage *pWaveMessage, WaveMessageSendType sendType, WaveMessageHistoryLogType messageHistoryLogType)
{
    m_originalMessageId     = pWaveMessage->getMessageIdAtOriginatingLocation ();
    m_type                  = pWaveMessage->getType ();
    m_destinationLocationID = pWaveMessage->getReceiverLocationId ();
    m_destinationServiceId  = pWaveMessage->getServiceCode ();
    m_opcode                = pWaveMessage->getOperationCode ();
    m_completionStatus      = pWaveMessage->getCompletionStatus ();
    m_sendType              = sendType;
    m_messageHistoryLogType = messageHistoryLogType;

    struct timeval tv       = {0};
    int returnValue         = gettimeofday (&tv, NULL);

    if (0 == returnValue)
    {
        m_timeInSeconds = tv.tv_sec;
        m_microSeconds  = tv.tv_usec;

        // trace (TRACE_LEVEL_SUCCESS, string ("MessageHistory::MessageHistory : m_timeInSeconds [") + m_timeInSeconds + string ("], m_microSeconds [") + m_microSeconds + string ("]"));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string ("MessageHistory::MessageHistory : gettimeofday returned [") + returnValue + string ("]"));
        waveAssert (false, __FILE__, __LINE__);
    }
}

MessageHistory::~MessageHistory ()
{

}

void MessageHistory::getMessageHistoryString (string &debugHistoryString)
{
    const UI32 bufferSize                     = 1000;
          char debugHistoryBuffer[bufferSize] = {0};
    const char *messageTypeString             = "UNKNOWN";
    const char *messageSendTypeString         = "UNKNOWN";
    const char *messageHistoryLogTypeString   = "UNKNOWN";

    switch (m_type)
    {
        case WAVE_MESSAGE_TYPE_REQUEST :
            messageTypeString       = "REQUEST";
            break;
        case WAVE_MESSAGE_TYPE_RESPONSE :
            messageTypeString       = "RESPONS";
            break;
        // // Logging events is not done.
        // case WAVE_MESSAGE_TYPE_EVENT :
        //     messageTypeString       = "EVENT  ";
        //     break;
        default :
            messageTypeString       = "UNKNOWN";
    }

    switch (m_sendType)
    {
        case WAVE_MESSAGE_SEND_TYPE_ONEWAY :
            messageSendTypeString     = "ONEWAY ";
            break;
        case WAVE_MESSAGE_SEND_TYPE_SYNCHRONOUS :
            messageSendTypeString     = "SYNC   ";
            break;
        case WAVE_MESSAGE_SEND_TYPE_ASYNCHRONOUS :
            messageSendTypeString     = "ASYNC  ";
            break;
        default :
            messageSendTypeString     = "UNKNOWN";
    }

    switch (m_messageHistoryLogType)
    {
        case WAVE_MESSAGE_HISTORY_LOG_AT_SEND :
            messageHistoryLogTypeString = "SENT   ";
            break;
        case WAVE_MESSAGE_HISTORY_LOG_AT_REPLY :
            messageHistoryLogTypeString = "REPLIED";
            break;
        case WAVE_MESSAGE_HISTORY_LOG_AT_HANDLE :
            messageHistoryLogTypeString = "HANDLE ";
            break;
        default :
            messageHistoryLogTypeString = "UNKNOWN";
    }

    char   timeStampString[64];
    // use the tread safe version
    ctime_r (&m_timeInSeconds, timeStampString);
    //Remove the new line character at the end
    timeStampString[(strlen (timeStampString)) - 1] = '\0';

    snprintf (debugHistoryBuffer, bufferSize, "%s - %06u |Id: %8u |Service: %4u |Op: %10u |Loc: %4u |type: %s |sendType: %s|%s", timeStampString, m_microSeconds, m_originalMessageId, m_destinationServiceId, m_opcode, m_destinationLocationID, messageTypeString, messageSendTypeString, messageHistoryLogTypeString);
    debugHistoryString.append (debugHistoryBuffer);

    // put completion status in case of reply.
    if ((WAVE_MESSAGE_HISTORY_LOG_AT_REPLY == m_messageHistoryLogType) || (WAVE_MESSAGE_TYPE_RESPONSE == m_type))
    {
        debugHistoryString.append (" (");
        debugHistoryString.append (FrameworkToolKit::localize(m_completionStatus));
        debugHistoryString.append (")");
    }
}

}

