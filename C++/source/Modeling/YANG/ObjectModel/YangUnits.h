/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGUNITS_H
#define YANGUNITS_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangUnits : public YangElement
{
    private :
    protected :
    public :
                            YangUnits      ();
        virtual            ~YangUnits      ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGUNITS_H
