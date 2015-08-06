/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/ApplicationServiceUtils.h"
#include "Framework/ServiceInterface/ApplicationServiceRepository.h"
#include "Framework/ServiceInterface/ApplicationService.h"
#include "Framework/ServiceInterface/ApplicationLocalService.h"
#include "Framework/ServiceInterface/ApplicationServiceMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

ApplicationServiceSendContext::ApplicationServiceSendContext (ApplicationServiceCallback pApplicationServiceCallback, void *pApplicationServiceContext)
    : m_pApplicationServiceCallback (pApplicationServiceCallback),
      m_pApplicationServiceContext  (pApplicationServiceContext)
{
}

ApplicationServiceSendContext::~ApplicationServiceSendContext ()
{
}

ApplicationServiceCallback  ApplicationServiceSendContext::getPApplicationServiceCallback ()
{
    return (m_pApplicationServiceCallback);
}

void *ApplicationServiceSendContext::getPApplicationServiceContext ()
{
    return (m_pApplicationServiceContext);
}

ApplicationServiceMessageHandlerContext::ApplicationServiceMessageHandlerContext (WaveObjectManager *pWaveObjectManager, PrismMessage *pPrismMessage)
    : m_pWaveObjectManager (pWaveObjectManager),
     m_pPrismMessage        (pPrismMessage)
{
}

ApplicationServiceMessageHandlerContext::~ApplicationServiceMessageHandlerContext ()
{
}

WaveObjectManager *ApplicationServiceMessageHandlerContext::getPWaveObjectManager ()
{
    return (m_pWaveObjectManager);
}

PrismMessage *ApplicationServiceMessageHandlerContext::getPPrismMessage ()
{
    return (m_pPrismMessage);
}

WaveServiceId ApplicationServiceUtils::getWaveServiceIdForApplicationServiceId (const UI32 &applicationServiceId)
{
    WaveServiceId                applicationServiceWaveServiceId = 0;
    ApplicationServiceRepository *pApplicationServiceRepository    = NULL;

    ApplicationServiceHelper::lock ();

    pApplicationServiceRepository = ApplicationServiceRepository::getInstance ();

    if (true == (pApplicationServiceRepository->isAnApplicationLocalService (applicationServiceId)))
    {
        ApplicationLocalService *pApplicationLocalService = pApplicationServiceRepository->getApplicationLocalService (applicationServiceId);

        prismAssert (NULL != pApplicationLocalService, __FILE__, __LINE__);

        applicationServiceWaveServiceId = pApplicationLocalService->getServiceId ();
    }
    else
    {
        ApplicationService *pApplicationService = pApplicationServiceRepository->getApplicationService (applicationServiceId);

        prismAssert (NULL != pApplicationService, __FILE__, __LINE__);

        applicationServiceWaveServiceId = pApplicationService->getServiceId ();
    }

    ApplicationServiceHelper::unlock ();

    return (applicationServiceWaveServiceId);
}

ResourceId ApplicationServiceUtils::sendToApplicationService (const WaveServiceId &sendingApplicationWaveServiceId, void *pPayLoad, const UI32 &payLoadLength, const WaveServiceId &receivingApplicationprismServiceId, const LocationId &prismLocationId, ApplicationServiceCallback pApplicationServiceCallback, void *pApplicationContext)
{
    ApplicationServiceMessage *pApplicationServiceMessage = new ApplicationServiceMessage (getWaveServiceIdForApplicationServiceId (receivingApplicationprismServiceId));
    ResourceId                 status                     = WAVE_MESSAGE_ERROR;

    if (NULL != pPayLoad)
    {
        pApplicationServiceMessage->addBuffer (APPLICATION_SERVICE_GENERIC_MESSAGE_INPUT_BUFFER1, payLoadLength, pPayLoad, false);
    }

    ApplicationServiceRepository *pApplicationServiceRepository = NULL;

    ApplicationServiceHelper::lock ();

    pApplicationServiceRepository = ApplicationServiceRepository::getInstance ();

    prismAssert (NULL != pApplicationServiceRepository, __FILE__, __LINE__);

    ApplicationServiceSendContext *pApplicationServiceSendContext = new ApplicationServiceSendContext (pApplicationServiceCallback, pApplicationContext);

    prismAssert (NULL != pApplicationServiceSendContext, __FILE__, __LINE__);

    if (true == (pApplicationServiceRepository->isAnApplicationLocalService (sendingApplicationWaveServiceId)))
    {
        ApplicationLocalService *pApplicationLocalService = pApplicationServiceRepository->getApplicationLocalService (sendingApplicationWaveServiceId);

        prismAssert (NULL != pApplicationLocalService, __FILE__, __LINE__);

        status = pApplicationLocalService->send (pApplicationServiceMessage, reinterpret_cast<PrismMessageResponseHandler> (&ApplicationLocalService::applicationLocalServiceMessageCallback), pApplicationServiceSendContext, 0, prismLocationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("ApplicationServiceUtils::sendToApplicationService : Could not send message to Application Service : ") + FrameworkToolKit::localize (status));
        }
    }
    else
    {
        ApplicationService *pApplicationService = pApplicationServiceRepository->getApplicationService (sendingApplicationWaveServiceId);

        prismAssert (NULL != pApplicationService, __FILE__, __LINE__);

        status = pApplicationService->send (pApplicationServiceMessage, reinterpret_cast<PrismMessageResponseHandler> (&ApplicationService::applicationServiceMessageCallback), pApplicationServiceSendContext, 0, prismLocationId);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, string ("ApplicationServiceUtils::sendToApplicationService : Could not send message to Application Service : ") + FrameworkToolKit::localize (status));
        }
    }

    ApplicationServiceHelper::unlock ();

    return (status);
}

void ApplicationServiceUtils::replyToApplicationService (void *pOutputPayLoad, const UI32 outputPayLoadLength, void *pPrismContext)
{
    ApplicationServiceMessageHandlerContext *pApplicationServiceMessageHandlerContext = reinterpret_cast<ApplicationServiceMessageHandlerContext *> (pPrismContext);

    prismAssert (NULL != pApplicationServiceMessageHandlerContext, __FILE__, __LINE__);

    WaveObjectManager *pWaveObjectManager = pApplicationServiceMessageHandlerContext->getPWaveObjectManager ();
    PrismMessage       *pPrismMessage       = pApplicationServiceMessageHandlerContext->getPPrismMessage ();

    prismAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);
    prismAssert (NULL != pPrismMessage,       __FILE__, __LINE__);

    if (NULL != pOutputPayLoad)
    {
        pPrismMessage->addBuffer (APPLICATION_SERVICE_GENERIC_MESSAGE_OUTPUT_BUFFER1, outputPayLoadLength, pOutputPayLoad, false);
    }

    pPrismMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);

    pWaveObjectManager->reply (pPrismMessage);
}

}
