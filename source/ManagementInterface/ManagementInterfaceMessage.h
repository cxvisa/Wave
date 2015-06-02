/***************************************************************************
 *   Copyright (C) 2005 - 2011 Vidyasagara Guntaka                         *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACEMESSAGE_H
#define MANAGEMENTINTERFACEMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"
//#include "Framework/Attributes/AttributesMap.h"

namespace WaveNs
{

class ManagementInterfaceMessage : public PrismMessage
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                              ManagementInterfaceMessage    (const string &serviceName, const UI32 &operationId);
        virtual              ~ManagementInterfaceMessage    ();

                string        getServiceName                () const;

                string        getClientIpAddress            () const;
                void          setClientIpAddress            (const string &clientIpAddress);

                UI32          getClientPort                 () const;
                void          setClientPort                 (const UI32 &clientPort);

                UI32          getClientId                   () const;
                void          setClientId                   (const UI32 &clientId);

                string        getClientName                 () const;
                void          setClientName                 (const string &clientName);

                string        getClientNameWithoutExtension () const;
                void          setClientNameWithoutExtension (const string &clientNameWithoutExtension);

                UI32          getServerId                   () const;
                void          setServerId                   (const UI32 &serverId);

                SI32          getSlotInstance               () const;
                void          setSlotInstance               (const SI32 &instance);

                bool          getAllWaveClients             () const;
                void          setAllWaveClients             (const bool &allWaveClients);

                string        getTtyName                    () const;
                void          setTtyName                    (const string &ttyName);

        virtual PrismMessage *clone                         ();

    // Now the data members

    private :
        string m_serviceName;
        string m_clientIpAddress;
        UI32   m_clientPort;
        UI32   m_clientId;
        string m_clientName;
        string m_clientNameWithoutExtension;
        UI32   m_serverId;
        SI32   m_slotInstance;
        bool   m_allWaveClients;
        string m_ttyName;

    protected :
    public :
};

}

#endif // MANAGEMENTINTERFACEMESSAGE_H
