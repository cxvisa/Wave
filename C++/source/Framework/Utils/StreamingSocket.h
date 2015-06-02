/******* ********************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef STREAMINGSOCKET_H
#define STREAMINGSOCKET_H

#include "Framework/Utils/StreamingSocketBase.h"
#include <sys/types.h>
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class StreamingSocket : public StreamingSocketBase
{
    private :
    protected :
    public :
                       StreamingSocket                    (const SI32 maximumNumberOfConnections);
                       StreamingSocket                    ();
        virtual       ~StreamingSocket                    ();

                bool   setTcpNoDelay                      ();
                bool   clearTcpNoDelay                    ();
                bool   setTcpCork                         ();
                bool   clearTcpCork                       ();
                bool   setTcpSendTimeout                  (UI32 timeoutInMilliSeconds);
                bool   clearTcpSendTimeout                ();

                // Note : following methods do not have any corresponding reseting methods.
                // Also, the values timeoutInMilliSeconds should be greater than 1000.
                bool   setTcpKeepAliveIdleTimeout         (UI32 timeoutInMilliSeconds);
                bool   setTcpKeepAliveProbeInterval       (UI32 timeoutInMilliSeconds);
                bool   setTcpKeepAliveProbeCount          (UI32 numberOfProbes);

        virtual bool   bind                               (const SI32 port);
        virtual bool   accept                             (StreamingSocketBase &newStreamingSocketBase);
        virtual bool   connect                            (const string &host, const SI32 port);

        virtual string getSourceIpAddress                 ();
        virtual string getPeerIpAddress                   ();
        virtual SI32   getPeerPort                        ();
        static  string getAPublicIpAddressForThisMachine  ();
        static  void   getPublicIpAddressesForThisMachine (vector<string> &ipAddressesVector);
        static  string getIpAddressForInterface           (const string &interfaceName);

                void   close                              (void);

    // Now the data members

    private :
        sockaddr_in m_socketAddress;

    protected :
    public :
};

}

#endif //STREAMINGSOCKET_H
