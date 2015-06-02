/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGTYPEDEF_H
#define YANGTYPEDEF_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangTypedef : public YangElement
{
    private :
    protected :
    public :
                            YangTypedef    ();
                            YangTypedef    (const string &name);
        virtual            ~YangTypedef    ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGTYPEDEF_H
