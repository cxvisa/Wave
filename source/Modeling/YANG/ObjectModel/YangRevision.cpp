/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangRevision.h"

namespace WaveNs
{

YangRevision::YangRevision ()
    : YangElement (getYangName (), ""){
}

YangRevision::YangRevision (const Date &date)
    : YangElement (getYangName (), ""),
      m_date      (date)
{
}

YangRevision::~YangRevision()
{
}

string YangRevision::getYangName ()
{
    return ("revision");
}

YangElement *YangRevision::createInstance ()
{
    return (new YangRevision ());
}

Date YangRevision::getDate () const
{
    return (m_date);
}

void YangRevision::setDate (const Date &date)
{
    m_date = date;
}

}
