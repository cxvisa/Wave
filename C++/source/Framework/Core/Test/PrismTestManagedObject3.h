/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMTESTMANAGEDOBJECT3_H
#define PRISMTESTMANAGEDOBJECT3_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Core/Test/PrismTestManagedObject1.h"

namespace WaveNs
{

class PrismTestManagedObject3 : public PrismTestManagedObject1
{
    private :
        virtual void setupAttributesForPersistence ();

    protected :
    public :
                        PrismTestManagedObject3  (WaveObjectManager *pWaveObjectManager);
        virtual        ~PrismTestManagedObject3  ();

        static  string  getClassName             ();

        virtual void    setupAttributesForCreate ();

                void    setInteger3              (const UI32 &integer3);
                void    setMessage3              (const string &message3);
                void    setObjectId3             (const ObjectId &objectId3);
                void    setAssociation3          (const ObjectId &association3);

                UI32      getInteger3            () const;
                string    getMessage3            () const;
                ObjectId  getObjectId3           () const;
                ObjectId  getAssociation3        () const;

        virtual bool     operator ==             (const PrismTestManagedObject3 &rhs) const;
        virtual bool     operator !=             (const PrismTestManagedObject3 &rhs) const;

    // Now the data members

    private :
        UI32     m_integer3;
        string   m_message3;
        ObjectId m_objectId3;
        ObjectId m_association3;

    protected :
    public :
};

}

#endif // PRISMTESTMANAGEDOBJECT3_H
