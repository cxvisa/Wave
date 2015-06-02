/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGENUM_H
#define YANGENUM_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangEnum : public YangElement
{
    private :
    protected :
    public :
                             YangEnum                             ();
        virtual             ~YangEnum                             ();

        static  string       getYangName                          ();

        static  YangElement *createInstance                       ();

                UI32         getValue                             () const;
                void         setValue                             (const UI32 &value);

                bool         getValueIsExplicitlySet              () const;

        virtual void         processChildElement                  (YangElement *pYangElement);

        virtual bool         considerForHFileForCLanguage         () const;
        virtual void         getNameForHFileForCLanguage          (string &actualName, string &processedNameForCLanguage, string &cLanguageValue) const;

    // Now the data members

    private :
        UI32   m_value;
        bool   m_valueIsExplicitlySet;

    protected :
    public :
};

}

#endif // YANGENUM_H
