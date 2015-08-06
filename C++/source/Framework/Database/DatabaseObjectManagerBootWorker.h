/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERBOOTWORKER_H
#define DATABASEOBJECTMANAGERBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

class WaveAsynchronousContextForBootPhases;

namespace WaveNs
{

class DatabaseObjectManagerBootWorker : public WaveWorker
{
    private :
        void  boot                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void  bootValidateStep          (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  bootDatabaseStep          (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  bootConnectToDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  bootReconnectToDatabaseOnInstallIfRequiredStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);

    protected :
    public :
                 DatabaseObjectManagerBootWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~DatabaseObjectManagerBootWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERBOOTWORKER_H
