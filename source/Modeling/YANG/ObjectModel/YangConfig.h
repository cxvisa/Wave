/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGCONFIG_H
#define YANGCONFIG_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangConfig : public YangElement
{
    private :
    protected :
    public :
                            YangConfig     ();
        virtual            ~YangConfig     ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

        virtual void        updateParentAnnotations ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGCONFIG_H
