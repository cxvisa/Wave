/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"

namespace WaveNs
{

WaveManagedObjectSynchronousQueryContext::WaveManagedObjectSynchronousQueryContext (const string &classToQueryFor)
    : WaveManagedObjectQueryContextBase (classToQueryFor)
{
}

WaveManagedObjectSynchronousQueryContext::~WaveManagedObjectSynchronousQueryContext ()
{
}

}
