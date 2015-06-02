/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGKEY_H
#define YANGKEY_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangKey : public YangElement
{
    private :
    protected :
    public :
                            YangKey        ();
        virtual            ~YangKey        ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGKEY_H
