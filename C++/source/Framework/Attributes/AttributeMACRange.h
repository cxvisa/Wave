/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil Channaveerasetty                                        *
 ***************************************************************************/

#ifndef ATTRIBUTEMACRANGE_H
#define ATTRIBUTEMACRANGE_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/Types/MacRange.h"
#include "WaveResourceIdEnums.h"

namespace WaveNs
{

class AttributeMACRange : public Attribute
{
    private :
        virtual bool                validate                        () const;

    protected :
    public :

                                    AttributeMACRange               (const MACRange &data, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);

                                    AttributeMACRange               (const MACRange &data, const MACRange &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);

                                    AttributeMACRange               (MACRange *pData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);

                                    AttributeMACRange               (MACRange *pData, const MACRange &defaultData, const string &attributeName = "", const UI32 &attributeUserTag = 0, const bool &isOperational = false);

                                    AttributeMACRange               (const AttributeMACRange &attribute);
        virtual                    ~AttributeMACRange               ();
                AttributeMACRange  &operator =                      (const AttributeMACRange &attribute);
                MACRange            getValue                        () const;
                void                setValue                        (const MACRange &data);
        virtual string              getSqlType                      ();
        virtual void                setupOrm                        (OrmTable *pOrmTable);
        virtual string              getSqlForCreate                 ();
        virtual void                getSqlForInsert                 (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);

        virtual void                getSqlForUpdate                 (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                getSqlForSelect                 (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                toString                        (string &valueString);
        virtual void                fromString                      (const string &valueString);
        virtual ResourceId          loadFromPlainString             (const string &valueString);
        virtual void               *getPData                        ();
        virtual void                setValue                        (const void *pData);
        virtual Attribute          *clone                           ();
        static  map<string, string> getSupportedConversions         ();

                bool                isCurrentValueSameAsDefault     () const;
                MACRange            getDefaultData                  () const;
                bool                getIsDefaultDataValidFlag       (void) const;
        virtual void                setDefaultValue                 ();
        virtual void                getCValue                       (WaveCValue *pCValue);
    // Now the data members

    private :
        MACRange *m_pData;
        MACRange  m_defaultData;
        bool      m_isDefaultDataValid; // if this is true, then default value is valid

    protected :
    public :
};

}

#endif  //ATTRIBUTEMACRange_H
