/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/Test/WaveTestManagedObject5.h"

namespace WaveNs
{

WaveTestManagedObject5::WaveTestManagedObject5 (WaveObjectManager *pWaveObjectManager)
    : WaveElement               (pWaveObjectManager),
      WavePersistableObject     (WaveTestManagedObject5::getClassName (), WaveTestManagedObject4::getClassName ()),
      WaveTestManagedObject4    (pWaveObjectManager),
      WaveLocalManagedObjectBase (this)
{
}

WaveTestManagedObject5::~WaveTestManagedObject5 ()
{
}

string WaveTestManagedObject5::getClassName ()
{
    return ("WaveTestManagedObject5");
}

void WaveTestManagedObject5::setupAttributesForPersistence ()
{
    WaveTestManagedObject4::setupAttributesForPersistence ();
    WaveLocalManagedObjectBase::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeObjectIdVectorAssociation (&m_associationVector5, "associationVector5", getClassName (), getObjectId (), WaveTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject5::setupAttributesForCreate ()
{
    WaveLocalManagedObjectBase::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeObjectIdVectorAssociation (&m_associationVector5, "associationVector5", getClassName (), getObjectId (), WaveTestManagedObject1::getClassName ()));
}

void WaveTestManagedObject5::setAssociationVector5 (const vector<ObjectId> &objectVector5)
{
    m_associationVector5 = objectVector5;
}
vector<ObjectId> WaveTestManagedObject5::getAssociationVector5 () const
{
    return (m_associationVector5);
}

bool WaveTestManagedObject5::operator == (const WaveTestManagedObject5 &rhs) const
{
    bool isEqual = WaveTestManagedObject4::operator == (rhs);

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

bool WaveTestManagedObject5::operator != (const WaveTestManagedObject5 &rhs) const
{
    return (!(operator == (rhs)));
}

}
