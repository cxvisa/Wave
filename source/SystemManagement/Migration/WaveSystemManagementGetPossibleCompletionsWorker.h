/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTGETPOSSIBLECOMPLETIONSWORKER_H
#define WAVESYSTEMMANAGEMENTGETPOSSIBLECOMPLETIONSWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Modeling/YANG/ObjectModel/YangUserInterface.h"
#include "SystemManagement/CommandLineInterface/Client/CommandLineInterfaceEntry.h"

namespace WaveNs
{

class WaveSystemManagementGetPossibleCompletionsMessage; 

class WaveSystemManagementGetPossibleCompletionsWorker : public WaveWorker
{
    private :
        virtual PrismMessage *createMessageInstance (const UI32 &operationCode);

    protected :
    public :
                            WaveSystemManagementGetPossibleCompletionsWorker    (WaveObjectManager *pWaveObjectManager);
        virtual            ~WaveSystemManagementGetPossibleCompletionsWorker    ();
                void        getPossibleCompletionsMessageHandler                (WaveSystemManagementGetPossibleCompletionsMessage *pWaveSystemManagementGetPossibleCompletionsMessage); 
                void        initializeCommandLineInterfaces ();

    // Now the Data Members

    private :
    protected :
    public :
        CommandLineInterfaceEntry  *m_pTopLevelCommandLineinterfaceEntry;
        CommandLineInterfaceEntry  *m_pCommandLineInterfaceEntryForShowRunningConfig;
        CommandLineInterfaceEntry  *m_pCommandLineInterfaceEntryForShow;
        YangUserInterface          *m_pYangUserInterface;
        bool                        m_isInitializationDone;
};

}

#endif // WAVESYSTEMMANAGEMENTGETPOSSIBLECOMPLETIONSWORKER_H 
