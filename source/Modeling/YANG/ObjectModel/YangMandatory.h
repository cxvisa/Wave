/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGMANDATORY_H
#define YANGMANDATORY_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangMandatory : public YangElement
{
    private :
    protected :
    public :
                            YangMandatory    ();
        virtual            ~YangMandatory    ();

        static  string      getYangName      ();

        static YangElement *createInstance   ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGMANDATORY_H
