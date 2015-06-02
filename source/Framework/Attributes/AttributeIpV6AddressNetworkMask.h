/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef ATTRIBUTEIPV6ADDRESSNETWORKMASK_H
#define ATTRIBUTEIPV6ADDRESSNETWORKMASK_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Types/IpV6AddressNetworkMask.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeIpV6AddressNetworkMask : public Attribute
{
    private :
        virtual bool                                validate                        () const;
        virtual bool                                isConditionOperatorSupported    (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                                    AttributeIpV6AddressNetworkMask (const IpV6AddressNetworkMask &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                                    AttributeIpV6AddressNetworkMask (const IpV6AddressNetworkMask &data, const IpV6AddressNetworkMask &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                                    AttributeIpV6AddressNetworkMask (IpV6AddressNetworkMask *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                                    AttributeIpV6AddressNetworkMask (IpV6AddressNetworkMask *pData, const IpV6AddressNetworkMask &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);
                                                    AttributeIpV6AddressNetworkMask (const AttributeIpV6AddressNetworkMask &attribute);
        virtual                                    ~AttributeIpV6AddressNetworkMask ();
                AttributeIpV6AddressNetworkMask    &operator =                      (const AttributeIpV6AddressNetworkMask &attribute);
                IpV6AddressNetworkMask              getValue                        () const;
                void                                getAllValues                    (string &NetworkMask, UI8 *length);
                void                                setValue                        (const IpV6AddressNetworkMask &data);
                bool                                isCurrentValueSameAsDefault     () const;
                bool                                getIsDefaultIpV6AddressNetworkMaskValidFlag() const;
                IpV6AddressNetworkMask              getDefaultIpV6AddressNetworkMask() const;
        virtual string                              getSqlType                      ();
        virtual void                                setupOrm                        (OrmTable *pOrmTable);
        virtual string                              getSqlForCreate                 ();
        virtual void                                getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                                getSqlForUpdate                 (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                                getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                                toString                        (string &valueString);
        virtual void                                fromString                      (const string &valueString);
        virtual ResourceId                          loadFromPlainString             (const string &valueString);
        virtual void                               *getPData                        ();
        virtual void                                setValue                        (const void *pData);
        virtual Attribute                          *clone                           ();
        static  map<string, string>                 getSupportedConversions         ();
        virtual void                                setDefaultValue                 ();
        virtual void                                getCValue                       (WaveCValue *pCValue);
    // Now the data members

    private :
        IpV6AddressNetworkMask *m_pData;
        IpV6AddressNetworkMask  m_defaultIpV6AddressNetworkMask;
        bool                    m_isDefaultIpV6AddressNetworkMaskValid;

    protected :
    public :
};

}

#endif
