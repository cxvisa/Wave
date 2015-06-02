/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef ATTRIBUTEIPV4ADDRESSUC_H
#define ATTRIBUTEIPV4ADDRESSUC_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeUC.h"
#include "Framework/Types/IpV4AddressUC.h"
#include "Framework/Types/IpV4Address.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeIpV4AddressUC : public Attribute, public AttributeUC
{
    private :
        virtual bool                    validate                        () const;

    protected :
    public :
                                        AttributeIpV4AddressUC          (const IpV4AddressUC &data, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeIpV4AddressUC          (const IpV4AddressUC &data, const bool &isNoElement, const bool &defaultFlag, const IpV4Address &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);                                      AttributeIpV4AddressUC (IpV4AddressUC *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeIpV4AddressUC          (IpV4AddressUC *pData, const bool &isNoElement, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeIpV4AddressUC          (IpV4AddressUC *pData, const bool &isNoElement, const bool &defaultFlag, const IpV4Address &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                        AttributeIpV4AddressUC          (const AttributeIpV4AddressUC &attribute);
        virtual                        ~AttributeIpV4AddressUC          ();
                AttributeIpV4AddressUC &operator =                      (const AttributeIpV4AddressUC &attribute);
                IpV4AddressUC           getValue                        () const;
                void                    setValue                        (const IpV4AddressUC &data);
                bool                    isCurrentValueSameAsDefault     () const;
                IpV4Address             getDefaultData                  () const;
                bool                    getIsDefaultDataValidFlag       (void) const;
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
        IpV4AddressUC *m_pData;
        bool           m_isNoElement;
        IpV4Address    m_defaultData;
        bool           m_isDefaultDataValid; // if this is true, then default value is valid

    protected :
    public :
};

}
 #endif  //ATTRIBUTEIPV4ADDRESSUC_H
