/***************************************************************************
 *   Copyright (C) 2008-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef ATTRIBUTESERIALIZABLEOBJECT_H
#define ATTRIBUTESERIALIZABLEOBJECT_H 

#include "Framework/Attributes/Attribute.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

template<class T> class AttributeSerializableObject : public Attribute
{
    private:
        virtual bool                                   validate                          () const;
    protected:
    public:
                                                       AttributeSerializableObject (const T &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                                       AttributeSerializableObject (T *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                                       AttributeSerializableObject (const AttributeSerializableObject<T> &attribute);
        virtual                                       ~AttributeSerializableObject ();
                AttributeSerializableObject<T>        &operator =                  (const AttributeSerializableObject<T> &attribute);
                T                                      getValue                    () const;
                void                                   setValue                    (const T &data);
        virtual string                                 getSqlType                  ();
        virtual void                                   setupOrm                    (OrmTable *pOrmTable);
        virtual string                                 getSqlForCreate             ();
        virtual void                                   getSqlForInsert             (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                                   getSqlForUpdate             (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                                   getSqlForSelect             (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                                   toString                    (string &valueString);
        virtual void                                   fromString                  (const string &valueString);
        virtual void                                  *getPData                    ();
        virtual void                                   setValue                    (const void *pData);
        virtual Attribute                             *clone                       ();
        virtual void                                   setDefaultValue             ();
        virtual void                                   getCValue                   (WaveCValue *pCValue);
                bool                                   isCurrentValueSameAsDefault () const; 
    // data members
    private:
                T   *m_pData;
    protected:
    public:
};

}
#endif //ATTRIBUTESERIALIZABLEOBJECT_H
