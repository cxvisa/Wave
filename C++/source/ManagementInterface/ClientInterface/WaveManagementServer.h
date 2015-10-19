/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEMENTSERVER_H
#define WAVEMANAGEMENTSERVER_H

#include "Framework/Types/Types.h"

#include <string>
#include <map>

using namespace std;

namespace WaveNs
{

class ClientStreamingSocket;
class ManagementInterfaceMessage;

class WaveManagementServer
{
    private :
    protected :
    public :
                        WaveManagementServer            (const string &waveClientName, const string &waveClientNameWithoutExtension, const string &ipAddress, const SI32 &port);
                       ~WaveManagementServer            ();

        ResourceId      connect                         (const UI32 &numberOfRetries = 0, const UI32 &maximumNumberOfSecondsToTryFor = 0);
        void            indicateClosing                 ();

        UI32            getId                           () const;
        string          getIpAddress                    () const;
        SI32            getPort                         () const;
        bool            operator <<                     (ManagementInterfaceMessage *pManagementInterfaceMessage);
        void            addServiceCache                 (const vector<string> &serviceNames, const vector<UI32> &serviceIds);
        WaveServiceId  getWaveServiceIdForServiceName (const string &serviceName);
        string          getWaveServiceNameForServiceId (const WaveServiceId &serviceId);

        UI32            getServerUniqueIdentifier       () const;

        void            updateMessageVersionAndSerializationTypeForSocket (const string& msgVersion);
        
    // Now the Data Members

    private :
        UI32                   m_id;
        string                 m_waveClientName;
        string                 m_waveClientNameWithoutExtension;
        string                 m_ipAddress;
        SI32                   m_port;
        ClientStreamingSocket *m_pClientStreamingSocket;

        vector<string>         m_serviceNames;
        vector<UI32>           m_serviceIds;
        map<string, UI32>      m_serviceMapByName;
        map<UI32, string>      m_serviceMapById;
        UI32                   m_serverUniqueIdentifier;

    protected :
    public :
};

}

#endif // WAVEMANAGEMENTSERVER_H
