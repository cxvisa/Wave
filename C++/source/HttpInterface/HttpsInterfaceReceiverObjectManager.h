/**************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPSINTERFACERECEIVEROBJECTMANAGER_H
#define HTTPSINTERFACERECEIVEROBJECTMANAGER_H

#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"

namespace WaveNs
{

class HttpsInterfaceReceiverObjectManager : public HttpInterfaceReceiverObjectManager
{
    private :
        HttpsInterfaceReceiverObjectManager ();

    protected :
        virtual bool getIsTranportSecurityEnabled () const;
        virtual SI32 getInterfaceReceiverPort     () const;

    public :
        virtual                                    ~HttpsInterfaceReceiverObjectManager ();

        static  string                              getServiceName                      ();
        static HttpsInterfaceReceiverObjectManager *getInstance                         ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // HTTPSINTERFACERECEIVEROBJECTMANAGER_H
