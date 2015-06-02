/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGAUGMENT_H
#define YANGAUGMENT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

#include <string>

using namespace std;

namespace WaveNs
{

class YangAugment : public YangElement
{
    private :
    protected :
    public :
                             YangAugment          ();
                             YangAugment          (const string &targetNode);
        virtual             ~YangAugment          ();

        static  string       getYangName          ();

        static  YangElement *createInstance       ();

                string       getTargetNode        () const;
                void         setTargetNode        (const string &targetNode);

        virtual void         processAttribute     (const string &attributeName, const string &attributeValue);

                void         getTargetNodeDetails (string &targetNodeModuleName, string &targetNodePathInModule);

                void         transferWhenConditionsToChildren ();

    // Now the data members

    private :
        string m_targetNode;

    protected :
    public :
};

}

#endif // YANGAUGMENT_H
