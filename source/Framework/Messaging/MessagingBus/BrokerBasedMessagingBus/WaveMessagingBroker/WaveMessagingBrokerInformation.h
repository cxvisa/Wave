/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERINFORMATION_H
#define WAVEMESSAGINGBROKERINFORMATION_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class WaveMessagingBrokerInformation : public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                WaveMessagingBrokerInformation ();
                WaveMessagingBrokerInformation (const string &name, const string &ipAddress, const SI32 &port);
               ~WaveMessagingBrokerInformation ();

        string  getName                        () const;
        void    setName                        (const string &name);

        string  getIpAddress                   () const;
        void    setIpAddress                   (const string &ipAddress);

        SI32    getPort                        () const;
        void    setPort                        (const SI32 &port);

        // Now the data members

    private :
        string m_name;
        string m_ipAddress;
        SI32   m_port;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERINFORMATION_H
