/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectAsynchronousPluginContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveManagedObjectAsynchronousPluginContext::WaveManagedObjectAsynchronousPluginContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext)
{
}

WaveManagedObjectAsynchronousPluginContext::~WaveManagedObjectAsynchronousPluginContext ()
{

}

vector<UI32> WaveManagedObjectAsynchronousPluginContext::getAttributeUserTags () const
{
    return (m_attributeUserTags);
}

void WaveManagedObjectAsynchronousPluginContext::setAttributeUserTags(const vector<UI32> &attributeUserTags)
{
    m_attributeUserTags = attributeUserTags;
}

vector<string> WaveManagedObjectAsynchronousPluginContext::getAttributeNames () const
{
    return (m_attributeNames);
}

void WaveManagedObjectAsynchronousPluginContext::setAttributeNames (const vector<string> &attributeNames)
{

    m_attributeNames = attributeNames;
}

vector<string> WaveManagedObjectAsynchronousPluginContext::getAttributeValues () const
{
    return (m_attributeValues);
}

void WaveManagedObjectAsynchronousPluginContext::setAttributeValues(const vector< string >& attributeValues)
{
    m_attributeValues = attributeValues;
}

vector<Attribute *> WaveManagedObjectAsynchronousPluginContext::getAttributes () const
{
    return (m_attributes);
}

void WaveManagedObjectAsynchronousPluginContext::setAttributeVector (vector<Attribute *> attributes)
{
    m_attributes = attributes;
}

void WaveManagedObjectAsynchronousPluginContext::addToAttributeVector (Attribute *pattribute)
{
    m_attributes.push_back(pattribute);
}

void WaveManagedObjectAsynchronousPluginContext::setManagedObjectName (const string &managedObjectName)
{
    m_managedObjectName = managedObjectName;
}

string WaveManagedObjectAsynchronousPluginContext::getManagedObjectName () const
{
    return (m_managedObjectName);
}

UI32 WaveManagedObjectAsynchronousPluginContext::getGroupCode () const
{
    return (m_groupCode);
}

void WaveManagedObjectAsynchronousPluginContext::setGroupCode (UI32 groupCode)
{
    m_groupCode = groupCode;
}

void WaveManagedObjectAsynchronousPluginContext::setParentManagedObjectNames ( const vector<string> &parentManagedObjectNames)
{
    m_parentManagedObjectNames = parentManagedObjectNames;
}

void WaveManagedObjectAsynchronousPluginContext::getParentManagedObjectNames ( vector<string> &parentManagedObjectNames) const
{
    parentManagedObjectNames = m_parentManagedObjectNames;
}


UpdateNewAttributeInManagedObjectContext::UpdateNewAttributeInManagedObjectContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveManagedObjectAsynchronousPluginContext (pCaller, pCallback, pCallerContext)
{
}

UpdateNewAttributeInManagedObjectContext::~UpdateNewAttributeInManagedObjectContext ()
{
}

vector<string>UpdateNewAttributeInManagedObjectContext::getNewAttributeNames () const
{
    return (m_newAttributeNames);
}

void UpdateNewAttributeInManagedObjectContext::addNewAttributeName (const string &attributeName)
{
    m_newAttributeNames.push_back (attributeName);
}

GetHardwareConfigurationDetailsContext::GetHardwareConfigurationDetailsContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveManagedObjectAsynchronousPluginContext (pCaller, pCallback, pCallerContext),
      m_isUpdateBackend (false),
      m_clientName (""),
      m_pOperateOnWaveManagedObject (NULL)
{
}

GetHardwareConfigurationDetailsContext::GetHardwareConfigurationDetailsContext (WaveManagedObject *pOperateOnWaveManagedObject , WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveManagedObjectAsynchronousPluginContext (pCaller, pCallback, pCallerContext),
    m_isUpdateBackend (false),
    m_clientName (""),
    m_pOperateOnWaveManagedObject(pOperateOnWaveManagedObject)
{
}

GetHardwareConfigurationDetailsContext::~GetHardwareConfigurationDetailsContext ()
{
}

void GetHardwareConfigurationDetailsContext::setIsUpdateBackend (bool isUpdateBackend)
{
    m_isUpdateBackend = isUpdateBackend;
}

bool GetHardwareConfigurationDetailsContext::getIsUpdateBackend ()
{
    return (m_isUpdateBackend);
}

void GetHardwareConfigurationDetailsContext::setClientName (const string &clientName)
{
    m_clientName = clientName;
}

void GetHardwareConfigurationDetailsContext::getClientName (string &clientName) const
{
    clientName = m_clientName;
}

void GetHardwareConfigurationDetailsContext::setAttributeNamesGroupCodeMap (const map <string, UI32> &attributeNamesGroupCodeMap)
{
    m_attributeNamesGroupCodeMap = attributeNamesGroupCodeMap;
}

map <string, UI32> GetHardwareConfigurationDetailsContext::getAttributeNamesGroupCodeMap () const
{
    return (m_attributeNamesGroupCodeMap);
}

void GetHardwareConfigurationDetailsContext::setGroupCodeBackendNamesMap (const map <UI32, string> &groupCodeBackendNamesMap)
{
    m_groupCodeBackendNamesMap = groupCodeBackendNamesMap;
}

map <UI32, string> GetHardwareConfigurationDetailsContext::getGroupCodeBackendNamesMap () const
{
    return (m_groupCodeBackendNamesMap);
}

string GetHardwareConfigurationDetailsContext::getClientNameForGroup ( const UI32 groupCode )
{
    string clientName;
    map <UI32, string>::iterator element;
    element = m_groupCodeBackendNamesMap.find( groupCode );
    
    if ( m_groupCodeBackendNamesMap.end() != element )
    {
        clientName = element->second;
    }

    return (clientName);
}

void GetHardwareConfigurationDetailsContext::setGroupCodeAttributeGroupMap (const map <UI32, vector <string> > &groupCodeAttributeGroupMap)
{
    m_groupCodeAttributeGroupMap = groupCodeAttributeGroupMap;
}

map <UI32, vector <string> > GetHardwareConfigurationDetailsContext::getGroupCodeAttributeGroupMap () const
{
    return (m_groupCodeAttributeGroupMap);
}

vector<string> GetHardwareConfigurationDetailsContext::getAttributeNamesForGroup ( const UI32 &groupCode )
{
    vector<string> attributeNames;

    map <UI32, vector <string> >::iterator element;
    element = m_groupCodeAttributeGroupMap.find(groupCode);

    if ( m_groupCodeAttributeGroupMap.end() != element )
    {
        attributeNames = element->second;
    }
    
    return (attributeNames);
}
void GetHardwareConfigurationDetailsContext::setAttributeNameBackendNameMap (const map <string, string> &attributeNameBackendNameMap)
{
    m_attributeNamesBackendNamesMap = attributeNameBackendNameMap;
}

map <string, string> GetHardwareConfigurationDetailsContext::getAttributeNameBackendNameMap () const
{
    return (m_attributeNamesBackendNamesMap);
}


WaveManagedObject* GetHardwareConfigurationDetailsContext::getPOperateOnWaveManagedObject ()
{
    return (m_pOperateOnWaveManagedObject);
}

void GetHardwareConfigurationDetailsContext::setPOperateOnWaveManagedObject (WaveManagedObject *pOperateOnWaveManagedObject)
{
    m_pOperateOnWaveManagedObject = pOperateOnWaveManagedObject;
}


IsAssociatedManagedObjectToBeCreatedContext::IsAssociatedManagedObjectToBeCreatedContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveManagedObjectAsynchronousPluginContext (pCaller, pCallback, pCallerContext)
{
}

IsAssociatedManagedObjectToBeCreatedContext::~IsAssociatedManagedObjectToBeCreatedContext ()
{

}

WaveMessage *IsAssociatedManagedObjectToBeCreatedContext::getMessage () const
{
    return (m_pMessage);
}

void IsAssociatedManagedObjectToBeCreatedContext::setMessage(WaveMessage *pMessage)
{
    m_pMessage = pMessage;
}

string IsAssociatedManagedObjectToBeCreatedContext::getAssociatedAttributeName  () const
{
    return (m_associatedAttributeName);
}

void  IsAssociatedManagedObjectToBeCreatedContext::setAssociatedAttributeName  (const string &associatedAttributeName)
{
    m_associatedAttributeName = associatedAttributeName;
}

string IsAssociatedManagedObjectToBeCreatedContext::getAssociatedClassName  () const
{
    return (m_associatedClassName);
}

void IsAssociatedManagedObjectToBeCreatedContext::setAssociatedClassName  (const string &associatedClassName)
{
    m_associatedClassName = associatedClassName;
}


string  IsAssociatedManagedObjectToBeCreatedContext::getAssociatedAttributeValue () const
{
    return (m_associatedAttributeValue);
}

void  IsAssociatedManagedObjectToBeCreatedContext::setAssociatedAttributeValue (const string &associatedAttributeValue)
{
    m_associatedAttributeValue = associatedAttributeValue;

}

UI32 IsAssociatedManagedObjectToBeCreatedContext::getAttributeIndex () const
{
    return (m_attributeIndex);
}

void IsAssociatedManagedObjectToBeCreatedContext::setAttributeIndex (const UI32 attributeIndex)
{
    m_attributeIndex = attributeIndex;

}

bool IsAssociatedManagedObjectToBeCreatedContext::getIsAssociatedMOToBeCreated () const
{
    return (m_isAssociatedMOToBeCreated);
}

void IsAssociatedManagedObjectToBeCreatedContext::setIsAssociatedMOToBeCreated (const bool isAssociatedMOToBeCreated)
{
    m_isAssociatedMOToBeCreated = isAssociatedMOToBeCreated;

}

GetHardwareConfigurationDetailsForPostbootContext::GetHardwareConfigurationDetailsForPostbootContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : GetHardwareConfigurationDetailsContext(pCaller, pCallback, pCallerContext)
{   
}

GetHardwareConfigurationDetailsForPostbootContext::GetHardwareConfigurationDetailsForPostbootContext (string managedObjectName, string passName, vector<WaveManagedObject *> *pWaveManagedObjects, WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext) : GetHardwareConfigurationDetailsContext(pCaller, pCallback, pCallerContext)
{
    m_passName = passName;
    m_pWaveManagedObjects = pWaveManagedObjects;    
    setManagedObjectName ( managedObjectName );
}

GetHardwareConfigurationDetailsForPostbootContext::GetHardwareConfigurationDetailsForPostbootContext (string managedObjectName, string passName, vector<WaveManagedObject *> *pWaveManagedObjects, const map<UI32, bool> &groupCodeChoiceFlag,  map<UI32, map<UI32, vector<UI32> > > &choiceCaseGroup, WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext) : GetHardwareConfigurationDetailsContext(pCaller, pCallback, pCallerContext)
{
    m_passName = passName;
    m_pWaveManagedObjects = pWaveManagedObjects;
    setManagedObjectName ( managedObjectName );
    m_groupCodeChoiceFlag = groupCodeChoiceFlag;
    m_choiceCaseGroup = choiceCaseGroup;
}

GetHardwareConfigurationDetailsForPostbootContext::~GetHardwareConfigurationDetailsForPostbootContext ()
{
}   

void GetHardwareConfigurationDetailsForPostbootContext::setPassName ( const string &passName )
{
    m_passName = passName;
}   
    
string GetHardwareConfigurationDetailsForPostbootContext::getPassName ( ) const
{
    return( m_passName );
}   
    
vector<WaveManagedObject *>* GetHardwareConfigurationDetailsForPostbootContext::getWaveManagedObjects ( )
{
    return ( m_pWaveManagedObjects );
}

void GetHardwareConfigurationDetailsForPostbootContext::setWaveManagedObjects ( vector<WaveManagedObject *>* pWaveManagedObjects )
{
    m_pWaveManagedObjects = pWaveManagedObjects;
}

void GetHardwareConfigurationDetailsForPostbootContext::setGroupCodeChoiceFlag ( const map<UI32, bool> &groupCodeChoiceFlag)
{
    m_groupCodeChoiceFlag = groupCodeChoiceFlag;
}

void GetHardwareConfigurationDetailsForPostbootContext::getGroupCodeChoiceFlag ( map<UI32, bool> &groupCodeChoiceFlag) const
{
    groupCodeChoiceFlag = m_groupCodeChoiceFlag;
}

void GetHardwareConfigurationDetailsForPostbootContext::setChoiceCaseGroup ( const map<UI32, map<UI32, vector<UI32> > > &choiceCaseGroup)
{
    m_choiceCaseGroup = choiceCaseGroup;
}
 
void GetHardwareConfigurationDetailsForPostbootContext::getChoiceCaseGroup ( map<UI32, map<UI32, vector<UI32> > > &choiceCaseGroup) const
{
    choiceCaseGroup = m_choiceCaseGroup;
}
 
void GetHardwareConfigurationDetailsForPostbootContext::getCaseGroupsForChoiceGroup ( const UI32 &choiceGroup, const UI32 &userTag, vector<UI32> &caseGroups ) const
{
    map<UI32, map<UI32, vector<UI32> > >::const_iterator elementChoiceCaseGroup = m_choiceCaseGroup.find( choiceGroup );

    if ( elementChoiceCaseGroup != m_choiceCaseGroup.end() )
    {
        map<UI32, vector<UI32> >::const_iterator elementUserTagCaseGroup = (elementChoiceCaseGroup->second).find(userTag);

        if ( elementUserTagCaseGroup != (elementChoiceCaseGroup->second).end() )
        {
            caseGroups = elementUserTagCaseGroup->second;
        }
    }        
}

bool GetHardwareConfigurationDetailsForPostbootContext::isAChoiceGroup ( const UI32 &groupCode )
{
    bool found = false;
    
    map<UI32, map<UI32, vector<UI32> > >::const_iterator elementChoiceCaseGroup = m_choiceCaseGroup.find(groupCode);

    if ( elementChoiceCaseGroup != m_choiceCaseGroup.end() )
    {
        found = true;
    }

    return (found);
}

void GetHardwareConfigurationDetailsForPostbootContext::setKeyAttributeNames ( const set<string> &keyAttributeNames )
{
    m_keyAttributeNames = keyAttributeNames;
}
 
bool GetHardwareConfigurationDetailsForPostbootContext::isKeyAttribute ( const string &attributeName)
{
    bool keyAttribute = false;
    
    if ( 1 == m_keyAttributeNames.count( attributeName ) )
    {
        keyAttribute = true;
    }

    return (keyAttribute);
}

}

