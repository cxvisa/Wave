/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include "Framework/Attributes/AttributesMap.h"
#include <string>

typedef enum
{
    SERIALIZE_WITH_UNKNOWN = 0,
    SERIALIZE_WITH_ATTRIBUTE_ORDER,
    SERIALIZE_WITH_ATTRIBUTE_NAME
} SerializationFormatType;

namespace WaveNs
{

class SerializableObject
{
    private :
    protected :
                void                setIsPreparedForSerialization           (bool isPreparedForSerialization);
        virtual void                setupAttributesForSerialization         ();
                void                addSerializableAttribute                (Attribute *pAttribute);
                void                serialize                               (string &serializedData);
                void                loadFromSerializableObject              (SerializableObject *pSerializableObject);
                void                loadFromSerializedData                  (const string &serializedData);
                void                loadFromSerializedData                  (const UI8 *pData, const UI32 dataSize);
        virtual bool                isAttributeToBeLoadedFromSerializedData (SerializableObjectAttributeId soaid);
        static  SerializableObject *createAndLoadFromSerializedData         (const string &serializedData);
        static  SerializableObject *createAndLoadFromSerializedData         (const UI8 *pData, const UI32 dataSize);
                void                copyToAttributesMap                     (AttributesMap &attributesMap) const;
    public :
                                    SerializableObject                      ();
        virtual                    ~SerializableObject                      ();
                void                prepareForSerialization                 ();

                void                serialize2                              (string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); 
                void                loadFromSerializedData2                 (const string &serializedData, const UI8 serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME); 

                Attribute          *getAttribute                            (const string &attributeName);
                void                getAllAttributeNames                    (vector<string> &allAttributeNames) const;

                SerializableObject &operator =                              (const SerializableObject &serializableObject);

                void                addAttributeNameForOrderToNameMapping   (const string& attributeName);
        virtual void                setupAttributesForSerializationInAttributeOrderFormat         ();
                

    // Now the data members

    private :
        AttributesMap m_serializableAttributes;
        bool          m_isPreparedForSerialization;

    protected :
    public :
        friend class InterLocationMessageReceiverThread;
        friend class LocationBase;
        friend class StreamingSocketBase;
        friend class ClientStreamingSocket;
};

}

#endif //SERIALIZABLEOBJECT_H
