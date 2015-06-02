/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmRelation.h"

namespace WaveNs
{

OrmRelation::OrmRelation (const string &name, const string &relatedTo, const OrmRelationType &relationType)
    : OrmEntity (name),
      m_relatedTo    (relatedTo),
      m_relationType (relationType)
{
}

OrmRelation::~OrmRelation ()
{
}

string OrmRelation::getRelatedTo () const
{
    return (m_relatedTo);
}

OrmRelationType OrmRelation::getRelationType () const
{
    return (m_relationType);
}

string OrmRelation::getTypeForUpgradeMO () const
{
	string upgradeType;

	switch (getRelationUmlType()) {
	    case ORM_RELATION_UML_TYPE_ASSOCIATION:
		    upgradeType = "a-";
		    break;
	    case ORM_RELATION_UML_TYPE_AGGREGATION:
		    upgradeType = "g-";
		    break;
	    case ORM_RELATION_UML_TYPE_COMPOSITION:
		    upgradeType = "c-";
	}
	
	if (getRelationType () == ORM_RELATION_TYPE_ONE_TO_MANY)
		upgradeType += "m-";
	else
		upgradeType += "1-";

	upgradeType += m_relatedTo;

	return (upgradeType);
}

string OrmRelation::getAuxilliaryTableName (const string &parentName) const
{
    return ("");
}

string OrmRelation::getAlterSqlForOneToOneRelationship(const string &schema,const string & tableName) const
{
    return ("");
}

string OrmRelation::getAlterSqlToAddNotNullForOneToOneRelationship (const string &schema,const string & tableName) const
{
    return ("");
}

string OrmRelation::getAlterSqlToDropNotNullForOneToOneRelationship (const string &schema,const string & tableName) const
{
    return ("");
}

}
