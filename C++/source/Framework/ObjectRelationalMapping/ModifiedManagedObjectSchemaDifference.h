/**
 *@file ModifiedManagedObjectSchemaDifference.h 
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 *                    All rights reserved. 
 * Description: This file declares the
 *              class that stores the chagnes that 
 *              have been made to an existing table
 *               
 * Author :     Aashish Akhouri 
 * Date :       10/20/2011 
 */

#ifndef MODIFIEDMANAGEDOBJECTSCHEMADIFFRENCE_H
#define MODIFIEDMANAGEDOBJECTSCHEMADIFFRENCE_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectRelationalMapping/RelationshipInfoFromSchemaDifference.h"
#include "Framework/ObjectRelationalMapping/SchemaDifference.h"
#include <vector>
#include <string>
#include <utility>


namespace WaveNs
{

class ModifiedManagedObjectSchemaDifference
{
    public:
                                                                ModifiedManagedObjectSchemaDifference   (const string & tableName);
                                                               ~ModifiedManagedObjectSchemaDifference   ();

        void                                                    addAddedFieldInfo                       (const pair<string, string> & addedFieldInfo);
        void                                                    addRemovedFieldInfo                     (const pair<string, string> & removedFieldInfo);
        void                                                    addChangedFieldInfo                     (const pair<string, string> & changedFieldInfo);

        const  string &                                         getTableName ()                         const;

        const vector<pair<string, string> > &                   getAddedFieldsInfo                      () const;
        const vector<pair<string, string> > &                   getRemovedFieldsInfo                    () const;
        const vector<pair<string, string> > &                   getChangedFieldsInfo                    () const;

        void                                                    addAddedRelations                       (const RelationshipInfoFromSchemaDifference & relationshipInfo);

        void                                                    addRemovedRelations                     (const RelationshipInfoFromSchemaDifference & relationshipInfo);

        void                                                    addChangedRelations                     (const RelationshipInfoFromSchemaDifference & relationshipInfo);

        const vector<RelationshipInfoFromSchemaDifference> &    getAddedRelations                       ();

        const vector<RelationshipInfoFromSchemaDifference> &    getRemovedRelations                     () const;

        const vector<RelationshipInfoFromSchemaDifference> &    getChangedRelations                     () const;

        void                                                    printContentsForDebugging               ();
     
    private:
        

        string                                                  m_tableName;
        SchemaDifference<pair<string, string> >                 m_fieldSchemaDifferences;   //Captures the simple field
		
        //Changes
        vector<RelationshipInfoFromSchemaDifference>            m_addedRelations;
        vector<RelationshipInfoFromSchemaDifference>            m_removedRelations;
        vector<RelationshipInfoFromSchemaDifference>            m_changedRelations;

};

}

#endif//MODIFIEDMANAGEDOBJECTSCHEMADIFFRENCE_H
