/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEMENTCLIENTMAP_H
#define WAVEMANAGEMENTCLIENTMAP_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"

#include <string>
#include <map>

using namespace std;

namespace WaveNs
{

class WaveManagementClient;
class ManagementInterfaceMessage;

class WaveManagementClientMap
{
    private :
    protected :
    public :
                              WaveManagementClientMap ();
                             ~WaveManagementClientMap ();

        bool                  isAKnownClient          (const string &name);
        bool                  isAKnownClient          (const string &ipAddress, const UI32 &port);
        bool                  isAKnownClient          (const UI32 &id);
        void                  addClient               (WaveManagementClient *pWaveManagementClient);
        WaveManagementClient *removeClient            (const string &ipAddress, const UI32 &port);
        WaveManagementClient *removeClient            (const UI32 &id);
        WaveManagementClient *getClient               (const string &ipAddress, const UI32 &port);
        UI32                  getClientId             (const string &ipAddress, const UI32 &port);
        UI32                  getClientId             (const string &name);
        WaveManagementClient *getClient               (const UI32 &id);
        WaveManagementClient *getClient               (const string &name);
        vector<WaveManagementClient *> *removeAllClient (const string &ipAddress);
        ResourceId            post                    (ManagementInterfaceMessage *pManagementInterfaceMessage);
        vector<string>        getClientsConnected     () const;

    // Now the Data Members

    private :
        map<string, WaveManagementClient *> m_managementClientsByName;
        map<string, WaveManagementClient *> m_managementClients;
        map<UI32,   WaveManagementClient *> m_managementClientsById;
        map<UI32,   string>                 m_clientMessageVersionById;
        WaveMutex                          m_managementClientsMutex;

    protected :
    public :
};

}

#endif // WAVEMANAGEMENTCLIENTMAP_H
