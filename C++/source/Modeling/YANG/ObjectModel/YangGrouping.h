/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGGROUPING_H
#define YANGGROUPING_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangGrouping : public YangElement
{
    private :
    protected :
    public :
                             YangGrouping                               ();
                             YangGrouping                               (const string &name);
        virtual             ~YangGrouping                               ();

        static  string       getYangName                                ();

        static  YangElement *createInstance                             ();

                void         incrementUsageCount                        (const UI32 &count = 1);
                UI32         getUsageCount                              () const;
                void         setUsageCount                              (const UI32 &usageCount);

                void         incrementUsageCountForProgrammingLanguages (const UI32 &countForProgrammingLanguages = 1);
                UI32         getUsageCountForProgrammingLanguages       () const;
                void         setUsageCountForProgrammingLanguages       (const UI32 &usageCountForProgrammingLanguages);

        virtual bool         considerSubTreeForHFileForCLanguage        () const;

        virtual bool         considerForComputingUsageCountForGroupingsForProgrammingLanguages () const;


    // Now the data members

    private :
        UI32 m_usageCount;
        UI32 m_usageCountForProgrammingLanguages;

    protected :
    public :
};

}

#endif // YANGGROUPING_H
