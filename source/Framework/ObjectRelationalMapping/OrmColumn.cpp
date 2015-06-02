/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmColumn.h"

namespace WaveNs
{

OrmColumn::OrmColumn (const string &name, const string &sqlType, const string &typeForUpgradeMO, const bool &isPrimary)
    :   OrmEntity           (name),
        m_sqlType           (sqlType),
        m_typeForUpgradeMO  (typeForUpgradeMO),
        m_isPrimary         (isPrimary)
{
}

OrmColumn::~OrmColumn ()
{
}

string OrmColumn::getSqlType () const
{
    return (m_sqlType);
}

string OrmColumn::getTypeForUpgradeMO () const
{
    return (m_typeForUpgradeMO);
}

string OrmColumn::getSqlForCreate (const string &schema) const
{
    return ("    " + getName () + " " + m_sqlType + (m_isPrimary ? " PRIMARY KEY" : ""));
}

bool OrmColumn::getIsPrimary () const
{
    return (m_isPrimary);
}

void OrmColumn::setIsPrimary (const bool &isPrimary)
{
    m_isPrimary = isPrimary;
}

}

