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
class PrismLinearSequencerContext;

class DatabaseObjectManagerInstallWorker : public WaveWorker
{
    private :
        void  install                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void  installValidateStep            (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  installDatabaseStep            (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  installBootDatabaseStep        (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  installShutdownDatabaseStep    (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void  installCreatePrismDatabaseStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);

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
