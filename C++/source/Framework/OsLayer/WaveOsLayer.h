/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOSLAYER_H
#define WAVEOSLAYER_H

#include <unistd.h>
#include <sys/time.h>
#include <syslog.h>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include "Framework/Trace/TraceTypes.h"
#include "WaveResourceIdEnums.h"

using namespace std;

namespace WaveNs
{

unsigned int  waveSleep                 (unsigned int numberOfSecondsToSleep);
unsigned int  waveUSleep                (unsigned int numberOfMicroSecondsToSleep);
void          waveSysLog                (const char * const pStringToLog);
void          initializeWaveSocketLayer ();
void          getIpAddressesForThisHost  (vector<string> &ipAddressesForThisHost);
string        getIpAddressForInterface   (const string &interfaceName);
int           waveCloseSocket           (int fd);
void          waveBlockSignals          ();
void          waveInstallSigIntHandler  ();
char         *waveGetCwd                (char *buf, size_t size);
void          waveCreateWaitableTimer   ();
void          waveWaitForAlarmSignal    ();
int           waveSetITimer             (struct itimerval *pItimerValue);
void          waveSetConsoleTextColor   (TraceLevel requestedTraceLevel);
void          waveResetConsoleTextColor ();
string        getIPv6AddressForInterface (const string &interfaceName);
string        getStateForInterface       (const string &interfaceName);

}

#endif // WAVEOSLAYER_H

