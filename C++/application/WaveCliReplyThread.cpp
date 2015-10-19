/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "WaveCliReplyThread.h"
#include "Framework/Trace/TraceObjectManager.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"

namespace WaveNs
{

WaveCliReplyThread::WaveCliReplyThread (ManagementInterfaceMessage *pManagementInterfaceMessage)
    : WavePosixThread (),
      m_pManagementInterfaceMessage (pManagementInterfaceMessage)
{
}

WaveThreadStatus WaveCliReplyThread::start ()
{
    trace (TRACE_LEVEL_DEBUG, string ("WaveCliReplyThread::start \n\r"));

    UI32 noOfReply = 1000;
    UI32 i;
    bool lastReply;

    for (i = 0; i < noOfReply - 1; i++)
    {
        lastReply = false;
        m_pManagementInterfaceMessage->setIsLastReply (lastReply);
        WaveUserInterfaceObjectManager::replyToWaveServer (m_pManagementInterfaceMessage);
    }

    lastReply = true;

    m_pManagementInterfaceMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    m_pManagementInterfaceMessage->setIsLastReply (lastReply);
    WaveUserInterfaceObjectManager::replyToWaveServer (m_pManagementInterfaceMessage);

    delete this;

    return (WAVE_THREAD_SUCCESS);

}

}

