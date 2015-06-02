/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGBIT_H
#define YANGBIT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangBit : public YangElement
{
    private :
    protected :
    public :
                             YangBit                      ();
        virtual             ~YangBit                      ();

        static  string       getYangName                  ();

        static  YangElement *createInstance               ();

        virtual void         processChildElement          (YangElement *pYangElement);

        virtual void         getNameForHFileForCLanguage  (string &actualName, string &processedNameForCLanguage, string &cLanguageValue) const;

        virtual bool         considerForHFileForCLanguage () const;

    // Now the data members

    private :
        UI32 m_position;

    protected :
    public :
};

}

#endif // YANGBIT_H
