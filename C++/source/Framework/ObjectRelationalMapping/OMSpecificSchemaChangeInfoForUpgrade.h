/****************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                 *
 *   All rights reserved.                                                   *
 *   Author : Pritee Kadu         					                        *
 ***************************************************************************/

#ifndef OMSPECIFICSCHEMACHANGEINFOFORUPGRADE_H
#define OMSPECIFICSCHEMACHANGEINFOFORUPGRADE_H

#include "Framework/ObjectRelationalMapping/ManagedObjectSchemaInfoRepository.h"
#include <vector>
#include <string>


namespace WaveNs
{

class OMSpecificSchemaChangeInfoForUpgrade 
{
	
	private:
	public:
                                OMSpecificSchemaChangeInfoForUpgrade ();
                               ~OMSpecificSchemaChangeInfoForUpgrade ();

                
                string                                              getObjectManagerName            () const;
                void                                                setObjectManagerName            (const string& fieldNamesStrings);
                vector<string>                                      getAddedManagedObjectNames      () const;
                void                                                setAddedManagedObjectNames      (const vector<string>& fieldNamesTypes);
                vector<string>                                      getRemovedManagedObjectNames    () const;
                void                                                setRemovedManagedObjectNames    (const vector<string>& fieldNamesTypes);
                map<string, ModifiedManagedObjectSchemaDifference*>& getModifiedManagedObjectInfo   ();
                void                                                setModifiedManagedObjectInfo    (const map<string, ModifiedManagedObjectSchemaDifference*> &modifiedMoInfo);
                vector<string>                                      getModifiedManagedObjectNames   () const;
                ModifiedManagedObjectSchemaDifference*              getDifferenceSchemaInfoForMo    (const string& managedObjectName) const;
        

	protected:

    // Data Members    
    private:
                string                                              m_name;
                vector<string>                                      m_addedManagedObjectNames;
                vector<string>                                      m_removedManagedObjectNames;
                map<string, ModifiedManagedObjectSchemaDifference*> m_modifiedManagedObjectSchemaInfo;

	public:
	protected:

};

}

#endif
