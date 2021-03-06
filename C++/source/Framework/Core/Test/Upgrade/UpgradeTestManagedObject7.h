/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UPGRADETESTMANAGEDOBJECT7_H
#define UPGRADETESTMANAGEDOBJECT7_H

#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "Framework/Core/Test/Upgrade/UpgradeTestManagedObject1.h"

namespace WaveNs
{

class UpgradeTestManagedObject7 : public WaveManagedObject
{
private :
protected :
    virtual void setupAttributesForPersistence ();

public :
    UpgradeTestManagedObject7   (WaveObjectManager *pWaveObjectManager);
    virtual                                                            ~UpgradeTestManagedObject7   ();

    static  string                                                      getClassName             ();

    virtual void                                                        setupAttributesForCreate ();

    void                                                        setInteger7              (const UI32 &integer7);
    void                                                        setMessage7              (const string &message7);
    void                                                        setObjectId7             (const ObjectId &objectId7);
    void                                                        setComposition7          (const vector<WaveManagedObjectPointer<UpgradeTestManagedObject1> > &composition7);

    UI32                                                        getInteger7              () const;
    string                                                      getMessage7              () const;
    ObjectId                                                    getObjectId7             () const;
    vector<WaveManagedObjectPointer<UpgradeTestManagedObject1> >  getComposition7          () const;

    virtual bool                                                        operator ==              (const UpgradeTestManagedObject7 &rhs) const;
    virtual bool                                                        operator !=              (const UpgradeTestManagedObject7 &rhs) const;

    // Now the data members

private :
    UI32                                                       m_integer7;
    string                                                     m_message7;
    ObjectId                                                   m_objectId7;

    vector<WaveManagedObjectPointer<UpgradeTestManagedObject1> > m_composition7;

protected :
public :
};

}

#endif // UPGRADETESTMANAGEDOBJECT7_H
