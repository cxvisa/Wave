/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONSERVICE_H
#define APPLICATIONSERVICE_H

#include "Framework/Utils/PrismMutex.h"
#include "Framework/ServiceInterface/ApplicationServiceRepository.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ServiceInterface/ApplicationServiceHelper.h"

namespace WaveNs
{

class ApplicationServiceMessage;

class ApplicationService : public WaveObjectManager
{
    private :
                              ApplicationService                (const string &applicationServiceName, const UI32 &applicationServiceId);

        virtual PrismMessage *createMessageInstance             (const UI32 &operationCode);

                void          applicationServiceMessageHandler  (ApplicationServiceMessage *pApplicationServiceMessage);
                void          applicationServiceMessageCallback (FrameworkStatus frameworkStatus, ApplicationServiceMessage *pApplicationServiceMessage, void *pContext);

    protected :
    public :
        virtual       ~ApplicationService                       ();

        static  UI32  registerNewApplicationService             (const string &newApplicationServiceName);
        static  void  createNewApplicationServices              ();
        static  void  addMessageHandler                         (const UI32 &applicationServiceId, const UI32 &operationCode, ApplicationServiceMessageHandler handler);

                void  addMessageHandlerToThisApplicationService (const UI32 &operationCode, ApplicationServiceMessageHandler handler);

    // Now the data members

    private :
        static ApplicationServiceRepository                *m_pApplicationServiceRepository;

               UI32                                         m_applicationServiceId;
               map<UI32, ApplicationServiceMessageHandler>  m_applicaionServiceMessageHandlersMap;

    protected :
    public :

    friend class ApplicationServiceRepository;
    friend class ApplicationServiceUtils;
};

}

#endif // APPLICATIONSERVICE_H
