/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGFEATURE_H
#define YANGFEATURE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangFeature : public YangElement
{
    private :
    protected :
    public :
                            YangFeature    ();
        virtual            ~YangFeature    ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGFEATURE_H
