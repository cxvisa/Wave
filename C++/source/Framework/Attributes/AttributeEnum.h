/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef ATTRIBUTEENUM_H
#define ATTRIBUTEENUM_H

#include "Framework/Attributes/Attribute.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeEnum : public Attribute
{
    private :
        virtual bool            validate                        () const;

    protected :
    public :
                                AttributeEnum                   (const UI32 &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeEnum                   (const UI32 &data, const UI32 &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeEnum                   (UI32 *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeEnum                   (UI32 *pData, const UI32 &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                AttributeEnum                   (const AttributeEnum &attribute);
        virtual                ~AttributeEnum                   ();
                AttributeEnum  &operator =                      (const AttributeEnum &attribute);
                UI32            getValue                        () const;
                void            setValue                        (const UI32 &data);
                bool            isCurrentValueSameAsDefault     () const;
                UI32            getDefaultData                  () const;
                bool            getIsDefaultDataValidFlag       (void) const;
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
        static  map<string, string>     getSupportedConversions ();
        virtual void            setDefaultValue                 ();
		virtual void 		    getCValue                       (WaveCValue *pCValue);

    // functions to be used during yang parsing
                void            populateNameValueEnumMap        (string name, UI32 value);       
                ResourceId      getValueFromEnumName            (const string &name, UI32 &value);       
                ResourceId      getEnumNameFromValue            (string &name, const UI32 &value);       


    // Now the data members

    private :
        UI32 *m_pData;
        UI32  m_defaultData;
        bool  m_isDefaultDataValid; // if this is true, then default value is valid

        map <string, UI32>      m_NameToValueMap;
        map <UI32, string>      m_ValueToNameMap;

    protected :
    public :
};

}

#endif  //ATTRIBUTEENUM_H
