/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef ATTRIBUTESI64_H
#define ATTRIBUTESI64_H

#include "Framework/Attributes/Attribute.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeSI64 : public Attribute
{
    private :
        virtual bool            validate                        () const;
        virtual bool            isConditionOperatorSupported    (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                AttributeSI64                   (const SI64 &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeSI64                   (const SI64 &data, const SI64 &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeSI64                   (SI64 *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeSI64                   (SI64 *pData, const SI64 &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeSI64                   (const AttributeSI64 &attribute);
        virtual                ~AttributeSI64                   ();
                AttributeSI64  &operator =                      (const AttributeSI64 &attribute);
                SI64            getValue                        () const;
                void            setValue                        (const SI64 &data);
                bool            isCurrentValueSameAsDefault     () const;
                SI64            getDefaultValue                 () const;
                bool            getIsDefaultDataValidFlag       () const;
        virtual string          getSqlType                      ();
        virtual void            setupOrm                        (OrmTable *pOrmTable);
        virtual string          getSqlForCreate                 ();
        virtual void            getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void            getSqlForUpdate                 (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void            getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void            toString                        (string &valueString);
        virtual void            fromString                      (const string &valueString);
        virtual ResourceId      loadFromPlainString             (const string &valueString);
        virtual void           *getPData                        ();
        virtual void            setValue                        (const void *pData);
        virtual Attribute      *clone                           ();
        static  map<string, string> getSupportedConversions     ();
        virtual void            setDefaultValue                 ();
        virtual void            getCValue                       (WaveCValue *pCValue);
    // Now the data members

    private :
        SI64 *m_pData;
        SI64  m_defaultData;
        bool  m_isDefaultDataValid;

    protected :
    public :
};

}
#endif // ATTRIBUTESI64_H
