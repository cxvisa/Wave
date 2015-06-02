/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGLENGTH_H
#define YANGLENGTH_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangLength : public YangElement
{
    private :
    protected :
    public :
                            YangLength     ();
        virtual            ~YangLength     ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGLENGTH_H
