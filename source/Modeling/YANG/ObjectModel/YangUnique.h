/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kundan sinha                                                 *
 ***************************************************************************/

#ifndef YANGUNIQUE_H
#define YANGUNIQUE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangUnique : public YangElement
{
    private :
    protected :
    public :
                             YangUnique        ();
        virtual             ~YangUnique        ();

        static  string       getYangName       ();

        static YangElement  *createInstance    ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGUNIQUE_H
