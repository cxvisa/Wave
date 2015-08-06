/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/Attributes/AttributeSqlBetween.h"
#include "Framework/Attributes/AttributeTypes.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

AttributeSqlBetween::AttributeSqlBetween (Attribute *pOperand1, Attribute *pOperand2)
    : Attribute (AttributeType::AttributeTypeSqlBetween)
{
    m_pAttribute1 = pOperand1;
    m_pAttribute2 = pOperand2;
}

AttributeSqlBetween::~AttributeSqlBetween ()
{
    delete m_pAttribute1;
    delete m_pAttribute2;

    m_pAttribute1 = NULL;
    m_pAttribute2 = NULL;
}

bool AttributeSqlBetween::validate () const
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween::validate : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return (false);
}

bool AttributeSqlBetween::isConditionOperatorSupported (AttributeConditionOperator attributeConditionOperator)
{
    bool isSupported = false;

    if (WAVE_ATTRIBUTE_CONDITION_OPERATOR_BETWEEN == attributeConditionOperator || WAVE_ATTRIBUTE_CONDITION_OPERATOR_NOT_BETWEEN == attributeConditionOperator)
    {
        isSupported = true;
    }
    else
    {
        isSupported = false;
    }

    return (isSupported);
}

AttributeSqlBetween &AttributeSqlBetween::operator = (const AttributeSqlBetween &attribute)
{
    Attribute::operator = (attribute);

    return (*this);
}

string AttributeSqlBetween::getSqlType ()
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return "";
}

void AttributeSqlBetween::setupOrm (OrmTable *pOrmTable)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

string AttributeSqlBetween::getSqlForCreate ()
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return "";
}

void AttributeSqlBetween::getSqlForInsert (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::getSqlForUpdate (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::getSqlForSelect (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator)
{
    if (false == isConditionOperatorSupported (attributeConditionOperator))
    {
        trace (TRACE_LEVEL_FATAL, "AttributeSqlBetween::getSqlForSelect : This attribute does not support the condition operator:" + FrameworkToolKit::localize (attributeConditionOperator));
        waveAssert (false, __FILE__, __LINE__);
    }


    if (NULL == m_pAttribute1)
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween::getSqlForSelect : Attributes do not exist!"));
        waveAssert (false, __FILE__, __LINE__);
    }

    if (NULL == m_pAttribute2)
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween::getSqlForSelect : Attributes do not exist!"));
        waveAssert (false, __FILE__, __LINE__);
    }


    string attribute1Name = m_pAttribute1->getAttributeName ();
    string attribute2Name = m_pAttribute2->getAttributeName ();

    if (attribute1Name != attribute2Name)
    {
        trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween::getSqlForSelect : The attributes specified are not for the same coloumn!"));
        waveAssert (false, __FILE__, __LINE__);
    }


    string attribute1Value;
    string attribute2Value;

    m_pAttribute1->toEscapedString (attribute1Value);
    m_pAttribute2->toEscapedString (attribute2Value);

    sqlForSelect += attribute1Name + FrameworkToolKit::localize (attributeConditionOperator) + string ("'") + attribute1Value + string ("'") + string (" AND ") + string ("'") + attribute2Value + string ("'");
}

void AttributeSqlBetween::toString (string &valueString)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::fromString (const string &valueString)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void *AttributeSqlBetween::getPData ()
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return NULL;
}

void AttributeSqlBetween::setValue (const void *pData)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

Attribute *AttributeSqlBetween::clone ()
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return NULL;
}

void AttributeSqlBetween::loadFromPostgresQueryResult (PGresult *pResult, const UI32 &row, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::loadFromPostgresAuxilliaryQueryResult (map<string, PGresult *> &auxilliaryResultsMap, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::updateOrmRelations (const PrismPersistableObject *pPrismPersistableObject)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

WaveManagedObject *AttributeSqlBetween::getComposedManagedObject (const ObjectId &childObjectId)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return NULL;
}

bool AttributeSqlBetween::isDeletableForOperation (const WaveManagedObjectOperation &operation)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);

    return (false);
}

void AttributeSqlBetween::updateKeyString (const PrismPersistableObject *pPrismPersistableObject)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::getRestRowData (string &restRowData)
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

map<string, string> AttributeSqlBetween::getSupportedConversions ()
{
    map<string, string> supportedConversions;
    
    return (supportedConversions);
}

void AttributeSqlBetween::setDefaultValue()
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween:: : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
}

void AttributeSqlBetween::getCValue (WaveCValue *pCValue)
{
    waveAssert (false, __FILE__, __LINE__);
}

bool AttributeSqlBetween::isCurrentValueSameAsDefault () const
{
    trace (TRACE_LEVEL_FATAL, string ("AttributeSqlBetween::isCurrentValueSameAsDefault : This attribute is only for the SQL BETWEEN condition and does not make sense to invoke this method."));
    waveAssert (false, __FILE__, __LINE__);
    return (false);
}

}
