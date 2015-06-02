/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTPOINTER_H
#define WAVEMANAGEDOBJECTPOINTER_H

#include "Framework/Types/Types.h"

#include <iostream>

using namespace std;

namespace WaveNs
{

template<class T> class WaveManagedObjectPointer
{
    private :

        template<class TX> class WaveManagedObjectCountedPointer
        {
            private :
            protected :
            public :
                      WaveManagedObjectCountedPointer (TX *pTX);
                     ~WaveManagedObjectCountedPointer ();

                void  operator ++                     (int);
                void  operator --                     (int);

                UI32  getReferenceCount               () const;

                TX   *operator ->                     ();

                bool  operator ==                     (const WaveManagedObjectCountedPointer<TX> &rhs) const;

            // Now the data members

            private :
                TX   *m_pTX;
                UI32  m_referenceCount;

            protected :
            public :
        };

        void destroy ();

    protected :
    public :
                                     WaveManagedObjectPointer ();
                                     WaveManagedObjectPointer (const WaveManagedObjectPointer<T> &rhs);
                                     WaveManagedObjectPointer (T *pT);
                                    ~WaveManagedObjectPointer ();

        T                           *operator ->              ();
        WaveManagedObjectPointer<T> &operator =               (const WaveManagedObjectPointer<T> &rhs);
        bool                         operator ==              (const WaveManagedObjectPointer<T> &rhs) const;
        bool                         operator !=              (const WaveManagedObjectPointer<T> &rhs) const;

    // Now the data members

    private :
        WaveManagedObjectCountedPointer<T> *m_pWaveManagedObjectCountedPointer;

    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTPOINTER_H
