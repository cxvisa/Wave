/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef QUERYUTILS_H
#define QUERYUTILS_H

#include <string>
#include "Framework/ObjectRelationalMapping/OrmRepository.h"

using namespace std;

namespace WaveNs
{

class WaveManagedObjectSynchronousQueryContext;

class QueryUtils
{
    private :
    protected :
    public :
        static  vector<WaveManagedObject *> *querySynchronouslyByName (const string &managedClassName, const string &managedObjectName, const string &schema = OrmRepository::getWaveCurrentSchema ());   
        static  vector<WaveManagedObject *> *querySynchronously (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext);

    // Now the data members
    
    private :
    protected :
    public :
};

}

#endif //QUERYUTILS_H
