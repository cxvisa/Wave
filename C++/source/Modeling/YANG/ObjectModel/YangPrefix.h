/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGPREFIX_H
#define YANGPREFIX_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangPrefix : public YangElement
{
    private :
    protected :
    public :
                            YangPrefix     ();
                            YangPrefix     (const string &value);
        virtual            ~YangPrefix     ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

                string  getValue           () const;
                void    setValue           (const string &value);

    // Now the data members
    private :
        string m_value;

    protected :
    public :
};

}

#endif // YANGPREFIX_H
