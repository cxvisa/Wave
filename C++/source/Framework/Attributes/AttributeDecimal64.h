/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef ATTRIBUTEDECIMAL64_H
#define ATTRIBUTEDECIMAL64_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeVector.h"
#include "Framework/Types/Decimal64.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeDecimal64 : public Attribute
{
    private :
        virtual bool                    validate                        () const;
        virtual bool                    isConditionOperatorSupported    (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                        AttributeDecimal64              (const Decimal64 &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeDecimal64              (const Decimal64 &data, const Decimal64 &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeDecimal64              (Decimal64 *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeDecimal64              (Decimal64 *pData, const Decimal64 &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeDecimal64              (const AttributeDecimal64 &attribute);
        virtual                        ~AttributeDecimal64              ();
                AttributeDecimal64      &operator =                     (const AttributeDecimal64 &attribute);
                Decimal64               getValue                        () const;
                void                    getAllValues                    (SI64 *val, UI8 *fractiondigits);
                void                    setValue                        (const Decimal64 &data);
                bool                    isCurrentValueSameAsDefault     () const;
                Decimal64               getDefaultDecimal64             () const;
                bool                    getIsDefaultDecimal64ValidFlag  () const;
        virtual string                  getSqlType                      ();
        virtual void                    setupOrm                        (OrmTable *pOrmTable);
        virtual string                  getSqlForCreate                 ();
        virtual void                    getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                    getSqlForUpdate                 (string &sqlForUpdecimal64, string &sqlForUpdecimal642, bool isFirst = false);
        virtual void                    getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                    toString                        (string &valueString);
        virtual void                    fromString                      (const string &valueString);
        virtual ResourceId              loadFromPlainString             (const string &valueString);
        virtual void                   *getPData                        ();
        virtual void                    setValue                        (const void *pData);
        virtual Attribute              *clone                           ();
        static  map<string, string>     getSupportedConversions         ();
        virtual void                    setDefaultValue                 ();
        virtual void                    getCValue                       (WaveCValue *pCValue);
    // Now the data members

    private :
        Decimal64 *m_pData;
        Decimal64 m_defaultDecimal64;
        bool      m_isDefaultDecimal64Valid;

    protected :
    public :
};

class AttributeDecimal64Vector : public Attribute, public AttributeVector
{
    private :
        virtual bool validate () const;

    protected :
    public :
                                              AttributeDecimal64Vector             (const vector<Decimal64> &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                              AttributeDecimal64Vector             (const vector<Decimal64> &data, const vector<Decimal64> &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                              AttributeDecimal64Vector             (vector<Decimal64> *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                              AttributeDecimal64Vector             (vector<Decimal64> *pData, const vector<Decimal64> &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                              AttributeDecimal64Vector             (const AttributeDecimal64Vector &attribute);
        virtual                              ~AttributeDecimal64Vector             ();
                AttributeDecimal64Vector      &operator =                          (const AttributeDecimal64Vector &attribute);
                vector<Decimal64>             getValue                             () const;
                void                          setValue                             (const vector<Decimal64> &data);
                bool                          isCurrentValueSameAsDefault          () const;
                vector<Decimal64>             getDefaultDecimal64Vector            () const;
                bool                          getIsDefaultDecimal64VectorValidFlag () const;
        virtual string                        getSqlType                           ();
        virtual void                          setupOrm                             (OrmTable *pOrmTable);
        virtual string                        getSqlForCreate                      ();
        virtual void                          getSqlForInsert                      (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                          getSqlForUpdate                      (string &sqlForUpdecimal64, string &sqlForUpdecimal642, bool isFirst = false);
        virtual void                          getSqlForSelect                      (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                          toString                             (string &valueString);
        virtual void                          fromString                           (const string &valueString);
        virtual void                         *getPData                             ();
        virtual void                          setValue                             (const void *pData);
        virtual Attribute                    *clone                                ();
        virtual void                          setDefaultValue                      ();
        static  map<string, string>           getSupportedConversions              ();
        virtual void                          getCValue                            (WaveCValue *pCValue);
        virtual void                          addAttributeToVector                 (Attribute *attribute);
        virtual void                          deleteAttributeFromVector            (Attribute *attribute);
    // Now the data members

    private :
        vector<Decimal64> *m_pData;
        vector<Decimal64> m_defaultDecimal64Vector;
        bool              m_isDefaultDecimal64VectorValid;
    protected :
    public :
};

}

#endif // ATTRIBUTEDECIMAL64_H
