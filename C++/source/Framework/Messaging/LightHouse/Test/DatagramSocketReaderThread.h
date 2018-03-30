/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATAGRAMSOCKETREADERTHREAD_H
#define DATAGRAMSOCKETREADERTHREAD_H

#include "Framework/MultiThreading/WavePosixThread.h"

namespace WaveNs
{

class ServerDatagramSocket;

class DatagramSocketReaderThread : public WavePosixThread
{
    private :
    protected :
    public :
                                  DatagramSocketReaderThread (ServerDatagramSocket *pServerDatagramSocket);
        virtual                  ~DatagramSocketReaderThread ();

        virtual WaveThreadStatus  start                      ();

        // Now the data members

    private :
        ServerDatagramSocket *m_pServerDatagramSocket;

    protected :
    public :
};

}

#endif // DATAGRAMSOCKETREADERTHREAD_H
