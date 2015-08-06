/***************************************************************************
 *   Copyright (C) 2005 - 2010 Vidyasagara Guntaka                         *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Attributes/AttributeNumber.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/Integer.h"
#include "Framework/Utils/BigInteger.h"
#include "Framework/ObjectRelationalMapping/OrmTable.h"
#include "Framework/ObjectRelationalMapping/OrmColumn.h"
#include "Framework/ObjectRelationalMapping/OrmRelation.h"
#include "Framework/ObjectRelationalMapping/OrmAssociation.h"
#include "Framework/ObjectRelationalMapping/OrmAggregation.h"
#include "Framework/ObjectRelationalMapping/OrmComposition.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"

namespace WaveNs
{

AttributeNumber::AttributeNumber (const Number &data, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute          (AttributeType::AttributeTypeNumber, attributeName, attributeUserTag, isOperational),
    m_defaultData        (0),
    m_isDefaultDataValid (false)
{
    m_pData  = new Number();
    *m_pData = data;

    setIsMemoryOwnedByAttribute (true);
}

AttributeNumber::AttributeNumber (const Number &data, const Number &defaultData, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute          (AttributeType::AttributeTypeNumber, attributeName, attributeUserTag, isOperational),
    m_defaultData        (defaultData),
    m_isDefaultDataValid (true)
{
     m_pData = new Number();
    *m_pData = data;

    setIsMemoryOwnedByAttribute (true);
}

AttributeNumber::AttributeNumber (Number *pData, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute          (AttributeType::AttributeTypeNumber, attributeName, attributeUserTag, isOperational),
    m_defaultData        (0),
    m_isDefaultDataValid (false)
{
    m_pData = pData;

    setIsMemoryOwnedByAttribute (false);
}

AttributeNumber::AttributeNumber (Number *pData, const Number &defaultData, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute          (AttributeType::AttributeTypeNumber, attributeName, attributeUserTag, isOperational),
    m_defaultData        (defaultData),
    m_isDefaultDataValid (true)
{
    m_pData = pData;

    setIsMemoryOwnedByAttribute (false);
}

AttributeNumber::AttributeNumber (const AttributeNumber &attribute)
    : Attribute (attribute)
{
    m_pData              = new Number;
    *m_pData             = attribute.getValue ();
    m_defaultData        = attribute.getDefaultValue();
    m_isDefaultDataValid = attribute.getIsDefaultDataValidFlag();
    setIsMemoryOwnedByAttribute (true);
}

AttributeNumber::~AttributeNumber ()
{
    if (true == (getIsMemoryOwnedByAttribute ()))
    {
        delete m_pData;
    }
}

AttributeNumber &AttributeNumber::operator = (const AttributeNumber &attribute)
{
    Attribute::operator = (attribute);

    setValue (attribute.getValue ());

    m_defaultData        = attribute.getDefaultValue();
    m_isDefaultDataValid = attribute.getIsDefaultDataValidFlag();

    return (*this);
}

Number AttributeNumber::getValue () const
{
    if (true == (validate ()))
    {
        return (*m_pData);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeNumber::getValue : Invalid Cast of the underlying Attribute."));
        waveAssert (false, __FILE__, __LINE__);
        return (0);
    }
}

void AttributeNumber::setValue (const Number &data)
{
    if (true == (validate ()))
    {
        *m_pData = data;
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeNumber::setValue : Invalid Cast of the underlying Attribute."));
        waveAssert (false, __FILE__, __LINE__);
    }
}

bool AttributeNumber::validate () const
{
    waveAssert (AttributeType::AttributeTypeNumber == (getAttributeType ()), __FILE__, __LINE__);

    if (AttributeType::AttributeTypeNumber == (getAttributeType ()))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool AttributeNumber::isConditionOperatorSupported (AttributeConditionOperator attributeConditionOperator)
{
    bool isSupported = false;

    if (WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL                     == attributeConditionOperator ||
        WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_EQUAL                 == attributeConditionOperator ||
        WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN              == attributeConditionOperator ||
        WAVE_ATTRIBUTE_CONDITION_OPERATOR_GREATER_THAN_OR_EQUAL_TO  == attributeConditionOperator ||
        WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN                 == attributeConditionOperator ||
        WAVE_ATTRIBUTE_CONDITION_OPERATOR_LESS_THAN_OR_EQUAL_TO     == attributeConditionOperator)
    {
        isSupported = true;
    }
    else
    {
        isSupported = false;
    }

    return (isSupported);
}

string AttributeNumber::getSqlType ()
{
    return ("numeric");
}

void AttributeNumber::setupOrm (OrmTable *pOrmTable)
{
    pOrmTable->addColumn (new OrmColumn (getAttributeName (), getSqlType (), getAttributeTypeString (), getIsPrimary ()));
}

string AttributeNumber::getSqlForCreate ()
{
    return (getAttributeName () + " numeric");
}

void AttributeNumber::getSqlForInsert (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst)
{
    string tempString;

    toString (tempString);

    sqlForInsert += string (",") + tempString;

    sqlForPreValues += string (",") + getAttributeName ();
}

void AttributeNumber::getSqlForUpdate (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst)
{
    string tempString;

    toString (tempString);

    sqlForUpdate += "," + getAttributeName () + " = " + tempString;
}

void AttributeNumber::getSqlForSelect (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator)
{
    if (false == isConditionOperatorSupported (attributeConditionOperator))
    {
        trace (TRACE_LEVEL_FATAL, "AttributeNumber::getSqlForSelect : This attribute does not support the condition operator:" + FrameworkToolKit::localize (attributeConditionOperator));
        waveAssert (false, __FILE__, __LINE__);
    }

    string tempString;

    toString (tempString);

    sqlForSelect += getAttributeName () + FrameworkToolKit::localize (attributeConditionOperator) + tempString;
}

void AttributeNumber::toString (string &valueString)
{
    char buffer[128] = {0};

    snprintf (buffer, 128, "%Lf", (long double) ((getValue ()).getLd ()));

    valueString = string (buffer);
}

void AttributeNumber::fromString (const string &valueString)
{
    setValue (strtoll (valueString.c_str (), NULL, 10));
}

ResourceId AttributeNumber::loadFromPlainString (const string &valueString)
{
    ResourceId status = WAVE_MESSAGE_ERROR;
    char*   firstInvalidCharacterPosition = NULL;

    Number value = strtold (valueString.c_str (), &(firstInvalidCharacterPosition));

    // Check if the string has invalid character
    if ( *firstInvalidCharacterPosition == '\0' )
    {
        setValue (value);
        status = WAVE_MESSAGE_SUCCESS;
    }

    if (WAVE_MESSAGE_ERROR == status)
    {
        trace (TRACE_LEVEL_ERROR, string("AttributeNumber::loadFromPlainString : Improper format of AttributeNumber in string"));
    }

    return status ;
}

void *AttributeNumber::getPData ()
{
    return (m_pData);
}

void AttributeNumber::setValue (const void *pData)
{
    *m_pData = *(reinterpret_cast<const Number *> (pData));
}

Attribute *AttributeNumber::clone ()
{
    AttributeNumber *pAttributeNumber = new AttributeNumber (*this);

    return (pAttributeNumber);
}

map<string, string> AttributeNumber::getSupportedConversions ()
{
    map<string, string> supportedConversions;

    supportedConversions["WAVE_ATTRIBUTE_TYPE_WAVE_MESSAGE_TYPE"] = "WAVE_ATTRIBUTE_TYPE_WAVE_MESSAGE_TYPE";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_WAVE_MESSAGE_PRIORITY"] = "WAVE_ATTRIBUTE_TYPE_WAVE_MESSAGE_PRIORITY";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_PRISM_SERVICE_ID"] = "WAVE_ATTRIBUTE_TYPE_PRISM_SERVICE_ID";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_SERIALIZABLE_OBJECT_TYPE"] = "WAVE_ATTRIBUTE_TYPE_SERIALIZABLE_OBJECT_TYPE";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_LOCATIONID"] = "WAVE_ATTRIBUTE_TYPE_LOCATIONID";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_SI32"] = "WAVE_ATTRIBUTE_TYPE_SI32";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_SI16"] = "WAVE_ATTRIBUTE_TYPE_SI16";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_SI8"] = "WAVE_ATTRIBUTE_TYPE_SI8";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_UI64"] = "WAVE_ATTRIBUTE_TYPE_UI64";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_UI32"] = "WAVE_ATTRIBUTE_TYPE_UI32";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_UI16"] = "WAVE_ATTRIBUTE_TYPE_UI16";
    supportedConversions["WAVE_ATTRIBUTE_TYPE_UI8"] = "WAVE_ATTRIBUTE_TYPE_UI8";

    return (supportedConversions);
}

bool AttributeNumber::isCurrentValueSameAsDefault () const
{
    bool isDefault = false ;

    if ( getIsDefaultDataValidFlag() )
    {
        if ( getDefaultValue() == getValue() )
        {
            isDefault = true;
        }
    }

    return (isDefault);
}

bool AttributeNumber::getIsDefaultDataValidFlag() const
{
    return (m_isDefaultDataValid);
}

Number AttributeNumber::getDefaultValue() const
{
    return (m_defaultData);
}

void AttributeNumber::setDefaultValue()
{
    if(true == m_isDefaultDataValid)
    {
        setValue(&m_defaultData);
    }
    else
    {
        *m_pData = 0;
    }
}

void AttributeNumber::getCValue(WaveCValue *pCValue)
{
    trace (TRACE_LEVEL_FATAL, "AttributeNumber::getCValue : NOT YET IMPLEMENTED.");
    waveAssert (false, __FILE__, __LINE__);
    //wave_cvalue_set_number (pCValue, getValue ());
}


}

