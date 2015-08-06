/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTGETYANGUSERINTERFACEWORKER_H
#define WAVESYSTEMMANAGEMENTGETYANGUSERINTERFACEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveSystemManagementObjectManager;
class WaveSystemManagementGetYangUserInterfaceMessage;

class WaveSystemManagementGetYangUserInterfaceWorker : public WaveWorker
{
    private :
        void getYangUserInterfaceMessageHandler                  (WaveSystemManagementGetYangUserInterfaceMessage *pWaveSystemManagementGetYangUserInterfaceMessage);
        void getYangUserInterfaceCreateYangUserInterfaceStep     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void getYangUserInterfaceApplyAAAOnYangUserInterfaceStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);


    protected :
    public :
                 WaveSystemManagementGetYangUserInterfaceWorker (WaveSystemManagementObjectManager *pWaveSystemManagementObjectManager);
        virtual ~WaveSystemManagementGetYangUserInterfaceWorker ();

    // Now the data members

    private :
        WaveSystemManagementObjectManager *m_pWaveSystemManagementObjectManager;

    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTGETYANGUSERINTERFACEWORKER_H
