/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEMESSAGEBASE_H
#define MAPREDUCEMESSAGEBASE_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class MapReduceMessageBase : public SerializableObject
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                                      MapReduceMessageBase    ();
        virtual                      ~MapReduceMessageBase    ();

                MapReduceMessageType  getMapReduceMessageType () const;
                void                  setMapReduceMesageType  (const MapReduceMessageType &mapReduceMessageType);

        static  MapReduceMessageType  getType                 (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME);

        // Now the data members.

    private :
        MapReduceMessageType m_mapReduceMessageType;

    protected :
    public :
};

}

#endif // MAPREDUCEMESSAGEBASE_H
