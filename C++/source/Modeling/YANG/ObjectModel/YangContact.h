/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGCONTACT_H
#define YANGCONTACT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangContact : public YangElement
{
    private :
    protected :
    public :
                            YangContact    ();
        virtual            ~YangContact    ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGCONTACT_H
