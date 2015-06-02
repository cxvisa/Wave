/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/PrismTestManagedObject5.h"

namespace WaveNs
{

PrismTestManagedObject5::PrismTestManagedObject5 (WaveObjectManager *pWaveObjectManager)
    : PrismElement               (pWaveObjectManager),
      PrismPersistableObject     (PrismTestManagedObject5::getClassName (), PrismTestManagedObject4::getClassName ()),
      PrismTestManagedObject4    (pWaveObjectManager),
      WaveLocalManagedObjectBase (this)
{
}

PrismTestManagedObject5::~PrismTestManagedObject5 ()
{
}

string PrismTestManagedObject5::getClassName ()
{
    return ("PrismTestManagedObject5");
}

void PrismTestManagedObject5::setupAttributesForPersistence ()
{
    PrismTestManagedObject4::setupAttributesForPersistence ();
    WaveLocalManagedObjectBase::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_associationVector5, "associationVector5", getClassName (), getObjectId (), PrismTestManagedObject1::getClassName ()));
}

void PrismTestManagedObject5::setupAttributesForCreate ()
{
    WaveLocalManagedObjectBase::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_associationVector5, "associationVector5", getClassName (), getObjectId (), PrismTestManagedObject1::getClassName ()));
}

void PrismTestManagedObject5::setAssociationVector5 (const vector<ObjectId> &objectVector5)
{
    m_associationVector5 = objectVector5;
}
vector<ObjectId> PrismTestManagedObject5::getAssociationVector5 () const
{
    return (m_associationVector5);
}

bool PrismTestManagedObject5::operator == (const PrismTestManagedObject5 &rhs) const
{
    bool isEqual = PrismTestManagedObject4::operator == (rhs);

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

bool PrismTestManagedObject5::operator != (const PrismTestManagedObject5 &rhs) const
{
    return (!(operator == (rhs)));
}

}
