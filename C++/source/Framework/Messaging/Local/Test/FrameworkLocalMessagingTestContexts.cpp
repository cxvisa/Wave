/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestContexts.h"

namespace WaveNs
{

FrameworkLocalMessagingTestContext::FrameworkLocalMessagingTestContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pWaveMessage, pPrismElement, pSteps, numberOfSteps),
      m_remoteLocationId          (0),
      m_numberOfMessagesToSend    (0),
      m_numberOfMessagesSend      (0)
{
}

FrameworkLocalMessagingTestContext::~FrameworkLocalMessagingTestContext ()
{
}

LocationId FrameworkLocalMessagingTestContext::getRemoteLocationId ()
{
    return (m_remoteLocationId);
}

void FrameworkLocalMessagingTestContext::setRemoteLocationId (const LocationId &remoteLocationId)
{
    m_remoteLocationId = remoteLocationId;
}

void FrameworkLocalMessagingTestContext::setNumberOfMessagesToSend (const UI32 &numberOfMessagesToSend)
{
    m_numberOfMessagesToSend = numberOfMessagesToSend;
}

UI32 FrameworkLocalMessagingTestContext::getNumberOfMessagesToSend ()
{
    return (m_numberOfMessagesToSend);
}

void FrameworkLocalMessagingTestContext::incrementNumberOfMessagesSend ()
{
    ++m_numberOfMessagesSend;
}

void FrameworkLocalMessagingTestContext::resetNumberOfMessagesSend ()
{
    m_numberOfMessagesSend = 0;
}

UI32 FrameworkLocalMessagingTestContext::getNumberOfMessagesSend ()
{
    return (m_numberOfMessagesSend);
}

bool FrameworkLocalMessagingTestContext::areAllMessagesSent ()
{
    if (m_numberOfMessagesSend == m_numberOfMessagesToSend)
    {
        return true;
    }

    return false;
}

}
