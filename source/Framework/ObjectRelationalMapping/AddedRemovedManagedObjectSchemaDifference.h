/**
 *@file AddedRemovedManagedObjectSchemaDifference.h 
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 *                    All rights reserved. 
 * Description: This file declares the information regarding the tables added to
 *              the new schema and tables removed from the old schema
 *              
 *               
 * Author :     Aashish Akhouri 
 * Date :       10/20/2011 
 */

#ifndef ADDEDREMOVEDMANAGEDOBJECTSCHEMADIFFRENCE_H
#define ADDEDREMOVEDMANAGEDOBJECTSCHEMADIFFRENCE_H

#include <string>
#include "Framework/Types/Types.h"
#include "Framework/ObjectRelationalMapping/RelationshipInfoFromSchemaDifference.h"

namespace WaveNs
{

class AddedRemovedManagedObjectSchemaDifference
{
    private:
    protected:
    public:

                                                        AddedRemovedManagedObjectSchemaDifference   (const string & tableName);
                                                       ~AddedRemovedManagedObjectSchemaDifference   ();

    void                                                addRelations                                (const RelationshipInfoFromSchemaDifference &  relationshipInfo);
    const vector<RelationshipInfoFromSchemaDifference>& getRelations                                () const;

    const string &                                      getTableName () const;
    void                                                printContentsForDebugging                   ();

    private:
        string                                          mTableName;
        vector<RelationshipInfoFromSchemaDifference>    mRelations;
    protected:
    public:

};

}

#endif//ADDEDREMOVEDMANAGEDOBJECTSCHEMADIFFRENCE_H
