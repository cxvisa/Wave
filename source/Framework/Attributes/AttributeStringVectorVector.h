/***************************************************************************
 *   Copyright (C) 2005 - 2011 Vidyasagara Guntaka                         *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ATTRIBUTESTRINGVECTORVECTOR_H
#define ATTRIBUTESTRINGVECTORVECTOR_H

#include "Framework/Attributes/Attribute.h"

namespace WaveNs
{

class AttributeStringVectorVector : public Attribute
{
    private :
        virtual bool validate                     () const;
        virtual bool isConditionOperatorSupported (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                             AttributeStringVectorVector (const vector<vector<string> > &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                             AttributeStringVectorVector (const vector<vector<string> > &data, const vector<vector<string> > &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                             AttributeStringVectorVector (vector<vector<string> > *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                             AttributeStringVectorVector (vector<vector<string> > *pData, const vector<vector<string> > &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                             AttributeStringVectorVector (const AttributeStringVectorVector &attribute);
        virtual                             ~AttributeStringVectorVector ();
                AttributeStringVectorVector &operator =                 (const AttributeStringVectorVector &attribute);
                vector<vector<string> >      getValue                    () const;
                void                         setValue                    (const vector<vector<string> > &m_data);
                bool                         isCurrentValueSameAsDefault () const;
                vector<vector<string> >      getDefaultData              () const;
                bool                         getIsDefaultDataValidFlag   () const;
        virtual string                       getSqlType                  ();
        virtual void                         setupOrm                    (OrmTable *pOrmTable);
        virtual string                       getSqlForCreate             ();
        virtual void                         getSqlForInsert             (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                         getSqlForUpdate             (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                         getSqlForSelect             (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                         toString                    (string &valueString);
        virtual void                         fromString                  (const string &valueString);
        virtual void                        *getPData                    ();
        virtual void                         setValue                    (const void *pData);
        virtual Attribute                   *clone                       ();
        static  map<string, string>          getSupportedConversions     ();
        virtual void                         setDefaultValue             ();
                void                         toEscapedString             (string &valueString);
        virtual void                         getCValue                   (WaveCValue *pCValue);

    // Now the data members

    private :
        vector<vector<string> > *m_pData;
        vector<vector<string> >  m_defaultData;
        bool                     m_isDefaultDataValid;

    protected :
    public :
};

}

#endif // ATTRIBUTESTRINGVECTORVECTOR_H
