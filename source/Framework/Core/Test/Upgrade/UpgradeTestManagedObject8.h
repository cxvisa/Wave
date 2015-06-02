/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef UPGRADETESTMANAGEDOBJECT8_H
#define UPGRADETESTMANAGEDOBJECT8_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class UpgradeTestManagedObject8 : public WaveManagedObject
{
private :
protected :
    virtual void setupAttributesForPersistence ();

public :
    UpgradeTestManagedObject8   (WaveObjectManager *pWaveObjectManager);
    virtual                                                            ~UpgradeTestManagedObject8   ();

    static  string                                                      getClassName             ();

    virtual void                                                        setupAttributesForCreate ();

    void                                                        setInteger8              (const UI32 &integer8);
    void                                                        setMessage8              (const string &message8);

    UI32                                                        getInteger8              () const;
    string                                                      getMessage8              () const;

    // Now the data members

private :
    UI32                                                       m_integer8;
    string                                                     m_message8;


protected :
public :
};

}

#endif // UpgradeTestManagedObject8_H
