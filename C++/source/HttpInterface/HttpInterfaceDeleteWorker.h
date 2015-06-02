/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPINTERFACEDELETEWORKER_H
#define HTTPINTERFACEDELETEWORKER_H

#include "HttpInterface/HttpInterfaceMethodWorker.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class HttpInterfaceDeleteWorker : public HttpInterfaceMethodWorker
{
    private :
    protected :
    public :
                      HttpInterfaceDeleteWorker (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager);
        virtual      ~HttpInterfaceDeleteWorker ();
        virtual void  process                   (const HttpRequest &httpRequest);

    // Now the data members

    private :
    protected :
    public :

};

}

#endif // HTTPINTERFACEDELETEWORKER_H
