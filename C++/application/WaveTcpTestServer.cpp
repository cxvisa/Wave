/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/Types.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/ServerStreamingSocket.h"

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
using namespace WaveNs;

int main (int argc, char *argv[])
{
    int numberOfSuccessfulConnections = 0;

    ServerStreamingSocket *pServerStreamingSocket = new ServerStreamingSocket (3016, 1024);

    while (true)
    {
        ServerStreamingSocket *pNewConnectionSocket = new ServerStreamingSocket ();

        bool status = pServerStreamingSocket->accept (*pNewConnectionSocket);

        if (status)
        {
            numberOfSuccessfulConnections++;

            cout << numberOfSuccessfulConnections << endl;
        }
    }

    return (0);
}
