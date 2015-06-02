/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YNAGIMPORT_H
#define YNAGIMPORT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangImport : public YangElement
{
    private :
    protected :
    public :
                             YangImport          ();
        virtual             ~YangImport          ();

        static  string       getYangName         ();

        static  YangElement *createInstance      ();

                string       getModule           () const;
                void         setModule           (const string &module);

                string       getPrefix           () const;
                void         setPrefix           (const string &prefix);

        virtual void         processChildElement (YangElement *pYangElement);
        virtual void         processAttribute    (const string &attributeName, const string &attributeValue);

    // Now the data members
    private :
        string m_module;
        string m_prefix;

    protected :
    public :
};

}

#endif // YNAGIMPORT_H
