/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangNameSpace.h"

namespace WaveNs
{

YangNameSpace::YangNameSpace ()
    : YangElement (getYangName (), "")
{
}

YangNameSpace::YangNameSpace (const string &uri)
    : YangElement (getYangName (), ""),
      m_uri       (uri)
{
}

YangNameSpace::~YangNameSpace()
{
}

string YangNameSpace::getYangName ()
{
    return ("namespace");
}

YangElement *YangNameSpace::createInstance ()
{
    return (new YangNameSpace ());
}

void YangNameSpace::processAttribute (const string &attributeName, const string &attributeValue)
{
    if ("uri" == attributeName)
    {
        setUri (attributeValue);
    }
}

string YangNameSpace::getUri () const
{
    return (m_uri);
}

void YangNameSpace::setUri (const string &uri)
{
    m_uri = uri;

    setName (m_uri);
}

}
