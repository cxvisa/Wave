/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGDEFAULT_H
#define YANGDEFAULT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangDefault : public YangElement
{
    private :
    protected :
    public :
                            YangDefault    ();
        virtual            ~YangDefault    ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGDEFAULT_H
