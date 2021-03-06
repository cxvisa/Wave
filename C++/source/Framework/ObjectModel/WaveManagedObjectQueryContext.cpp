/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectQueryContext.h"

namespace WaveNs
{

WaveManagedObjectQueryContext::WaveManagedObjectQueryContext (const string &classToQueryFor, WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext           (pCaller, pCallback, pCallerContext),
      WaveManagedObjectQueryContextBase (classToQueryFor)
{
}

WaveManagedObjectQueryContext::~WaveManagedObjectQueryContext ()
{
}

}
