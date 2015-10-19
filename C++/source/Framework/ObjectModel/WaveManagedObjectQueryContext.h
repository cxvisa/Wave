/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTQUERYCONTEXT_H
#define WAVEMANAGEDOBJECTQUERYCONTEXT_H

#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContextBase.h"

namespace WaveNs
{

class WaveManagedObjectQueryContext : public WaveAsynchronousContext, public WaveManagedObjectQueryContextBase
{
    private :
    protected :
    public :
         WaveManagedObjectQueryContext (const string &classToQueryFor, WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        ~WaveManagedObjectQueryContext ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTQUERYCONTEXT_H
