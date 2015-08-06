/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEMENTCLIENTINFORMATION_H
#define WAVEMANAGEMENTCLIENTINFORMATION_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Types/Types.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveManagementClientInformation : virtual public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                WaveManagementClientInformation         ();
                                WaveManagementClientInformation         (const string &waveClientName, const string &waveClientNameWithoutExtension, const string &ipAddress, const UI32 &port, const WaveServiceId &userInterfaceServiceId, const string &messageVersion);
        virtual                ~WaveManagementClientInformation         ();

                string          getWaveClientName                       () const;
                void            setWaveClientName                       (const string &waveClientName);

                string          getWaveClientNameWithoutExtension       () const;
                void            setWaveClientNameWithoutExtension       (const string &waveClientName);

                string          getIpAddress                            () const;
                void            setIpAddress                            (const string &ipAddress);

                UI32            getPort                                 () const;
                void            setPort                                 (const UI32 &port);

                WaveServiceId  getUserInterfaceServiceId               () const;
                void            setUserInterfaceServiceId               (const WaveServiceId &userInterfaceServiceId);

                string          getServerIpAddressFromClientPerspective () const;
                void            setServerIpAddressFromClientPerspective (const string &serverIpAddressFromClientPerspective);

                UI32            getServerUniqueIdentifier               () const;
                void            setServerUniqueIdentifier               (const UI32 &uniqueIdentifier);

                string          getMessageVersion                       () const; 
                void            setMessageVersion                       (const string &messageVersion);


    // Now the data members

    private :
        string         m_waveClientName;
        string         m_waveClientNameWithoutExtension;
        string         m_ipAddress;
        UI32           m_port;
        WaveServiceId m_userInterfaceServiceId;
        string         m_serverIpAddressFromClientPerspective;
        UI32           m_serverUniqueIdentifierFromClientPerspective;
        vector<string> m_reservedFields;
        string         m_messageVersion; 
        
    protected :
    public :
};

}

#endif // WAVEMANAGEMENTCLIENTINFORMATION_H


