/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGOUTPUT_H
#define YANGOUTPUT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangOutput : public YangElement
{
    private :
    protected :
    public :
                            YangOutput     ();
        virtual            ~YangOutput     ();

        static  string      getYangName    ();

        static  YangElement *createInstance ();

        virtual bool         considerForComputingUsageCountForGroupingsForProgrammingLanguages () const;

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGOUTPUT_H
