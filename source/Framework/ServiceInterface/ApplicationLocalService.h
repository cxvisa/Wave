/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONLOCALSERVICE_H
#define APPLICATIONLOCALSERVICE_H

#include "Framework/Utils/PrismMutex.h"
#include "Framework/ServiceInterface/ApplicationServiceRepository.h"
#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/ServiceInterface/ApplicationServiceHelper.h"

namespace WaveNs
{

class ApplicationServiceMessage;

class ApplicationLocalService : public WaveLocalObjectManager
{
    private :
                              ApplicationLocalService               (const string &applicationServiceName, const UI32 &applicationLocalServiceId);

        virtual PrismMessage *createMessageInstance                 (const UI32 &operationCode);

                void          applicationLocalServiceMessageHandler  (ApplicationServiceMessage *pApplicationServiceMessage);
                void          applicationLocalServiceMessageCallback (FrameworkStatus frameworkStatus, ApplicationServiceMessage *pApplicationServiceMessage, void *pContext);

    protected :
    public :
        virtual       ~ApplicationLocalService                        ();

        static  UI32   registerNewApplicationLocalService             (const string &newApplicationLocalServiceName);
        static  void   createNewApplicationLocalServices              ();
        static  void   addMessageHandler                              (const UI32 &applicationServiceId, const UI32 &operationCode, ApplicationServiceMessageHandler handler);

                void   addMessageHandlerToThisApplicationLocalService (const UI32 &operationCode, ApplicationServiceMessageHandler handler);

    // Now the data members

    private :
        static ApplicationServiceRepository                *m_pApplicationServiceRepository;

               UI32                                         m_applicationLocalServiceId;
               map<UI32, ApplicationServiceMessageHandler>  m_applicaionLocalServiceMessageHandlersMap;

    protected :
    public :

    friend class ApplicationServiceRepository;
    friend class ApplicationServiceUtils;
};

}

#endif // APPLICATIONLOCALSERVICE_H
