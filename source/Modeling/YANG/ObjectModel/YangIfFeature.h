/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGIFFEATURE_H
#define YANGIFFEATURE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangIfFeature : public YangElement
{
    private :
    protected :
    public :
                            YangIfFeature    ();
        virtual            ~YangIfFeature    ();

        static  string      getYangName      ();

        static YangElement *createInstance   ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGIFFEATURE_H
