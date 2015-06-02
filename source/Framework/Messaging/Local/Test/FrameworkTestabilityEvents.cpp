/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/Test/FrameworkTestabilityEvents.h"
#include "Framework/Messaging/Local/Test/FrameworkLocalMessagingTestObjectManager.h"

namespace WaveNs
{

FrameworkTestabilityEvent1::FrameworkTestabilityEvent1 ()
    : PrismEvent (FrameworkLocalMessagingTestObjectManager::getPrismServiceId (), FRAMEWORK_MESSAGING_LOCAL_TEST_EVENT1)
{
    m_eventUI32  = 0;
}

FrameworkTestabilityEvent1::~FrameworkTestabilityEvent1 ()
{
}

void FrameworkTestabilityEvent1::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32   (&m_eventUI32,       "eventUI32"));
     addSerializableAttribute (new AttributeString (&m_eventString,     "eventString"));
}

UI32 FrameworkTestabilityEvent1::getEventUI32 () const
{
    return (m_eventUI32);
}

void FrameworkTestabilityEvent1::setEventUI32 (const UI32 &eventUI32)
{
    m_eventUI32 = eventUI32;
}

string FrameworkTestabilityEvent1::getEventString () const
{
    return (m_eventString);
}

void FrameworkTestabilityEvent1::setEventString (const string &eventString)
{
    m_eventString = eventString;
}

}
