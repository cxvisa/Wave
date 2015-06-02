/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/MessagingBus/WaveMessagingBus.h"

namespace WaveNs
{

WaveMessagingBus::WaveMessagingBus (const string &name)
    : m_name (name)
{
}

WaveMessagingBus::~WaveMessagingBus ()
{
}

string WaveMessagingBus::getName () const
{
    return (m_name);
}

void WaveMessagingBus::setName (const string &name)
{
    m_name = name;
}

}
