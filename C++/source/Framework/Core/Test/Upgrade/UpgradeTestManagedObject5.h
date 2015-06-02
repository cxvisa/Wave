/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UPGRADETESTMANAGEDOBJECT5_H
#define UPGRADETESTMANAGEDOBJECT5_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObjectBase.h"
#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject4.h"

namespace WaveNs
{

class UpgradeTestManagedObject5 : public virtual UpgradeTestManagedObject4, public virtual WaveLocalManagedObjectBase
{
private :
    virtual void setupAttributesForPersistence ();

protected :
public :
    UpgradeTestManagedObject5  (WaveObjectManager *pWaveObjectManager);
    virtual                  ~UpgradeTestManagedObject5  ();

    static  string            getClassName             ();

    virtual void              setupAttributesForCreate ();

    void              setAssociationVector5    (const vector<ObjectId> &associationVector5);

    vector<ObjectId>  getAssociationVector5    () const;

    virtual bool              operator ==              (const UpgradeTestManagedObject5 &rhs) const;
    virtual bool              operator !=              (const UpgradeTestManagedObject5 &rhs) const;


    // Now the data members

private :
    vector<ObjectId> m_associationVector5;

protected :
public :
};

}

#endif // UPGRADETESTMANAGEDOBJECT5_H
