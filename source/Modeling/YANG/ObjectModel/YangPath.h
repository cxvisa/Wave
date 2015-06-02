/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGPATH_H
#define YANGPATH_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangPath : public YangElement
{
    private :
    protected :
    public :
                            YangPath       ();
        virtual            ~YangPath       ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGPATH_H
