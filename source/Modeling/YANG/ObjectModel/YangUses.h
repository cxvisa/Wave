/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGUSES_H
#define YANGUSES_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangUses : public YangElement
{
    private :
    protected :
    public :
                            YangUses       ();
        virtual            ~YangUses       ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGUSES_H
