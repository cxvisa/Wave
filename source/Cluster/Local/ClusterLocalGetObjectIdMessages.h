/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef CLUSTERLOCALGETOBJECTIDMESSAGES_H
#define CLUSTERLOCALGETOBJECTIDMESSAGES_H

#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class PrismMessage;

class ClusterLocalGetSlotObjectIdMessage : public PrismMessage
{
    private :
    protected :
    public :
                            ClusterLocalGetSlotObjectIdMessage  (const UI32 &slotNumber, const LocationId &locationId);
        virtual            ~ClusterLocalGetSlotObjectIdMessage  ();

                UI32        getSlotNumber                       () const;
                void        setSlotNumber                       (const UI32 &slotNumber);
                
                LocationId  getLocationId                       () const;
                void        setLocationId                       (const LocationId &locationId);

                ObjectId    getSlotObjectId                     () const;
                void        setSlotObjectId                     (const ObjectId slotObjectId);

    // Now the data members

    private :
        UI32        m_slotNumber;
        LocationId  m_locationId;
        ObjectId    m_slotObjectId;

    protected :
    public :
};

class ClusterLocalGetLocationObjectIdMessage : public PrismMessage
{
    private :
    protected :
    public :
                            ClusterLocalGetLocationObjectIdMessage  (const LocationId &locationId);
        virtual            ~ClusterLocalGetLocationObjectIdMessage  ();

                LocationId  getLocationId                           () const;
                void        setLocationId                           (const LocationId &locationId);

                ObjectId    getLocationObjectId                     () const;
                void        setLocationObjectId                     (const ObjectId locationObjectId);

    // Now the data members

    private :
        LocationId  m_locationId;
        ObjectId    m_locationObjectId;

    protected :
    public :
};

class ClusterLocalGetSlotNumberMessage : public PrismMessage
{
    private :
    protected :
    public :
                            ClusterLocalGetSlotNumberMessage    (const ObjectId slotObjectId);
        virtual            ~ClusterLocalGetSlotNumberMessage    ();

                UI32        getSlotNumber                       () const;
                void        setSlotNumber                       (const UI32 &slotNumber);
                
                ObjectId    getSlotObjectId                     () const;
                void        setSlotObjectId                     (const ObjectId slotObjectId);

    // Now the data members

    private :
        UI32        m_slotNumber;
        ObjectId    m_slotObjectId;

    protected :
    public :
};

class ClusterLocalGetLocationIdMessage : public PrismMessage
{
    private :
    protected :
    public :
                            ClusterLocalGetLocationIdMessage    (const ObjectId locationObjectId);
        virtual            ~ClusterLocalGetLocationIdMessage    ();

                LocationId  getLocationId                       () const;
                void        setLocationId                       (const LocationId &locationId);
                
                ObjectId    getLocationObjectId                 () const;
                void        setLocationObjectId                 (const ObjectId slotObjectId);

    // Now the data members

    private :
        LocationId  m_locationId;
        ObjectId    m_locationObjectId;

    protected :
    public :
};

}

#endif // CLUSTERLOCALSETHAROLEMESSAGE_H
