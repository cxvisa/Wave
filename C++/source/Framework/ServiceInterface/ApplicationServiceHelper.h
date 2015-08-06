/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONSERVICEHELPER_H
#define APPLICATIONSERVICEHELPER_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"
#include "Framework/ServiceInterface/ApplicationServiceInterface.h"
#include <map>

namespace WaveNs
{

class WaveMessage;

typedef PrismApplicationServiceMessageHandler ApplicationServiceMessageHandler;

class ApplicationServiceHelper
{
    private :
    protected :
    public :
        static void lock   ();
        static void unlock ();

        static UI32                                         getNextApplicationServiceId         ();
        static void                                         addMessageHandler                   (const UI32 &applicationServiceId, const UI32 &operationCode, ApplicationServiceMessageHandler handler);
        static map<UI32, ApplicationServiceMessageHandler> *getHandlersMapForApplicationService (const UI32 &applicationServiceId);

    // Now the data members

    private :
        static PrismMutex                                               m_applicationServiceHelperMutex;
        static UI32                                                     m_nextApplicationServiceId;
        static map<UI32, map<UI32, ApplicationServiceMessageHandler> *> m_allApplicationServiceMessageHandlersMap;

    protected :
    public :
};

}

#endif // APPLICATIONSERVICEHELPER_H
