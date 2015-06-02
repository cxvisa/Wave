/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPINTERFACEGETWORKER_H
#define HTTPINTERFACEGETWORKER_H

#include "HttpInterface/HttpInterfaceMethodWorker.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class HttpInterfaceGetWorker : public HttpInterfaceMethodWorker
{
    private :
    protected :
    public :
                      HttpInterfaceGetWorker (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager);
        virtual      ~HttpInterfaceGetWorker ();
        virtual void  process                (const HttpRequest &httpRequest);

    // Now the data members

    private :
    protected :
    public :

};

}

#endif // HTTPINTERFACEGETWORKER_H
