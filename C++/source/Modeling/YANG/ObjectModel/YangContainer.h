/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGCONTAINER_H
#define YANGCONTAINER_H

#include "Modeling/YANG/ObjectModel/YangDataElement.h"
#include "Modeling/YANG/ObjectModel/YangLeaf.h"

namespace WaveNs
{

class YangContainer : public YangDataElement
{
    private :
                bool         getConfigurationStringForLeafWithHideInSubMode (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, string &configurationString);

    protected :
    public :
                             YangContainer                         ();
                             YangContainer                         (const string &name);
        virtual             ~YangContainer                         ();

        static  string       getYangName                           ();

        static  YangElement *createInstance                        ();

        virtual void         processChildElement                   (YangElement *pYangElement);

        virtual bool         meetsCriteriaToBeShownInConfiguration () const;

        virtual void         displayConfiguration2                 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData);
        virtual void         displayConfiguration3                 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData);

        virtual void         collectHideInSubModeLeafForSelf       ();
        virtual void         propagateCompactSyntaxOneLevelForSelf ();

    // Now the data members

    private :
        bool                m_isPresenceContainer;
        YangLeaf           *m_pYangLeafWithHideInSubMode;

    protected :
    public :
};

}

#endif // YANGCONTAINER_H
