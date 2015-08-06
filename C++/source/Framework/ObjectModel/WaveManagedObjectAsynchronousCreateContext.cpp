/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu VArshney                                            *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectAsynchronousCreateContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveManagedObjectAsynchronousCreateContext::WaveManagedObjectAsynchronousCreateContext (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext)
{
}

WaveManagedObjectAsynchronousCreateContext::~WaveManagedObjectAsynchronousCreateContext ()
{

}

vector<string> WaveManagedObjectAsynchronousCreateContext::getAttributeNames () const
{
    return (m_attributeNames);
}

void WaveManagedObjectAsynchronousCreateContext::setAttributeNames (const vector<string> &attributeNames)
{

    m_attributeNames = attributeNames;
}

vector<string> WaveManagedObjectAsynchronousCreateContext::getAttributeValues () const
{
    return (m_attributeValues);
}

void WaveManagedObjectAsynchronousCreateContext::setAttributeValues(const vector< string >& attributeValues)
{
    m_attributeValues = attributeValues;
}

string WaveManagedObjectAsynchronousCreateContext::getManagedObjectClassNameNeedToBeCreated () const
{
    return (m_managedObjectClassName);
}

void WaveManagedObjectAsynchronousCreateContext::setManagedObjectClassNameNeedToBeCreated (const string &managedObjectClassName)
{
    m_managedObjectClassName = managedObjectClassName;
}

ObjectId WaveManagedObjectAsynchronousCreateContext::getObjectId () const
{
    return (m_objectId);
}

void WaveManagedObjectAsynchronousCreateContext::setObjectId (const WaveNs::ObjectId& objectId)
{
    m_objectId = objectId;
}

string WaveManagedObjectAsynchronousCreateContext::getParentAttributeName () const
{
    return (m_parentAttributeName);
}

void WaveManagedObjectAsynchronousCreateContext::setParentAttributeName (const string &attributeName)
{
    m_parentAttributeName = attributeName;
}

}
