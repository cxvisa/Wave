/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef ATTRIBUTEUI32VECTORUC_H
#define ATTRIBUTEUI32VECTORUC_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeUC.h"
#include "Framework/Types/UI32VectorUC.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeUI32VectorUC : public Attribute, public AttributeUC
{
    private :
        virtual bool                    validate                        () const;

    protected :
    public :
                                        AttributeUI32VectorUC           (const UI32VectorUC &data, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32VectorUC           (const UI32VectorUC &data, const bool &isNoElement, const bool &defaultFlag, const vector<UI32> &defaultUI32VectorUC, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32VectorUC           (UI32VectorUC *pData, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32VectorUC           (UI32VectorUC *pData, const bool &isNoElement, const bool &defaultFlag, const vector<UI32> &defaultUI32VectorUC, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32VectorUC           (const AttributeUI32VectorUC &attribute);
        virtual                        ~AttributeUI32VectorUC           ();
                AttributeUI32VectorUC  &operator =                      (const AttributeUI32VectorUC &attribute);

                UI32VectorUC            getValue                        () const;
                void                    setValue                        (const UI32VectorUC &data);

                bool                    isCurrentValueSameAsDefault     () const;
                vector<UI32>            getDefaultUI32Vector            () const;
                bool                    getIsDefaultUI32ValidFlag       () const;

                bool                    getIsNoElement                  () const;

        virtual string                  getSqlType                      ();
        virtual void                    setupOrm                        (OrmTable *pOrmTable);
        virtual string                  getSqlForCreate                 ();
        virtual void                    getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                    getSqlForUpdate                 (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                    getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                    toString                        (string &valueString);
        virtual void                    fromString                      (const string &valueString);
        virtual void                   *getPData                        ();
        virtual void                    setValue                        (const void *pData);
        virtual Attribute              *clone                           ();
        static  map<string, string>     getSupportedConversions         ();
        virtual void                    setDefaultValue                 ();
        virtual void                    getCValue                       (WaveCValue *pCValue);
        virtual bool                    getIsUserConfigured             ();
    // Now the data members

    private :
        UI32VectorUC *m_pData;
        bool          m_isNoElement;
        vector<UI32>  m_defaultUI32Vector;
        bool          m_isDefaultUI32Valid;

    protected :
    public :
};

}

#endif  //ATTRIBUTEUI32VECTORUC_H

