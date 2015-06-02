/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangPattern.h"

namespace WaveNs
{

YangPattern::YangPattern ()
    : YangElement (getYangName (), "")
{
}

YangPattern::~YangPattern()
{
}

string YangPattern::getYangName ()
{
    return ("pattern");
}

YangElement *YangPattern::createInstance ()
{
    return (new YangPattern ());
}

}
