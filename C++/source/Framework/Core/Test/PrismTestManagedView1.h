/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef PRISMTESTMANAGEDVIEW1_H
#define PRISMTESTMANAGEDVIEW1_H 

#include "Framework/ObjectModel/WaveManagedView.h"

namespace WaveNs
{

class PrismTestManagedView1 : virtual public WaveManagedView
{
    private :
    protected :
        void setupAttributesForPersistence  ();
        void setupAttributesForCreate       ();

    public :
                           PrismTestManagedView1            (WaveObjectManager *pWaveObjectManager);
        virtual           ~PrismTestManagedView1            ();

        static  string      getClassName             ();
        virtual string      getSqlForCreateView      ();

                void        setInteger1              (const UI32 &integer1);
                void        setMessage1              (const string &message1);

                UI32        getInteger1              () const;
                string      getMessage1              () const;


    // Now the data members
    private :
    UI32        m_integer1;
    string      m_message1;

    protected:
    public :
};

}

#endif // PRISMTESTMANAGEDVIEW1_H 
