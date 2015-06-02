/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGMAXELEMENTS_H
#define YANGMAXELEMENTS_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangMaxElements : public YangElement
{
    private :
    protected :
    public :
                            YangMaxElements    ();
        virtual            ~YangMaxElements    ();

        static  string      getYangName       ();

        static YangElement *createInstance    ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGMAXELEMENTS_H
