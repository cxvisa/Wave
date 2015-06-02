/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGDESCRIPTION_H
#define YANGDESCRIPTION_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangDescription : public YangElement
{
    private :
    protected :
    public :
                             YangDescription ();
        virtual             ~YangDescription ();

        static  string       getYangName     ();

        static  YangElement *createInstance  ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGDESCRIPTION_H
