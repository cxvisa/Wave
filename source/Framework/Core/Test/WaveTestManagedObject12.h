/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDOBJECT12_H
#define WAVETESTMANAGEDOBJECT12_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class WaveTestManagedObject12 : public WaveManagedObject
{
private :
protected :
    virtual void setupAttributesForPersistence ();

public :
                                                                WaveTestManagedObject12   (WaveObjectManager *pWaveObjectManager);
    virtual                                                     ~WaveTestManagedObject12   ();

    static  string                                              getClassName             ();

    virtual void                                                setupAttributesForCreate ();

    void                                                        setInteger12              (const UI32 &integer12);
    void                                                        setMessage12              (const string &message12);

    UI32                                                        getInteger12              () const;
    string                                                      getMessage12              () const;

    // Now the data members

private :
    UI32                                                       m_integer12;
    string                                                     m_message12;


protected :
public :
};

}

#endif // WaveTestManagedObject12_H
