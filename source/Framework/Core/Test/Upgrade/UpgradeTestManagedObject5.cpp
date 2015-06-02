/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject5.h"

namespace WaveNs
{

UpgradeTestManagedObject5::UpgradeTestManagedObject5 (WaveObjectManager *pWaveObjectManager)
        : PrismElement               (pWaveObjectManager),
        PrismPersistableObject     (UpgradeTestManagedObject5::getClassName (), UpgradeTestManagedObject4::getClassName ()),
        UpgradeTestManagedObject4    (pWaveObjectManager),
        WaveLocalManagedObjectBase (this)
{
}

UpgradeTestManagedObject5::~UpgradeTestManagedObject5 ()
{
}

string UpgradeTestManagedObject5::getClassName ()
{
    return ("UpgradeTestManagedObject5");
}

void UpgradeTestManagedObject5::setupAttributesForPersistence ()
{
    UpgradeTestManagedObject4::setupAttributesForPersistence ();
    WaveLocalManagedObjectBase::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_associationVector5, "associationVector5", getClassName (), getObjectId (), UpgradeTestManagedObject1::getClassName ()));
}

void UpgradeTestManagedObject5::setupAttributesForCreate ()
{
    WaveLocalManagedObjectBase::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_associationVector5, "associationVector5", getClassName (), getObjectId (), UpgradeTestManagedObject1::getClassName ()));
}

void UpgradeTestManagedObject5::setAssociationVector5 (const vector<ObjectId> &objectVector5)
{
    m_associationVector5 = objectVector5;
}
vector<ObjectId> UpgradeTestManagedObject5::getAssociationVector5 () const
{
    return (m_associationVector5);
}

bool UpgradeTestManagedObject5::operator == (const UpgradeTestManagedObject5 &rhs) const
{
    bool isEqual = UpgradeTestManagedObject4::operator == (rhs);

    if (false == isEqual)
    {
        return (false);
    }

    if (rhs.m_associationVector5 != m_associationVector5)
    {
        return (false);
    }

    return (true);
}

bool UpgradeTestManagedObject5::operator != (const UpgradeTestManagedObject5 &rhs) const
{
    return (!(operator == (rhs)));
}

}
