/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDOBJECT6_H
#define WAVETESTMANAGEDOBJECT6_H

#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "Framework/Core/Test/WaveTestManagedObject1.h"

namespace WaveNs
{

class WaveTestManagedObject6 : public WaveManagedObject
{
    private :
    protected :
        virtual void setupAttributesForPersistence ();

    public :
                                                                   WaveTestManagedObject6   (WaveObjectManager *pWaveObjectManager);
        virtual                                                   ~WaveTestManagedObject6   ();

        static  string                                             getClassName             ();

        virtual void                                               setupAttributesForCreate ();

                void                                               setInteger6              (const UI32 &integer6);
                void                                               setMessage6              (const string &message6);
                void                                               setObjectId6             (const ObjectId &objectId6);
                void                                               setComposition6          (const WaveManagedObjectPointer<WaveTestManagedObject1> &composition6);

                UI32                                               getInteger6              () const;
                string                                             getMessage6              () const;
                ObjectId                                           getObjectId6             () const;
                WaveManagedObjectPointer<WaveTestManagedObject1>  getComposition6          () const;

        virtual bool                                               operator ==              (const WaveTestManagedObject6 &rhs) const;
        virtual bool                                               operator !=              (const WaveTestManagedObject6 &rhs) const;

    // Now the data members

    private :
        UI32                                                       m_integer6;
        string                                                     m_message6;
        ObjectId                                                   m_objectId6;

        WaveManagedObjectPointer<WaveTestManagedObject1>          m_composition6;

    protected :
    public :
};

}

#endif // WAVETESTMANAGEDOBJECT6_H
