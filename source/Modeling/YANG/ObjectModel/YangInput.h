/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGINPUT_H
#define YANGINPUT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangInput : public YangElement
{
    private :
    protected :
    public :
                            YangInput      ();
        virtual            ~YangInput      ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGINPUT_H
