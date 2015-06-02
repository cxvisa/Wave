/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UNIXDOMAINSTREAMINGSOCKET_H
#define UNIXDOMAINSTREAMINGSOCKET_H

#include "Framework/Utils/StreamingSocketBase.h"
#include <sys/types.h>
#include <string>

namespace WaveNs
{

class UnixDomainStreamingSocket : public StreamingSocketBase
{
    private :
    protected :
    public :
                       UnixDomainStreamingSocket          (const SI32 maximumNumberOfConnections);
                       UnixDomainStreamingSocket          ();
        virtual       ~UnixDomainStreamingSocket          ();

        virtual bool   bind                               (const SI32 port);
        virtual bool   accept                             (StreamingSocketBase &newStreamingSocketBase);
        virtual bool   connect                            (const string &host, const SI32 port);

/*
        virtual string getSourceIpAddress                 ();
        virtual string getPeerIpAddress                   ();
        virtual SI32   getPeerPort                        ();
        static  string getAPublicIpAddressForThisMachine  ();
        static  void   getPublicIpAddressesForThisMachine (vector<string> &ipAddressesVector);
        static  string getIpAddressForInterface           (const string &interfaceName);
*/
    // Now the data members

    private :
        sockaddr_un m_socketAddress;

        static const string serverPathPrefix;

    protected :
    public :
};

}

#endif // UNIXDOMAINSTREAMINGSOCKET_H
