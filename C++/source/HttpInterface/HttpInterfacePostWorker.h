/***************************************************************************
*   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Vidyasagara Reddy Guntaka                                    *
***************************************************************************/

#ifndef HTTPINTERFACEPOSTWORKER_H
#define HTTPINTERFACEPOSTWORKER_H

#include "HttpInterface/HttpInterfaceMethodWorker.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class HttpInterfacePostWorker : public HttpInterfaceMethodWorker
{
    private :
    protected :
    public :
                      HttpInterfacePostWorker (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager);
        virtual      ~HttpInterfacePostWorker ();
        virtual void  process                 (const HttpRequest &httpRequest);

    // Now the data members

    private :
    protected :
    public :

};

}

#endif // HTTPINTERFACEPOSTWORKER_H
