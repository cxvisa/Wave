/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class PrismAsynchronousContext;
class WaveLinearSequencerContext;

class DatabaseObjectManagerInstallWorker : public WaveWorker
{
    private :
        void  install                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void  installValidateStep            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  installDatabaseStep            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  installBootDatabaseStep        (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  installShutdownDatabaseStep    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void  installCreatePrismDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);

    protected :
    public :
                 DatabaseObjectManagerInstallWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~DatabaseObjectManagerInstallWorker ();

    // Now the data members

    private :
        static bool m_fullInstallRequried;

    protected :
    public :
};

}
