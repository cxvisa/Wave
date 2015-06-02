/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGFRACTIONDIGITS_H
#define YANGFRACTIONDIGITS_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangFractionDigits : public YangElement
{
    private :
    protected :
    public :
                            YangFractionDigits    ();
        virtual            ~YangFractionDigits    ();

        static  string      getYangName           ();

        static YangElement *createInstance        ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGFRACTIONDIGITS_H
