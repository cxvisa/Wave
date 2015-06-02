/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangGrouping.h"

namespace WaveNs
{

YangGrouping::YangGrouping ()
    : YangElement                         (getYangName (), ""),
      m_usageCount                        (0),
      m_usageCountForProgrammingLanguages (0)
{
}

YangGrouping::YangGrouping (const string &name)
    : YangElement                         (getYangName (), name),
      m_usageCount                        (0),
      m_usageCountForProgrammingLanguages (0)
{
}

YangGrouping::~YangGrouping()
{
}

string YangGrouping::getYangName ()
{
    return ("grouping");
}

YangElement *YangGrouping::createInstance ()
{
    return (new YangGrouping ());
}

void YangGrouping::incrementUsageCount (const UI32 &count)
{
    m_usageCount += count;
}

UI32 YangGrouping::getUsageCount () const
{
    return (m_usageCount);
}

void YangGrouping ::setUsageCount (const UI32 &usageCount)
{
    m_usageCount = usageCount;
}

void YangGrouping::incrementUsageCountForProgrammingLanguages (const UI32 &countForProgrammingLanguages)
{
    m_usageCountForProgrammingLanguages += countForProgrammingLanguages;
}

UI32 YangGrouping::getUsageCountForProgrammingLanguages () const
{
    return (m_usageCountForProgrammingLanguages);
}

void YangGrouping ::setUsageCountForProgrammingLanguages (const UI32 &usageCountForProgrammingLanguages)
{
    m_usageCountForProgrammingLanguages = usageCountForProgrammingLanguages;
}

bool YangGrouping::considerSubTreeForHFileForCLanguage () const
{
    if (0 < m_usageCountForProgrammingLanguages)
    {
        return (true);
    }
    else
    {
        cout << "SKIPPING ... " << getName () << endl;
        return (false);
    }
}

bool YangGrouping::considerForComputingUsageCountForGroupingsForProgrammingLanguages () const
{
    return (false);
}


}
