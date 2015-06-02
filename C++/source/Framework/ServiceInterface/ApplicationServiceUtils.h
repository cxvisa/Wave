/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONSERVICEUTILS_H
#define APPLICATIONSERVICEUTILS_H

#include "Framework/Types/Types.h"
#include "Framework/ServiceInterface/ApplicationServiceHelper.h"
#include "Framework/ServiceInterface/ApplicationServiceInterface.h"

namespace WaveNs
{

class WaveObjectManager;
class PrismMessage;

typedef PrismApplicationServiceCallback ApplicationServiceCallback;

class ApplicationServiceSendContext
{
    private :
    protected :
    public :
                                    ApplicationServiceSendContext (ApplicationServiceCallback pApplicationServiceCallback, void *pApplicationServiceContext);
                                   ~ApplicationServiceSendContext ();

        ApplicationServiceCallback  getPApplicationServiceCallback ();
        void                       *getPApplicationServiceContext ();

    // Now the data members

    private :
        ApplicationServiceCallback  m_pApplicationServiceCallback;
        void                       *m_pApplicationServiceContext;

    protected :
    public :
};

class ApplicationServiceUtils
{
    private :
    protected :
    public :
        static PrismServiceId getPrismServiceIdForApplicationServiceId (const UI32 &applicationServiceId);
        static ResourceId     sendToApplicationService                 (const PrismServiceId &sendingApplicationServicePrismServiceId, void *pPayLoad, const UI32 &payLoadLength, const PrismServiceId &prismServiceId, const LocationId &prismLocationId, ApplicationServiceCallback pApplicationServiceCallback, void *pApplicationContext);
        static void           replyToApplicationService                (void *pOutputPayLoad, const UI32 outputPayLoadLength, void *pPrismContext);

    // Now the data members

    private :
    protected :
    public :
};

class ApplicationServiceMessageHandlerContext
{
    private :
    protected :
    public :
                            ApplicationServiceMessageHandlerContext (WaveObjectManager *pWaveObjectManager, PrismMessage *pPrismMessage);
                           ~ApplicationServiceMessageHandlerContext ();

        WaveObjectManager *getPWaveObjectManager                  ();
        PrismMessage       *getPPrismMessage                        ();

    // Now the data members

    private :
        WaveObjectManager *m_pWaveObjectManager;
        PrismMessage       *m_pPrismMessage;

    protected :
    public :
};

}

#endif // APPLICATIONSERVICEUTILS_H
