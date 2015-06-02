/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGTEXT_H
#define YANGTEXT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangText : public YangElement
{
    private :
    protected :
    public :
                            YangText                  ();
        virtual            ~YangText                  ();

        static  string      getYangName               ();

        static YangElement *createInstance            ();

        virtual void        loadValue                 (const string &value);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGTEXT_H
