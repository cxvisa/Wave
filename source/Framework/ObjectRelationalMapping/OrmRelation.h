/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ORMRELATION_H
#define ORMRELATION_H

#include "Framework/ObjectRelationalMapping/OrmEntity.h"

#include <string>

using namespace std;

namespace WaveNs
{

typedef enum
{
    ORM_RELATION_TYPE_ONE_TO_ONE,
    ORM_RELATION_TYPE_ONE_TO_MANY
} OrmRelationType;

typedef enum
{
    ORM_RELATION_UML_TYPE_ASSOCIATION,
    ORM_RELATION_UML_TYPE_AGGREGATION,
    ORM_RELATION_UML_TYPE_COMPOSITION
} OrmRelationUmlType;


class OrmRelation : public OrmEntity
{
    private :
    protected :
    public :
                                    OrmRelation                    (const string &name, const string &relatedTo, const OrmRelationType &relationType);
        virtual                    ~OrmRelation                    ();

                string              getRelatedTo           () const;
                OrmRelationType     getRelationType        () const;
        virtual string              getSqlForCreate        (const string &schema) const = 0;
        virtual string              getSqlForCreate2       (const string &parentName, const string &schema) const = 0;

	
        virtual string              getAuxilliaryTableName (const string &parentName) const;
	virtual	string		    getTypeForUpgradeMO	   () const;
        virtual OrmRelationUmlType  getRelationUmlType     () const = 0;
        virtual string              getAlterSqlForOneToOneRelationship              (const string &schema,const string & tableName) const;
        virtual string              getAlterSqlToAddNotNullForOneToOneRelationship  (const string &schema,const string & tableName) const;
        virtual string              getAlterSqlToDropNotNullForOneToOneRelationship (const string &schema,const string & tableName) const;
    // Now the data members

    private :
        string          m_relatedTo;
        OrmRelationType m_relationType;

    protected :
    public :
};

}

#endif // ORMRELATION_H
