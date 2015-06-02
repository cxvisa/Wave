/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef RELATIONSHIPENTRY_H
#define RELATIONSHIPENTRY_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectRelationalMapping/OrmRelation.h"

#include <string>

using namespace std;

namespace WaveNs
{

class RelationshipEntry
{
    private :
    protected :
    public :
                                    RelationshipEntry           (const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual                    ~RelationshipEntry           ();

                void                getSqlForInsertIntoParent   (string &sql);
                void                getSqlForDeleteFromParent   (string &sql);

        const   string             &getParentClassName          () const;
        const   string             &getChildClassName           () const;
        const   string             &getRelationshipName         () const;
                string              getRelationshipTableName    () const;
                OrmRelationType     getRelationType             () const;
                OrmRelationUmlType  getRelationUmlType          () const;
        // Now the data members

    private :
        string              m_parentClassName;
        string              m_childClassName;
        string              m_relationshipName;
        ObjectId            m_parentObjectId;
        ObjectId            m_childObjectId;
        OrmRelationType     m_ormRelationType;
        OrmRelationUmlType  m_ormRelationUmlType; 

    protected :
    public :
};

}

#endif // RELATIONSHIPENTRY_H
