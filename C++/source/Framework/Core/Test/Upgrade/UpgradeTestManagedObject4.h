/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UPGRADETESTMANAGEDOBJECT4_H
#define UPGRADETESTMANAGEDOBJECT4_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject1.h"

namespace WaveNs
{

class UpgradeTestManagedObject4 : public UpgradeTestManagedObject1
{
private :
    virtual void setupAttributesForCreate ();

protected :
    virtual void setupAttributesForPersistence ();

public :
    UpgradeTestManagedObject4  (WaveObjectManager *pWaveObjectManager);
    virtual                  ~UpgradeTestManagedObject4  ();

    static  string            getClassName             ();

    void              setInteger4              (const UI32 &integer4);
    void              setMessage4              (const string &message4);
    void              setObjectId4             (const ObjectId &objectId4);
    void              setAssociation4          (const ObjectId &association4);
    void              setObjectIdVector4       (const vector<ObjectId> &objectIdVector4);
    void              setAssociationVector4    (const vector<ObjectId> &associationVector4);

    UI32              getInteger4              () const;
    string            getMessage4              () const;
    ObjectId          getObjectId4             () const;
    ObjectId          getAssociation4          () const;
    vector<ObjectId>  getObjectIdVector4       () const;
    vector<ObjectId>  getAssociationVector4    () const;

    virtual bool              operator ==              (const UpgradeTestManagedObject4 &rhs) const;
    virtual bool              operator !=              (const UpgradeTestManagedObject4 &rhs) const;


    // Now the data members

private :
    UI32             m_integer4;
    string           m_message4;
    ObjectId         m_objectId4;
    ObjectId         m_association4;
    vector<ObjectId> m_objectIdVector4;
    vector<ObjectId> m_associationVector4;

protected :
public :
};

}

#endif // UPGRADETESTMANAGEDOBJECT4_H
