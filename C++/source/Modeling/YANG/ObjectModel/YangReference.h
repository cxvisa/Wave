/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGREFERENCE_H
#define YANGREFERENCE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangReference : public YangElement
{
    private :
    protected :
    public :
                            YangReference  ();
        virtual            ~YangReference  ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGREFERENCE_H
