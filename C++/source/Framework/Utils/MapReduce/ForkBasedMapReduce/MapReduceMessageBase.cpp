/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceMessageBase.h"
#include "WaveResourceIdEnums.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

MapReduceMessageBase::MapReduceMessageBase ()
    : SerializableObject (),
      m_mapReduceMessageType (MAP_REDUCE_MESSAGE_TYPE_READY)
{
}

MapReduceMessageBase::~MapReduceMessageBase ()
{
}

void MapReduceMessageBase::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeResourceId (reinterpret_cast<UI32 *> (&m_mapReduceMessageType), "mapReduceMessageType"));
}

MapReduceMessageType MapReduceMessageBase::getMapReduceMessageType () const
{
    return (m_mapReduceMessageType);
}

void MapReduceMessageBase::setMapReduceMesageType (const MapReduceMessageType &mapReduceMessageType)
{
    m_mapReduceMessageType = mapReduceMessageType;
}

MapReduceMessageType MapReduceMessageBase::getType (const string &serializedData, const UI8 serializationType)
{
    // We know the SerializableObjectAttributeId for Message Type is always 1. (This cannot be changed from 1)
    // So the corresponding attribute in the serialized XML will be tagged with A1.  So look for the data
    // tagged between <A1> and </A1>

    SI32 index1            = 0;
    SI32 index2            = 0;
    string attributeTag    = "";

    if (SERIALIZE_WITH_ATTRIBUTE_ORDER == serializationType)
    {
        attributeTag = string ("1");
    }
    else
    {
        attributeTag = string ("mapReduceMessageType");
    }
    UI32 startIndexOffset = attributeTag.size () + strlen ("<A>");

    index1    = serializedData.find (string ("<A") + attributeTag + string (">"));
    index2    = serializedData.find (string ("</A") + attributeTag + string (">"));

    string sotString = serializedData.substr (index1 + startIndexOffset, index2 - index1 - startIndexOffset);

    MapReduceMessageType mapReduceMessageType = MAP_REDUCE_MESSAGE_TYPE_RESPONSE;

    AttributeResourceId attributeResourceId (mapReduceMessageType);
    attributeResourceId.fromString (sotString);

    MapReduceMessageType *pMapReduceMessageType = (MapReduceMessageType *) attributeResourceId.getPData ();

    return (*pMapReduceMessageType);
}

}
