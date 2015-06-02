/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGNAMESPACE_H
#define YANGNAMESPACE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangNameSpace : public YangElement
{
    private :
    protected :
    public :
                             YangNameSpace  ();
                             YangNameSpace  (const string &uri);
        virtual             ~YangNameSpace  ();

        static  string       getYangName    ();

        static  YangElement *createInstance ();

        virtual void         processAttribute                        (const string &attributeName, const string &attributeValue);

                string  getUri              () const;
                void    setUri              (const string &uri);

    // Now the data members
    private :
        string m_uri;

    protected :
    public :
};

}

#endif // YANGNAMESPACE_H
