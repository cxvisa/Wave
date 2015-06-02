/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGORGANIZATION_H
#define YANGORGANIZATION_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangOrganization : public YangElement
{
    private :
    protected :
    public :
                            YangOrganization ();
        virtual            ~YangOrganization ();

        static  string      getYangName      ();

        static YangElement *createInstance   ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGORGANIZATION_H
