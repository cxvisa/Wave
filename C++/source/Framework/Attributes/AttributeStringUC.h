/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu  Varshney                                           *
 ***************************************************************************/

#ifndef ATTRIBUTESTRINGUC_H
#define ATTRIBUTESTRINGUC_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeUC.h"
#include "Framework/Types/StringUC.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeStringUC : public Attribute, public AttributeUC
{
    private :
        virtual bool                validate                        () const;

    protected :
    public :
                                    AttributeStringUC               (const StringUC &data, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeStringUC               (const StringUC &data, const bool &isNoElement, const bool &defaultFlag, const string &defaultString, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeStringUC               (StringUC *pData, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeStringUC               (StringUC *pData, const bool &isNoElement, const bool &defaultFlag, const string &defaultString, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                    AttributeStringUC               (const AttributeStringUC &attribute);
        virtual                    ~AttributeStringUC               ();
                AttributeStringUC  &operator =                      (const AttributeStringUC &attribute);

                StringUC            getValue                        () const;
                void                setValue                        (const StringUC &data);

                bool                isCurrentValueSameAsDefault     () const;
                string              getDefaultString                () const;
                bool                getIsDefaultStringValidFlag     () const;

                bool                getIsNoElement                  () const;

        virtual string              getSqlType                      ();
        virtual void                setupOrm                        (OrmTable *pOrmTable);
        virtual string              getSqlForCreate                 ();
        virtual void                getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                getSqlForUpdate                 (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                toString                        (string &valueString);
        virtual void                fromString                      (const string &valueString);
        virtual void                getPlainString                  (string &valueString);
        virtual ResourceId          loadFromPlainString             (const string &valueString);
        virtual void               *getPData                        ();
        virtual void                setValue                        (const void *pData);
        virtual Attribute          *clone                           ();
        static  map<string, string> getSupportedConversions         ();

                void                toEscapedString                 (string *inputString, string &valueString);
        virtual void                setDefaultValue                 ();
        virtual void                getCValue                       (WaveCValue *pCValue);
        virtual bool                getIsUserConfigured             ();
        
    // Now the data members

    private :
        StringUC *m_pData;
        bool      m_isNoElement;
        string    m_defaultString;
        bool      m_isDefaultStringValid;

    protected :
    public :
};

}

#endif  //ATTRIBUTESTRINGUC_H

