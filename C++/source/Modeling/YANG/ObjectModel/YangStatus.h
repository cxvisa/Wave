/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGSTATUS_H
#define YANGSTATUS_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangStatus : public YangElement
{
    private :
    protected :
    public :
                            YangStatus     ();
        virtual            ~YangStatus     ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

        virtual void        updateParentAnnotations ();
    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGSTATUS_H
