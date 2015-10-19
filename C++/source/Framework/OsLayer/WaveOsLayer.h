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

unsigned int  prismSleep                 (unsigned int numberOfSecondsToSleep);
unsigned int  prismUSleep                (unsigned int numberOfMicroSecondsToSleep);
void          prismSysLog                (const char * const pStringToLog);
void          initializeWaveSocketLayer ();
void          getIpAddressesForThisHost  (vector<string> &ipAddressesForThisHost);
string        getIpAddressForInterface   (const string &interfaceName);
int           prismCloseSocket           (int fd);
void          prismBlockSignals          ();
void          prismInstallSigIntHandler  ();
char         *prismGetCwd                (char *buf, size_t size);
void          prismCreateWaitableTimer   ();
void          prismWaitForAlarmSignal    ();
int           prismSetITimer             (struct itimerval *pItimerValue);
void          prismSetConsoleTextColor   (TraceLevel requestedTraceLevel);
void          prismResetConsoleTextColor ();
string        getIPv6AddressForInterface (const string &interfaceName);
string        getStateForInterface       (const string &interfaceName);

}

#endif // WAVEOSLAYER_H

