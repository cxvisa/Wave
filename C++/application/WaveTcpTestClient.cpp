/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/Types.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/ClientStreamingSocket.h"

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
    char response;

    for (int i = 1025; i < 65535; i++)
    {
        ClientStreamingSocket *pClientStreamingSocket = new ClientStreamingSocket (argv[1], 3016, 1);

        if (pClientStreamingSocket->getIsConnected ())
        {
            numberOfSuccessfulConnections++;
        }
    }

    cout << numberOfSuccessfulConnections << endl;

    cout << "Waiting to terminate ... ";
    cin >> response;

    return (0);
}
