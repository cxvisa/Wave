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
class WaveMessage;

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
        static WaveServiceId getWaveServiceIdForApplicationServiceId (const UI32 &applicationServiceId);
        static ResourceId     sendToApplicationService                 (const WaveServiceId &sendingApplicationServiceWaveServiceId, void *pPayLoad, const UI32 &payLoadLength, const WaveServiceId &prismServiceId, const LocationId &prismLocationId, ApplicationServiceCallback pApplicationServiceCallback, void *pApplicationContext);
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
                            ApplicationServiceMessageHandlerContext (WaveObjectManager *pWaveObjectManager, WaveMessage *pWaveMessage);
                           ~ApplicationServiceMessageHandlerContext ();

        WaveObjectManager *getPWaveObjectManager                  ();
        WaveMessage       *getPWaveMessage                        ();

    // Now the data members

    private :
        WaveObjectManager *m_pWaveObjectManager;
        WaveMessage       *m_pWaveMessage;

    protected :
    public :
};

}

#endif // APPLICATIONSERVICEUTILS_H
