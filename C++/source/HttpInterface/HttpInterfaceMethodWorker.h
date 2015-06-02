/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPINTERFACEMETHODWORKER_H
#define HTTPINTERFACEMETHODWORKER_H

#include <Framework/ObjectModel/WaveWorker.h>
#include "Framework/Utils/ServerStreamingSocket.h"
#include "HttpInterface/HttpRequest.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class HttpInterfaceMethodWorker : public WaveWorker
{
    private :
    protected :
    public :
                                         HttpInterfaceMethodWorker  (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const WaveHttpInterfaceMethod &waveHttpInterfaceMethod);
        virtual                         ~HttpInterfaceMethodWorker  ();

        virtual void                     process                    (const HttpRequest &httpRequest) = 0;

                WaveHttpInterfaceMethod  getWaveHttpInterfaceMethod () const;

    // Now the data members

    private :
        WaveHttpInterfaceMethod m_waveHttpInterfaceMethod;

    protected :
    public :

    
};

}

#endif // HTTPINTERFACEMETHODWORKER_H
