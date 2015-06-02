/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGERRORMESSAGE_H
#define YANGERRORMESSAGE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangErrorMessage : public YangElement
{
    private :
    protected :
    public :
                            YangErrorMessage    ();
        virtual            ~YangErrorMessage    ();

        static  string      getYangName         ();

        static YangElement *createInstance      ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGERRORMESSAGE_H
