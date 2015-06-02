/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXT_H
#define PRISMMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContextBase.h"

namespace WaveNs
{

class WaveManagedObjectSynchronousQueryContext : public WaveManagedObjectQueryContextBase
{
    private :
    protected :
    public :
         WaveManagedObjectSynchronousQueryContext (const string &classToQueryFor);
        ~WaveManagedObjectSynchronousQueryContext ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXT_H
