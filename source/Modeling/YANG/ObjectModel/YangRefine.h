/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGREFINE_H
#define YANGREFINE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangRefine : public YangElement
{
    private :
    protected :
    public :
                            YangRefine     ();
        virtual            ~YangRefine     ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

        virtual void        processAttribute        (const string &attributeName, const string &attributeValue);

                string      getTargetExpression     () const;
                void        setTargetExpression     (const string &targetExpression);

                void        refineYangElements      (vector<YangElement *> &childElementsInGrouping);

    // Now the data members

    private :
        string              m_targetExpression;
    protected :
    public :
};

}

#endif // YANGREFINE_H
