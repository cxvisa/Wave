/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGPOSITION_H
#define YANGPOSITION_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangPosition : public YangElement
{
    private :
    protected :
    public :
                                 YangPosition               ();
        virtual                 ~YangPosition               ();

        static   string          getYangName                ();

        static   YangElement    *createInstance             ();
                 void            processAttribute           (const string &attributeName, const string &attributeValue);

                 UI32            getValue                   () const;
                 void            setValue                   (const UI32 &value);

    // Now the data members

    private :
        UI32 m_value;

    protected :
    public :
};

}

#endif // YANGPOSITION_H
