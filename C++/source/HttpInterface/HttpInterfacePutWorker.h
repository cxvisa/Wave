/***************************************************************************
*   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Vidyasagara Reddy Guntaka                                    *
***************************************************************************/

#ifndef HTTPINTERFACEPUTWORKER_H
#define HTTPINTERFACEPUTWORKER_H

#include "HttpInterface/HttpInterfaceMethodWorker.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class HttpInterfacePutWorker : public HttpInterfaceMethodWorker
{
    private :
    protected :
    public :
                      HttpInterfacePutWorker (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager);
        virtual      ~HttpInterfacePutWorker ();
        virtual void  process                (const HttpRequest &httpRequest);

    // Now the data members

    private :
    protected :
    public :

};

}

#endif // HTTPINTERFACEPUTWORKER_H
