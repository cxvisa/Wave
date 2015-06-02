/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPINTERFACERECEIVERTHREAD_H
#define HTTPINTERFACERECEIVERTHREAD_H

#include <Framework/MultiThreading/PrismPosixThread.h>

namespace WaveNs
{

class ServerStreamingSocket;

class HttpInterfaceReceiverThread : public PrismPosixThread
{
    private :
        virtual WaveThreadStatus start ();

    protected :
    public :
                 HttpInterfaceReceiverThread (ServerStreamingSocket *pServerStreamingSocket);
        virtual ~HttpInterfaceReceiverThread ();

    // Now the data members

    private :
        ServerStreamingSocket *m_pServerStreamingSocket;

    protected :
    public :
};

}

#endif // HTTPINTERFACERECEIVERTHREAD_H
