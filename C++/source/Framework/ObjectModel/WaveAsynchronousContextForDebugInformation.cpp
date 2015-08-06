/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForDebugInformation.h"

namespace WaveNs
{

WaveAsynchronousContextForDebugInformation::WaveAsynchronousContextForDebugInformation (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
    m_debugInformation  ("")
{
}

WaveAsynchronousContextForDebugInformation::~WaveAsynchronousContextForDebugInformation ()
{
}

void WaveAsynchronousContextForDebugInformation::setDebugInformation (const string &debugInformation)
{
    m_debugInformation = debugInformation;
}

const string & WaveAsynchronousContextForDebugInformation::getDebugInformation () const
{
    return (m_debugInformation);
}

}
