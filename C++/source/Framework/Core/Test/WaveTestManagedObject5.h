/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDOBJECT5_H
#define WAVETESTMANAGEDOBJECT5_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObjectBase.h"
#include "Framework/Core/Test/WaveTestManagedObject4.h"

namespace WaveNs
{

class WaveTestManagedObject5 : public virtual WaveTestManagedObject4, public virtual WaveLocalManagedObjectBase
{
    private :
        virtual void setupAttributesForPersistence ();

    protected :
    public :
                                  WaveTestManagedObject5  (WaveObjectManager *pWaveObjectManager);
        virtual                  ~WaveTestManagedObject5  ();

        static  string            getClassName             ();

        virtual void              setupAttributesForCreate ();

                void              setAssociationVector5    (const vector<ObjectId> &associationVector5);

                vector<ObjectId>  getAssociationVector5    () const;

        virtual bool              operator ==              (const WaveTestManagedObject5 &rhs) const;
        virtual bool              operator !=              (const WaveTestManagedObject5 &rhs) const;


    // Now the data members

    private :
        vector<ObjectId> m_associationVector5;

    protected :
    public :
};

}

#endif // WAVETESTMANAGEDOBJECT5_H
