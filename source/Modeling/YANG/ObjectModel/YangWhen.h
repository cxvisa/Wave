/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGWHEN_H
#define YANGWHEN_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class WaveXPathExpressionElement;

class YangWhen : public YangElement
{
    private :
    protected :
    public :
                            YangWhen       ();
        virtual            ~YangWhen       ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

                void        setConditionString                      (const string &conditionString);
                string      getConditionString                      () const;

        virtual void        processAttribute                        (const string &attributeName, const string &attributeValue);

                bool        evaluateCondition                       (YangDisplayConfigurationContext *pYangDisplayConfigurationContext);

    // Now the data members

    private :
        string                      m_conditionString;
        WaveXPathExpressionElement *m_pWaveXPathExpressionElement;

    protected :
    public :
};

}

#endif // YANGWHEN_H
