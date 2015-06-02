/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/ApplicationServiceHelper.h"

namespace WaveNs
{

PrismMutex                                               ApplicationServiceHelper::m_applicationServiceHelperMutex;
UI32                                                     ApplicationServiceHelper::m_nextApplicationServiceId                 = 1;
map<UI32, map<UI32, ApplicationServiceMessageHandler> *> ApplicationServiceHelper::m_allApplicationServiceMessageHandlersMap;

void ApplicationServiceHelper::lock ()
{
    m_applicationServiceHelperMutex.lock ();
}

void ApplicationServiceHelper::unlock ()
{
    m_applicationServiceHelperMutex.unlock ();
}

UI32 ApplicationServiceHelper::getNextApplicationServiceId ()
{
    UI32 nextApplicationServiceId = m_nextApplicationServiceId;

    m_nextApplicationServiceId++;

    return (nextApplicationServiceId);
}

void ApplicationServiceHelper::addMessageHandler (const UI32 &applicationServiceId, const UI32 &operationCode, ApplicationServiceMessageHandler handler)
{
    map<UI32, map<UI32, ApplicationServiceMessageHandler> *>::iterator element    = m_allApplicationServiceMessageHandlersMap.find (applicationServiceId);
    map<UI32, map<UI32, ApplicationServiceMessageHandler> *>::iterator endElement = m_allApplicationServiceMessageHandlersMap.end ();

    if (element == endElement)
    {
        m_allApplicationServiceMessageHandlersMap[applicationServiceId] = new map<UI32, ApplicationServiceMessageHandler>;
    }

    (*(m_allApplicationServiceMessageHandlersMap[applicationServiceId]))[operationCode] = handler;
}

map<UI32, ApplicationServiceMessageHandler> *ApplicationServiceHelper::getHandlersMapForApplicationService (const UI32 &applicationServiceId)
{
    map<UI32, map<UI32, ApplicationServiceMessageHandler> *>::iterator element    = m_allApplicationServiceMessageHandlersMap.find (applicationServiceId);
    map<UI32, map<UI32, ApplicationServiceMessageHandler> *>::iterator endElement = m_allApplicationServiceMessageHandlersMap.end ();

    if (element == endElement)
    {
        return (NULL);
    }
    else
    {
        return (m_allApplicationServiceMessageHandlersMap[applicationServiceId]);
    }
}

}
