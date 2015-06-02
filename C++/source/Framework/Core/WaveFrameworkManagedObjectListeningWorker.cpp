/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkManagedObjectListeningWorker.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"

namespace WaveNs
{

WaveFrameworkManagedObjectListeningWorker::WaveFrameworkManagedObjectListeningWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
}

WaveFrameworkManagedObjectListeningWorker::~WaveFrameworkManagedObjectListeningWorker ()
{
}

}
