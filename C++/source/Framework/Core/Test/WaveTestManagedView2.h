/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Ghosh                                                 *
 ***************************************************************************/

#ifndef WAVETESTMANAGEDVIEW2_H
#define WAVETESTMANAGEDVIEW2_H

#include "Framework/ObjectModel/WaveManagedView.h"

namespace WaveNs
{

class WaveTestManagedView2 : public WaveManagedView  
{
    private :
    protected :
        virtual void setupAttributesForPersistence  ();
        virtual void     setupAttributesForCreate   ();

    public :
                        WaveTestManagedView2       (WaveObjectManager *pWaveObjectManager);
        virtual        ~WaveTestManagedView2       ();

        static  string  getClassName                ();
        virtual void    getSetContextForCreateView  (WaveManagedObjectSynchronousQueryContextForSetOperation &viewContext);

                string  getMessage2                 ();
                UI32    getInteger2                 ();

    // Now the data members

    private :

    protected :
    public :
        UI32    m_integer1;
        string  m_message1;
};

}

#endif // WAVETESTMANAGEDVIEW2_H
