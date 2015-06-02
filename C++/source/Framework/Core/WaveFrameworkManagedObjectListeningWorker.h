/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKMANAGEDOBJECTLISTENINGWORKER_H
#define WAVEFRAMEWORKMANAGEDOBJECTLISTENINGWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveFrameworkManagedObjectListeningWorker : public WaveWorker
{

    private :
    protected :
    public :
                 WaveFrameworkManagedObjectListeningWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~WaveFrameworkManagedObjectListeningWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEFRAMEWORKMANAGEDOBJECTLISTENINGWORKER_H
