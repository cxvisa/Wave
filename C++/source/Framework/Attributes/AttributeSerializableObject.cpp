/***************************************************************************
 *   Copyright (C) 2008-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Attributes/AttributeSerializableObject.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

template<class T> AttributeSerializableObject<T>::AttributeSerializableObject (const T &data, const string &attributeName , const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute (AttributeType::AttributeTypeSerializableObject, attributeName, attributeUserTag, isOperational)
{
    m_pData = new T;
    *m_pData = data;
    setIsMemoryOwnedByAttribute (true);
}

template<class T> AttributeSerializableObject<T>::AttributeSerializableObject (T  *pData, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute (AttributeType::AttributeTypeSerializableObject, attributeName, attributeUserTag, isOperational)
{
    m_pData = pData;
    setIsMemoryOwnedByAttribute (false);
}

template<class T> AttributeSerializableObject<T>::AttributeSerializableObject (const AttributeSerializableObject<T> &attribute)
    : Attribute (attribute)
{   
    m_pData = new T;
   *m_pData = attribute.getValue ();
    setIsMemoryOwnedByAttribute (true);
}

template<class T> AttributeSerializableObject<T>::~AttributeSerializableObject ()
{
    if (true == (getIsMemoryOwnedByAttribute ()))
    {
        delete m_pData;
    }
}

template<class T> AttributeSerializableObject<T> &AttributeSerializableObject<T>::operator = (const AttributeSerializableObject<T> &attribute)
{   
    Attribute::operator = (attribute);
    
    setValue (attribute.getValue ());

    return (*this);
}   

template<class T> bool AttributeSerializableObject<T>::validate () const
{
    waveAssert (AttributeType::AttributeTypeSerializableObject == (getAttributeType ()), __FILE__, __LINE__);

    if (AttributeType::AttributeTypeSerializableObject == (getAttributeType ()))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

template<class T> T AttributeSerializableObject<T>::getValue () const
{
    if (true == (validate ()))
    {
        return (*m_pData);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeSerializableObject::getValue : Invalid Cast of the underlying Attribute."));
        waveAssert (false, __FILE__, __LINE__);
        return (T ());
    }
}

template<class T> void AttributeSerializableObject<T>::setValue (const T &data)
{
    if (true == (validate ()))
    {
        *m_pData = data;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeSerializableObject::setValue : Invalid Cast of the underlying Attribute."));
        waveAssert (false, __FILE__, __LINE__);
    }
}

template<class T> string AttributeSerializableObject<T>::getSqlType ()
{
    waveAssert (false, __FILE__, __LINE__);

    string temp;
    return temp;
}

template<class T> void AttributeSerializableObject<T>::setupOrm (OrmTable *pOrmTable)
{
    waveAssert (false, __FILE__, __LINE__);
}
    
template<class T> string AttributeSerializableObject<T>::getSqlForCreate ()
{   
    waveAssert (false, __FILE__, __LINE__);
    string temp;
    return temp;
}
    
template<class T> void AttributeSerializableObject<T>::getSqlForInsert (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst)
{
    waveAssert (false, __FILE__, __LINE__);
}

template<class T> void AttributeSerializableObject<T>::getSqlForUpdate (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst)
{
    waveAssert (false, __FILE__, __LINE__);
}

template<class T> void AttributeSerializableObject<T>::getSqlForSelect (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator)
{
    waveAssert (false, __FILE__, __LINE__);
}

template<class T> void *AttributeSerializableObject<T>::getPData ()
{
    return (m_pData);
}

template<class T> void AttributeSerializableObject<T>::setValue (const void *pData)
{
    *m_pData = *(reinterpret_cast<const T *> (pData));
}

template<class T> Attribute *AttributeSerializableObject<T>::clone ()
{   
    AttributeSerializableObject *pAttributeSerializableObject = new AttributeSerializableObject (*this);

    return (pAttributeSerializableObject);
}

template<class T> void AttributeSerializableObject<T>::toString (string &valueString)
{
    SerializableObject *pObject = dynamic_cast<SerializableObject *> (m_pData);

    waveAssert (NULL != pObject, __FILE__, __LINE__);

    return (pObject->serialize2 (valueString));
}

template<class T> void AttributeSerializableObject<T>::fromString (const string &valueString)
{
    T tempSerializableObject;

    SerializableObject *pObject = dynamic_cast<SerializableObject *> (&tempSerializableObject);

    waveAssert (NULL != pObject, __FILE__, __LINE__);

    tempSerializableObject.loadFromSerializedData2 (valueString);

    setValue (tempSerializableObject);
}

template<class T> void AttributeSerializableObject<T>::setDefaultValue()
{
    waveAssert (false, __FILE__, __LINE__);
}

template<class T> void AttributeSerializableObject<T>::getCValue (WaveCValue *pCValue)
{
    waveAssert (false, __FILE__, __LINE__);
}

template<class T> bool AttributeSerializableObject<T>::isCurrentValueSameAsDefault () const
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSerializableObject::isCurrentValueSameAsDefault : This method is not supported."));
    waveAssert (false, __FILE__, __LINE__);
    return (false);
}
}
