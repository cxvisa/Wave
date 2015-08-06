/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMMANAGEDOBJECTQUERYCONTEXT_H
#define PRISMMANAGEDOBJECTQUERYCONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContextBase.h"

namespace WaveNs
{

class WaveManagedObjectQueryContext : public PrismAsynchronousContext, public WaveManagedObjectQueryContextBase
{
    private :
    protected :
    public :
         WaveManagedObjectQueryContext (const string &classToQueryFor, WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        ~WaveManagedObjectQueryContext ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMMANAGEDOBJECTQUERYCONTEXT_H
