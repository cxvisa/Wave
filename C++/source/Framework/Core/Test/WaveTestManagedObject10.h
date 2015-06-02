/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDOBJECT10_H
#define WAVETESTMANAGEDOBJECT10_H

#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "Framework/Core/Test/WaveTestManagedObject6.h"

namespace WaveNs
{

class WaveTestManagedObject10 : public WaveManagedObject
{
    private :
    protected :
        virtual void setupAttributesForPersistence ();

    public :
                                                                   WaveTestManagedObject10   (WaveObjectManager *pWaveObjectManager);
        virtual                                                   ~WaveTestManagedObject10   ();

        static  string                                             getClassName             ();

        virtual void                                               setupAttributesForCreate ();

                void                                               setInteger10              (const UI32 &integer10);
                void                                               setMessage10              (const string &message10);
                void                                               setComposition10          (const WaveManagedObjectPointer<WaveTestManagedObject6> &composition10);

                UI32                                               getInteger10              () const;
                string                                             getMessage10              () const;
                WaveManagedObjectPointer<WaveTestManagedObject6>   getComposition10          () const;

        virtual bool                                               operator ==              (const WaveTestManagedObject10 &rhs) const;
        virtual bool                                               operator !=              (const WaveTestManagedObject10 &rhs) const;

    // Now the data members

    private :
        UI32                                                       m_integer10;
        string                                                     m_message10;

        WaveManagedObjectPointer<WaveTestManagedObject6>           m_composition10;

    protected :
    public :
};

}

#endif // WAVETESTMANAGEDOBJECT10_H
