/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDVIEW_H
#define WAVEMANAGEDVIEW_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class WaveManagedView : virtual public WaveManagedObject
{
    private :
    protected :
        void setupAttributesForPersistence  ();
        void setupAttributesForCreate       ();

    public :
                           WaveManagedView            (WaveObjectManager *pWaveObjectManager);
        virtual           ~WaveManagedView            ();

        static  string      getClassName                ();
        virtual string      getSqlForCreateView         ();
        //virtual void        getSetContextForCreateView  (WaveManagedObjectSynchronousQueryContextForSetOperation* &pViewContext);
        //virtual void        getSetContextForCreateView  (WaveManagedObjectSynchronousQueryContextForSetOperation *pViewContext);
        virtual void        getSetContextForCreateView  (WaveManagedObjectSynchronousQueryContextForSetOperation &viewContext);


    // Now the data members
    private :

    protected:
    public :
};

}

#endif // WAVEMANAGEDVIEW_H
