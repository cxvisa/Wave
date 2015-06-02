/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMTESTMANAGEDOBJECT5_H
#define PRISMTESTMANAGEDOBJECT5_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObjectBase.h"
#include "Framework/Core/Test/PrismTestManagedObject4.h"

namespace WaveNs
{

class PrismTestManagedObject5 : public virtual PrismTestManagedObject4, public virtual WaveLocalManagedObjectBase
{
    private :
        virtual void setupAttributesForPersistence ();

    protected :
    public :
                                  PrismTestManagedObject5  (WaveObjectManager *pWaveObjectManager);
        virtual                  ~PrismTestManagedObject5  ();

        static  string            getClassName             ();

        virtual void              setupAttributesForCreate ();

                void              setAssociationVector5    (const vector<ObjectId> &associationVector5);

                vector<ObjectId>  getAssociationVector5    () const;

        virtual bool              operator ==              (const PrismTestManagedObject5 &rhs) const;
        virtual bool              operator !=              (const PrismTestManagedObject5 &rhs) const;


    // Now the data members

    private :
        vector<ObjectId> m_associationVector5;

    protected :
    public :
};

}

#endif // PRISMTESTMANAGEDOBJECT5_H
