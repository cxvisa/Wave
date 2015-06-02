/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef UPGRADETESTMANAGEDOBJECT9_H
#define UPGRADETESTMANAGEDOBJECT9_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class UpgradeTestManagedObject9 : public WaveManagedObject
{
private :
protected :
    virtual void setupAttributesForPersistence ();

public :
    UpgradeTestManagedObject9   (WaveObjectManager *pWaveObjectManager);
    virtual                                                            ~UpgradeTestManagedObject9   ();

    static  string                                                      getClassName             ();

    virtual void                                                        setupAttributesForCreate ();

    void                                                        setInteger9              (const UI32 &integer9);
    void                                                        setMessage9              (const string &message9);

    UI32                                                        getInteger9              () const;
    string                                                      getMessage9              () const;

    // Now the data members

private :
    UI32                                                       m_integer9;
    UI32                                                       m_integer9_1;  // This is a dummy data member and not used in BIST, this is just used to create a schema change
    string                                                     m_message9;


protected :
public :
};

}

#endif // UpgradeTestManagedObject9_H
