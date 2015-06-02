/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UPGRADETESTMANAGEDOBJECT1_H
#define UPGRADETESTMANAGEDOBJECT1_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class UpgradeTestManagedObject1 : public WaveManagedObject
{
private :
protected :
    virtual void setupAttributesForPersistence ();

public :
    UpgradeTestManagedObject1   (WaveObjectManager *pWaveObjectManager);
    virtual        ~UpgradeTestManagedObject1   ();

    static  string   getClassName             ();

    virtual void     setupAttributesForCreate ();

    void     setInteger1              (const UI32 &integer1);
    void     setMessage1              (const string &message1);
    void     setObjectId1             (const ObjectId &objectId1);

    UI32     getInteger1              () const;
    string   getMessage1              () const;
    ObjectId getObjectId1             () const;

    virtual bool     operator ==              (const UpgradeTestManagedObject1 &rhs) const;
    virtual bool     operator !=              (const UpgradeTestManagedObject1 &rhs) const;

    // Now the data members

private :
    UI32     m_integer1;
    string   m_message1;
    ObjectId m_objectId1;

protected :
public :
};

}

#endif // UPGRADETESTMANAGEDOBJECT1_H
