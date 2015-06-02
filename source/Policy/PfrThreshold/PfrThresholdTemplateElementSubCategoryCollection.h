/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PFRTHRESHOLDTEMPLATEELEMENTSUBCATEGORYCOLLECTION_H
#define PFRTHRESHOLDTEMPLATEELEMENTSUBCATEGORYCOLLECTION_H

#include "Policy/PfrThreshold/PfrThresholdElement.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class PfrThresholdTemplateElementSubCategoryCollection : public PfrThresholdElement
{
    private :
        virtual void loadTextAttributeFromDomElement (const string &textAttributeName, DOMElement *pDomElement);

    protected :
    public :
                                PfrThresholdTemplateElementSubCategoryCollection ();
        virtual                ~PfrThresholdTemplateElementSubCategoryCollection ();

                vector<string> &getSubCategoryNames                              ();

        // Now the data members

    private :
        vector<string> m_subCategoryNames;

    protected:
    public :
};

}

#endif // PFRTHRESHOLDTEMPLATEELEMENTSUBCATEGORYCOLLECTION_H
