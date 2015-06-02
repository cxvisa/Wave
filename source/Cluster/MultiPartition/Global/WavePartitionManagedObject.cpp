/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/Local/WaveNode.h"
#include "Cluster/MultiPartition/Global/WavePartitionManagedObject.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"

namespace WaveNs
{

WavePartitionManagedObject::WavePartitionManagedObject (WaveObjectManager *pWaveObjectManager)
    : PrismElement                     (pWaveObjectManager),
      PrismPersistableObject           (WavePartitionManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pWaveObjectManager)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (true);
}

WavePartitionManagedObject::~WavePartitionManagedObject ()
{
}

string WavePartitionManagedObject::getClassName ()
{
    return ("WavePartitionManagedObject");
}

void WavePartitionManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();
    addPersistableAttribute (new AttributeString(&m_partitionName, "PartitionName"));
    addPersistableAttribute (new AttributeObjectIdVectorAssociation(&m_waveNodeObjectIdList, "WaveNodeObjectIdList", getClassName (), getObjectId (), WaveNode::getClassName ()));
}

void WavePartitionManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeString(&m_partitionName, "PartitionName"));
    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation(&m_waveNodeObjectIdList, "WaveNodeObjectIdList", getClassName (), getObjectId (), WaveNode::getClassName ()));
}

bool   WavePartitionManagedObject::isWaveNodeMappedToPartition(ObjectId &objId)
{
    bool status = false;
    vector<ObjectId>::iterator itr = m_waveNodeObjectIdList.begin(); 
    for (; itr!= m_waveNodeObjectIdList.end() ; itr++)
    {
        if (*itr == objId)
        {
            status = true; 
            break;
        }
    }
    return status;
}

void   WavePartitionManagedObject::addWaveNodeToPartition(ObjectId &objId)
{
        prismAssert(ObjectId::NullObjectId != objId , __FILE__, __LINE__);
        prismAssert(false == isWaveNodeMappedToPartition(objId), __FILE__, __LINE__); 
        m_waveNodeObjectIdList.push_back(objId);
}

UI32   WavePartitionManagedObject::removeWaveNodeFromPartition(ObjectId &objId)
{
    prismAssert(ObjectId::NullObjectId != objId , __FILE__, __LINE__);
    prismAssert(true == isWaveNodeMappedToPartition(objId), __FILE__, __LINE__); 
    vector<ObjectId>::iterator itr = m_waveNodeObjectIdList.begin(); 
    for (; itr!= m_waveNodeObjectIdList.end() ; itr++)
    {
        if (*itr == objId)
        {
            m_waveNodeObjectIdList.erase(itr);
            break;
        }
    }
    return (m_waveNodeObjectIdList.size());
}


void   WavePartitionManagedObject::setPartitionName(const string &name)
{
        m_partitionName = name;
}

string WavePartitionManagedObject::getPartitionName(void)
{
        return m_partitionName;
}


}
