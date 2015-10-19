/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/QueryUtils.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"

namespace WaveNs
{

vector<WaveManagedObject *> *QueryUtils::querySynchronouslyByName (const string &managedClassName, const string &managedObjectName, const string &schema)
{
    return ((WaveFrameworkObjectManager::getInstance ())->querySynchronouslyByName (managedClassName, managedObjectName, schema));

}

vector<WaveManagedObject *> *QueryUtils::querySynchronously (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext)
{
    return ((WaveFrameworkObjectManager::getInstance ())->querySynchronously (pWaveManagedObjectSynchronousQueryContext));

}

}
