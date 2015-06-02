/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu                                                     *
 ***************************************************************************/

#ifndef ATTRIBUTEUI32UC_H
#define ATTRIBUTEUI32UC_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeUC.h"
#include "Framework/Types/UI32UC.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeUI32UC : public Attribute, public AttributeUC
{
    private :
        virtual bool                    validate                        () const;

    protected :
    public :
                                        AttributeUI32UC                 (const UI32UC &data, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32UC                 (const UI32UC &data, const bool &isNoElement, const bool &defaultFlag, const UI32 &defaultUI32UC, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32UC                 (UI32UC *pData, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32UC                 (UI32UC *pData, const bool &isNoElement, const bool &defaultFlag, const UI32 &defaultUI32UC, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeUI32UC                 (const AttributeUI32UC &attribute);
        virtual                        ~AttributeUI32UC                 ();
                AttributeUI32UC        &operator =                      (const AttributeUI32UC &attribute);

                UI32UC                  getValue                        () const;
                void                    setValue                        (const UI32UC &data);
            
                bool                    isCurrentValueSameAsDefault     () const;
                UI32                    getDefaultUI32                  () const;
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
        virtual void                    getPlainString                  (string &valueString);
        virtual ResourceId              loadFromPlainString             (const string &valueString);
        virtual void                   *getPData                        ();
        virtual void                    setValue                        (const void *pData);
        virtual Attribute              *clone                           ();
        static  map<string, string>     getSupportedConversions         ();
        virtual void                    setDefaultValue                 ();
        virtual void                    getCValue                       (WaveCValue *pCValue);
        virtual bool                    getIsUserConfigured             ();        

    // Now the data members

    private :
        UI32UC   *m_pData;
        bool      m_isNoElement;
        UI32      m_defaultUI32;
        bool      m_isDefaultUI32Valid;

    protected :
    public :
};

}

#endif  //ATTRIBUTEUI32UC_H

