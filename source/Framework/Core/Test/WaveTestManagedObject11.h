/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDOBJECT11_H
#define WAVETESTMANAGEDOBJECT11_H

#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "Framework/Core/Test/WaveTestManagedObject7.h"

namespace WaveNs
{

class WaveTestManagedObject11 : public WaveManagedObject
{
    private :
    protected :
        virtual void setupAttributesForPersistence ();

    public :
                                                                            WaveTestManagedObject11   (WaveObjectManager *pWaveObjectManager);
        virtual                                                            ~WaveTestManagedObject11   ();

        static  string                                                      getClassName              ();

        virtual void                                                        setupAttributesForCreate  ();

                void                                                        setInteger11              (const UI32 &integer11);
                void                                                        setMessage11              (const string &message11);
                void                                                        setComposition11          (const vector<WaveManagedObjectPointer<WaveTestManagedObject7> > &composition11);

                UI32                                                        getInteger11              () const;
                string                                                      getMessage11              () const;
                vector<WaveManagedObjectPointer<WaveTestManagedObject7> >   getComposition11          () const;

        virtual bool                                                        operator ==               (const WaveTestManagedObject11 &rhs) const;
        virtual bool                                                        operator !=               (const WaveTestManagedObject11 &rhs) const;

    // Now the data members

    private :
        UI32                                                       m_integer11;
        string                                                     m_message11;

        vector<WaveManagedObjectPointer<WaveTestManagedObject7> >  m_composition11;

    protected :
    public :
};

}

#endif // WAVETESTMANAGEDOBJECT7_H
