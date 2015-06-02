/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGORDEREDBY_H
#define YANGORDEREDBY_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangOrderedBy : public YangElement
{
    private :
    protected :
    public :
                            YangOrderedBy    ();
        virtual            ~YangOrderedBy    ();

        static  string      getYangName      ();

        static YangElement *createInstance   ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGORDEREDBY_H
