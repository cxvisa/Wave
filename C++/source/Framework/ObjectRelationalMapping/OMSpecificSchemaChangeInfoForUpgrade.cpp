/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Kadu                            					   *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OMSpecificSchemaChangeInfoForUpgrade.h"
#include "Framework/Database/DatabaseStandaloneTransaction.h"
#include "Framework/ObjectRelationalMapping/ManagedObjectSchemaInfoRepository.h"
#include "Framework/ObjectRelationalMapping/ManagedObjectSchemaInfo.h"
#include "Framework/Core/PrismFrameworkObjectManagerInitializeWorker.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

using namespace std;

namespace WaveNs
{

OMSpecificSchemaChangeInfoForUpgrade::OMSpecificSchemaChangeInfoForUpgrade ()
{
}

OMSpecificSchemaChangeInfoForUpgrade::~OMSpecificSchemaChangeInfoForUpgrade ()
{
}

void OMSpecificSchemaChangeInfoForUpgrade::setObjectManagerName (const string& objectManagerName)
{
    m_name = objectManagerName;
}

string OMSpecificSchemaChangeInfoForUpgrade::getObjectManagerName () const
{
    return (m_name);
}

void OMSpecificSchemaChangeInfoForUpgrade::setAddedManagedObjectNames (const vector<string>& managedObjectNames)
{
    m_addedManagedObjectNames = managedObjectNames;
}

vector<string> OMSpecificSchemaChangeInfoForUpgrade::getAddedManagedObjectNames () const
{
    return (m_addedManagedObjectNames);
}

void OMSpecificSchemaChangeInfoForUpgrade::setRemovedManagedObjectNames (const vector<string>& managedObjectNames)
{
    m_removedManagedObjectNames = managedObjectNames;
}

vector<string> OMSpecificSchemaChangeInfoForUpgrade::getRemovedManagedObjectNames () const
{
    return (m_removedManagedObjectNames);
}

void OMSpecificSchemaChangeInfoForUpgrade::setModifiedManagedObjectInfo (const map<string, ModifiedManagedObjectSchemaDifference*>& modifiedManagedObjects)
{
    m_modifiedManagedObjectSchemaInfo = modifiedManagedObjects;
}

map<string, ModifiedManagedObjectSchemaDifference*>& OMSpecificSchemaChangeInfoForUpgrade::getModifiedManagedObjectInfo ()
{
    return (m_modifiedManagedObjectSchemaInfo);
}

/*
vector<string> OMSpecificSchemaChangeInfoForUpgrade::getModifiedManagedObjectNames () const
{
    
}
*/
ModifiedManagedObjectSchemaDifference* OMSpecificSchemaChangeInfoForUpgrade::getDifferenceSchemaInfoForMo (const string& moName) const
{
    map <string, ModifiedManagedObjectSchemaDifference*>::const_iterator iter = m_modifiedManagedObjectSchemaInfo.find (moName);

    if (m_modifiedManagedObjectSchemaInfo.end () == iter)
    {
        trace (TRACE_LEVEL_WARN, "OMSpecificSchemaChangeInfoForUpgrade::getDifferenceInfoForMo: [" + moName + "] is not a modified managedObject. Please, check the same.");
        waveAssert (false, __FILE__, __LINE__);
    }
        
    return (iter->second);    
}

}
