/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSE_H
#define LIGHTPULSE_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Types/Uuid.h"

namespace WaveNs
{

class LightPulse : public SerializableObject
{
    private :
    protected :
        void setupAttributesForSerialization ();

    public :
                        LightPulse                              (const string &Name);
        virtual        ~LightPulse                              ();

                string  getName                                 () const;
                void    setName                                 (const string &name);

                Uuid    getSenderLightHouseId                   () const;
                void    setSenderLightHouseId                   (const Uuid &senderLightHouseId);

                string  getSenderLightHouseIpAddress            () const;
                void    setSenderLightHouseIpAddress            (const string &senderLightHouseIpAddress);

                SI32    getSenderLightHousePort                 () const;
                void    setSenderLightHousePort                 (const SI32 &port);

                string  getSenderIpAddressFromClientPerspective () const;
                void    setSenderIpAddressFromClientPerspective (const string &senderIpAddressFromClientPerspective);

        // Now the data members

    private :
        string m_name;
        Uuid   m_senderLightHouseId;
        string m_senderLightHouseIpAddress;
        SI32   m_senderLightHousePort;
        string m_senderIpAddressFromClientPerspective;

    protected :
    public :
};

}

#endif // LIGHTPULSE_H
