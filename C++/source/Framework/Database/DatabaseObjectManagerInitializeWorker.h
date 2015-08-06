/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERINITIALIZEWORKER_H
#define DATABASEOBJECTMANAGERINITIALIZEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveObjectManager;
class PrismAsynchronousContext;
class WaveLinearSequencerContext;

class DatabaseObjectManagerInitializeWorker : public WaveWorker
{
    private :
                void initialize                                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void initializeCreateObjectRelationalMappingStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        virtual void zeroize						             (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForBootPhases);
                void zeroizeDatabaseStep                         (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void zeroizeDatabaseBackupFilesStep              (WaveLinearSequencerContext *pWaveLinearSequencerContext);

    protected :
    public :
                DatabaseObjectManagerInitializeWorker            (WaveObjectManager *pWaveObjectManager);
                ~DatabaseObjectManagerInitializeWorker           ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERINITIALIZEWORKER_H
