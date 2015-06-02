/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGVALUE_H
#define YANGVALUE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangValue : public YangElement
{
    private :
    protected :
    public :
                            YangValue        ();
        virtual            ~YangValue        ();

        static  string      getYangName      ();

        static YangElement *createInstance   ();

        virtual void        loadValue        (const string &value);
                void        processAttribute (const string &attributeName, const string &attributeValue);

                UI32        getValue         () const;
                void        setValue         (const UI32 &value);


    // Now the data members

    private :
        UI32 m_value;

    protected :
    public :
};

}

#endif // YANGVALUE_H
