/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmComposition.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"

namespace WaveNs
{

OrmComposition::OrmComposition (const string &name, const string &relatedTo, const OrmRelationType &relationType, const bool &canBeEmpty)
    : OrmAssociation (name, relatedTo, relationType, canBeEmpty),
      m_disableValidations (false)
{
}

OrmComposition::~OrmComposition ()
{
}

OrmRelationUmlType OrmComposition::getRelationUmlType () const
{
    return (ORM_RELATION_UML_TYPE_COMPOSITION);
}

bool OrmComposition::getDisableValidations () const
{
    return m_disableValidations;
}

void OrmComposition::setDisableValidations (bool disableValidations)
{
    m_disableValidations = disableValidations;
}

string OrmComposition::getSqlForCreate2 (const string &parentName, const string &schema) const
{
    if (false == getDisableValidations ())
    {
        return OrmAssociation::getSqlForCreate2 (parentName, schema);
    }

    string sqlForCreate2;
    string relatedTo        = getRelatedTo ();
    UI32   parentTableId    = OrmRepository::getTableId (parentName);
    UI32   relatedToTableId = OrmRepository::getTableId (relatedTo);

    switch (getRelationType ())
    {
        case ORM_RELATION_TYPE_ONE_TO_ONE :
            break;

        case ORM_RELATION_TYPE_ONE_TO_MANY :
            sqlForCreate2 += string ("CREATE TABLE ") + schema + string (".t") + parentTableId + getName () + string ("t") + relatedToTableId + "\n";
            sqlForCreate2 += "(\n";
            sqlForCreate2 += "    ownerClassId integer,\n";
            sqlForCreate2 += "    ownerInstanceId bigint,\n";
            sqlForCreate2 += "    relatedToClassId integer,\n";
            sqlForCreate2 += "    relatedToInstanceId bigint\n";
            sqlForCreate2 += ");";

            break;

        default :
            prismAssert (false, __FILE__, __LINE__);
            break;
    }

    return (sqlForCreate2);
}

string OrmComposition::getSqlForDisableValidation (const string &parentName, const string &schema) const
{
    string sqlForAlter;

    switch (getRelationType ())
    {
        case ORM_RELATION_TYPE_ONE_TO_ONE :
            break;

        case ORM_RELATION_TYPE_ONE_TO_MANY :
            if (true == getDisableValidations ())
            {
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " DROP CONSTRAINT " + getOwnerClassFkeyConstraintName (parentName) + ";\n";
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " DROP CONSTRAINT " + getOwnerInstanceFkeyConstraintName (parentName) + ";\n";
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " DROP CONSTRAINT " + getRelatedClassFkeyConstraintName (parentName) + ";\n";
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " DROP CONSTRAINT " + getRelatedInstanceFkeyConstraintName (parentName) + ";\n";
            }

            break;

        default :
            prismAssert (false, __FILE__, __LINE__);
            break;
    }

    return (sqlForAlter);
}

string OrmComposition::getSqlForEnableValidation (const string &parentName, const string &schema) const
{
    string sqlForAlter;
    string relatedTo = getRelatedTo ();

    switch (getRelationType ())
    {
        case ORM_RELATION_TYPE_ONE_TO_ONE :
            break;

        case ORM_RELATION_TYPE_ONE_TO_MANY :
            if (false == getDisableValidations ())
            {
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " ADD CONSTRAINT " + getOwnerClassFkeyConstraintName (parentName) +
                                    " FOREIGN KEY (ownerClassId) REFERENCES " + schema + "." + parentName + "Derivations (objectIdClassId) DEFERRABLE INITIALLY DEFERRED;\n";
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " ADD CONSTRAINT " + getOwnerInstanceFkeyConstraintName (parentName) +
                                    " FOREIGN KEY (ownerInstanceId) REFERENCES " + schema + "." + parentName + "DerivationsInstances (objectIdInstanceId) DEFERRABLE INITIALLY DEFERRED;\n";
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " ADD CONSTRAINT " + getRelatedClassFkeyConstraintName (parentName) +
                                    " FOREIGN KEY (relatedToClassId) REFERENCES " + schema + "." + relatedTo + "Derivations (objectIdClassId) DEFERRABLE INITIALLY DEFERRED;\n";
		        sqlForAlter += "ALTER TABLE " + schema + "." + getAuxilliaryTableName (parentName) + " ADD CONSTRAINT " + getRelatedInstanceFkeyConstraintName (parentName) +
                                    " FOREIGN KEY (relatedToInstanceId) REFERENCES " + schema + "." + relatedTo + "DerivationsInstances (objectIdInstanceId) DEFERRABLE INITIALLY DEFERRED;\n";
            }

            break;

        default :
            prismAssert (false, __FILE__, __LINE__);
            break;
    }

    return (sqlForAlter);
}

}
