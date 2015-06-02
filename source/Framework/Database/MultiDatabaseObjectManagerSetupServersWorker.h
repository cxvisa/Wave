/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MULTIDATABASEOBJECTMANAGERSETUPSERVERSWORKER_H
#define MULTIDATABASEOBJECTMANAGERSETUPSERVERSWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;

class MultiDatabaseObjectManagerSetupServersWorker : public WaveWorker
{
    private :
        virtual void boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    protected :
    public :
                 MultiDatabaseObjectManagerSetupServersWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~MultiDatabaseObjectManagerSetupServersWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // MULTIDATABASEOBJECTMANAGERSETUPSERVERSWORKER_H
