/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGCASE_H
#define YANGCASE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangCase : public YangElement
{
    private :
    protected :
    public :
                            YangCase                        ();
        virtual            ~YangCase                        ();

        static  string      getYangName                     ();

        static YangElement *createInstance                  ();

        virtual void        computeCliTargetNodeNameForSelf ();

        virtual void        computeIsConfigurationForSelf   ();

        virtual bool        isYangElementForData            () const;

        virtual void        displayConfiguration2           (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData);
        virtual void        displayConfiguration3           (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData);

        virtual bool        considerForHFileForCLanguage    () const;

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGCASE_H
