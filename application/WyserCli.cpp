/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka, Jayanth Venkataraman              *
 ***************************************************************************/

#include "SystemManagement/CommandLineInterface/Client/WaveCommandLineInterface.h"
#include "Framework/Utils/FrameworkToolKit.h"

using namespace WaveNs;

void displayUsage (const char *pProgramName)
{
    cout << "USAGE:" << endl;
    cout << pProgramName << endl;
    cout << "    -cliport <port number> - Cli port number of DCMd instance to connect to" << endl;
    cout << endl;
}

int main (int argc, char *argv[])
{
    UI32    cliPortNumber   = FrameworkToolKit::FrameworkToolKit::getCommandLineInterfaceReceiverPort ();
    string  cliIpAddress    = "127.0.0.1";

    // Get the command line options
    for (SI32 i=1; i < argc; i++)
    {
        if ((0 == strcasecmp ("-cliport", argv[i])))
        {
            if ((i+1) < argc)
            {
                cliPortNumber = atoi (argv[i+1]);
            }
            i++;
        }
        else
        {
            displayUsage (argv[0]);
            return (1);
        }
    }

    WaveCommandLineInterface waveCommandLineInterface (cliIpAddress, cliPortNumber);

    return (0);
}
