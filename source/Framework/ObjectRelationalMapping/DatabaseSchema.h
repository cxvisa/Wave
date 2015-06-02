/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman					   *
 ***************************************************************************/

#ifndef DATABASESCHEMA_H
#define DATABASESCHEMA_H

#include "Framework/ObjectRelationalMapping/ManagedObjectSchemaInfoRepository.h"
#include "Framework/ObjectModel/SerializableObject.h"
#include <vector>
#include <string>


namespace WaveNs
{

class DatabaseSchema : virtual public SerializableObject
{
	
	private:
	public:
                                DatabaseSchema ();
                               ~DatabaseSchema ();

                bool            operator==              (const DatabaseSchema &rhsDbSchema);
                bool            isConvertibleTo         (const DatabaseSchema &rhsDbSchema);

        static  ResourceId      getDatabaseSchema       (DatabaseSchema &databaseSchema);
                
                void            setManagedObjectNames   (const vector<string> managedObjectNames);
                vector<string>  getManagedObjectNames   () const;
                
                void            setFieldNamesStrings    (const vector<string> fieldNamesStrings);
                vector<string>  getFieldNamesStrings    () const;

                void            setFieldNamesTypes      (const vector<string> fieldNamesTypes);
                vector<string>  getFieldNamesTypes      () const;
                
                void            setClassIds             (const vector<UI32> classIds);
                vector<UI32>    getClassIds             () const;

                void            setParentTableIds       (const vector<UI32> parentTableIds);
                vector<UI32>    getParentTableIds       () const;
                
                void            setUserDefinedKeyCombinationsFieldNames (const vector<string> userDefinedKeyCombinationsFieldNames);
                vector<string>  getUserDefinedKeyCombinationsFieldNames () const;

                void            setUserDefinedKeyCombinationsFieldTypes (const vector<string> userDefinedKeyCombinationsFieldNames);
                vector<string>  getUserDefinedKeyCombinationsFieldTypes () const;
                
                void            setFieldNamesExpandedTypes  (const vector<string> managedObjectNames);
                vector<string>  getFieldNamesExpandedTypes  () const;
        
                void            setIsLocalManagedObjectInfo (const vector<bool> isLocalManagedObjects);
                vector<bool>    getIsLocalManagedObjectInfo () const;

                void            setDerivedFromClassNames    (const vector<string> derivedFromClassNames);
                vector<string>  getDerivedFromClassNames    () const;

                void            convertDatabaseSchemaToManagedObjectSchemaInfoRepository  (ManagedObjectSchemaInfoRepository &dBSchemaRepository) const;

	protected:
        virtual void            setupAttributesForSerialization                         ();
        virtual void            setupAttributesForSerializationInAttributeOrderFormat   ();

    // Data Members    
    private:
        vector<string>     m_managedObjectNames;
        vector<string>     m_fieldNamesStrings;
        vector<string>     m_fieldNamesTypes;
        vector<UI32>       m_classIds;
        vector<UI32>       m_parentTableIds;
        vector<string>     m_userDefinedKeyCombinationsFieldNames;
        vector<string>     m_userDefinedKeyCombinationsFieldTypes;
        vector<string>     m_fieldNamesExpandedTypes;
        vector<bool>       m_isLocalManagedObjectInfo;
        vector<string>     m_derivedFromClassNames;

	public:
	protected:

};

}

#endif
