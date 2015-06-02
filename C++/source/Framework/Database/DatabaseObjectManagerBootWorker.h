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
        void  bootValidateStep          (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  bootDatabaseStep          (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  bootConnectToDatabaseStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  bootReconnectToDatabaseOnInstallIfRequiredStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);

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
