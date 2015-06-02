/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMTESTMANAGEDOBJECT1_H
#define PRISMTESTMANAGEDOBJECT1_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class PrismTestManagedObject1 : public WaveManagedObject
{
    private :
    protected :
        virtual void setupAttributesForPersistence ();

    public :
                        PrismTestManagedObject1   (WaveObjectManager *pWaveObjectManager);
        virtual        ~PrismTestManagedObject1   ();

        static  string   getClassName             ();

        virtual void     setupAttributesForCreate ();

                void     setInteger1              (const UI32 &integer1);
                void     setMessage1              (const string &message1);
                void     setObjectId1             (const ObjectId &objectId1);

                UI32     getInteger1              () const;
                string   getMessage1              () const;
                ObjectId getObjectId1             () const;

        virtual bool     operator ==              (const PrismTestManagedObject1 &rhs) const;
        virtual bool     operator !=              (const PrismTestManagedObject1 &rhs) const;

    // Now the data members

    private :
        UI32     m_integer1;
        string   m_message1;
        ObjectId m_objectId1;

    protected :
    public :
};

}

#endif // PRISMTESTMANAGEDOBJECT1_H
