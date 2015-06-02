/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGPATTERN_H
#define YANGPATTERN_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangPattern : public YangElement
{
    private :
    protected :
    public :
                            YangPattern    ();
        virtual            ~YangPattern    ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGPATTERN_H
