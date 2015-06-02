/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMNODECONNECTIONINFORMATION_H
#define PRISMNODECONNECTIONINFORMATION_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class PrismNodeConnectionInformation : virtual public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                        PrismNodeConnectionInformation ();
                        PrismNodeConnectionInformation (const string &thisLocationServerIpAddress, const UI32 &thisLocationServerPort, const LocationId &expectedLocationId = 0, const string &messageVersion = "");
        virtual        ~PrismNodeConnectionInformation ();

                string  getThisLocationServerIpAddress () const;
                void    setThisLocationServerIpAddress (const string &thisLocationServerIpAddress);
                UI32    getThisLocationServerPort      () const;
                void    setThisLocationServerPort      (const UI32 &thisLocationServerPort);
                LocationId  getExpectedLocationId      () const;
                void        setExpectedLocationId      (const LocationId &expectedLocationId);

                string      getMessageVersion          () const;   
                void        setMessageVersion          (const string &msgVersion); 

    // Now the data members

    private :
        string m_thisLocationServerIpAddress;
        UI32   m_thisLocationServerPort;
        UI32   m_expectedLocationId;
        string m_messageVersion;
    protected :
    public :
};


class PrismHaNodeConnectionInformation : virtual public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization                        ();
        virtual void setupAttributesForSerializationInAttributeOrderFormat  ();
    protected :
    public :
                        PrismHaNodeConnectionInformation ();
                        PrismHaNodeConnectionInformation (const string &thisLocationServerIpAddress, const UI32 &thisLocationServerPort, const LocationId &expectedLocationId = 0, const string &messageVersion = "");
        virtual        ~PrismHaNodeConnectionInformation ();

                string  getThisLocationServerIpAddress () const;
                void    setThisLocationServerIpAddress (const string &thisLocationServerIpAddress);
                UI32    getThisLocationServerPort      () const;
                void    setThisLocationServerPort      (const UI32 &thisLocationServerPort);
                LocationId  getExpectedLocationId          () const;
                void        setExpectedLocationId          (const LocationId &expectedLocationId);
                string  getMessageVersion                  () const;
                void    setMessageVersion                  (const string &thisLocationServerIpAddress);
    // Now the data members

    private :
        string m_thisLocationServerIpAddress;
        UI32   m_thisLocationServerPort;
        UI32   m_expectedLocationId;
        string m_messageVersion;
    protected :
    public :
};


}

#endif // PRISMNODECONNECTIONINFORMATION_H


