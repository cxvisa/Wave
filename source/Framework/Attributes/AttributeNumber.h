/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ATTRIBUTENUMBER_H
#define ATTRIBUTENUMBER_H

#include "Framework/Attributes/Attribute.h"
#include "WaveResourceIdEnums.h"
#include "Framework/Types/Number.h"

namespace WaveNs
{

class AttributeNumber : public Attribute
{
    private :
        virtual bool             validate                        () const;
        virtual bool             isConditionOperatorSupported    (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                     AttributeNumber                (const Number &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                     AttributeNumber                (const Number &data, const Number &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                     AttributeNumber                (Number *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                     AttributeNumber                (Number *pData, const Number &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                     AttributeNumber                (const AttributeNumber &attribute);
        virtual                     ~AttributeNumber                ();
                AttributeNumber     &operator =                     (const AttributeNumber &attribute);
                Number               getValue                       () const;
                void                 setValue                       (const Number &data);
                bool                 isCurrentValueSameAsDefault    () const;
                Number               getDefaultValue                () const;
                bool                 getIsDefaultDataValidFlag      () const;
        virtual string               getSqlType                     ();
        virtual void                 setupOrm                       (OrmTable *pOrmTable);
        virtual string               getSqlForCreate                ();
        virtual void                 getSqlForInsert                (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                 getSqlForUpdate                (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                 getSqlForSelect                (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                 toString                       (string &valueString);
        virtual void                 fromString                     (const string &valueString);
        virtual ResourceId           loadFromPlainString            (const string &valueString);
        virtual void                *getPData                       ();
        virtual void                 setValue                       (const void *pData);
        virtual Attribute           *clone                          ();
        static  map<string, string>  getSupportedConversions        ();
        virtual void                 setDefaultValue                ();
        virtual void                 getCValue                      (WaveCValue *pCValue);
    // Now the data members

    private :
        Number *m_pData;
        Number  m_defaultData;
        bool    m_isDefaultDataValid;

    protected :
    public :
};

}
#endif // ATTRIBUTENUMBER_H
