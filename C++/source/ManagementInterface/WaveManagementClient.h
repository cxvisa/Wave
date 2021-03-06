/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEMENTCLIENT_H
#define WAVEMANAGEMENTCLIENT_H

#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class ClientStreamingSocket;
class ManagementInterfaceMessage;

class WaveManagementClient
{
    private :
    protected :
    public :
                        WaveManagementClient      (const string &name, const string &ipAddress, const SI32 &port, const WaveServiceId &userInterfaceServiceId);
                       ~WaveManagementClient      ();

        ResourceId      connect                   (const string &serverIpAddressFromClientPerspective, const UI32 &numberOfRetries = 0, const UI32 &maximumNumberOfSecondsToTryFor = 0, const UI32 &serverUniqueIdentifierFromServerPerspective = 0);
        void            indicateClosing           ();

        UI32            getId                     () const;
        string          getName                   () const;
        string          getIpAddress              () const;
        SI32            getPort                   () const;
        WaveServiceId  getUserInterfaceServiceId () const;

        bool            operator <<               (ManagementInterfaceMessage *pManagementInterfaceMessage);

        void            updateMessageVersionAndSerializationTypeForSocket (const string& msgVersion);

    // Now the Data Members

    private :
        UI32                   m_id;
        string                 m_name;
        string                 m_ipAddress;
        SI32                   m_port;
        WaveServiceId         m_userInterfaceServiceId;
        ClientStreamingSocket *m_pClientStreamingSocket;

    protected :
    public :
};

}

#endif // WAVEMANAGEMENTCLIENT_H
