/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTYANGINTERFACESINITIALIZEWORKER_H
#define WAVESYSTEMMANAGEMENTYANGINTERFACESINITIALIZEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Modeling/YANG/ObjectModel/YangModuleCollection.h"
#include "Modeling/YANG/ObjectModel/YangUserInterface.h"

namespace WaveNs
{

class PrismLinearSequencerContext;
class WaveAsynchronousContextForBootPhases;
class WaveSystemManagementRebuildYangInterfacesMessage;

class WaveSystemManagementYangInterfacesInitializeWorker: public WaveWorker
{
    private :
        virtual WaveMessage   *createMessageInstance (const UI32 &operationCode);
        
                void            initialize                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void            initializeSystemManagementInterfaceStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);

                void            rebuildSystemManagementInterfaceStep    (PrismLinearSequencerContext *pPrismLinearSequencerContext);

                void            buildSystemManagementInterface          (YangModuleCollection *yangModuleCollection, YangUserInterface *yangUserInterface, string &yinForYangUserInterface);

        virtual void            boot                                    (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    protected :
    public :
                                WaveSystemManagementYangInterfacesInitializeWorker  (WaveObjectManager *pWaveObjectManager);
        virtual                ~WaveSystemManagementYangInterfacesInitializeWorker  ();
                
                 void           rebuildYangInterfacesMessageHandler                 (WaveSystemManagementRebuildYangInterfacesMessage *pWaveSystemManagementRebuildYangInterfacesMessage);

        YangModuleCollection   *getYangModuleCollection ();
        YangUserInterface      *getYangUserInterface ();
        YangUserInterface      *getClonedYangUserInterface ();
        string                 &getYinForYangUserInterface ();

    // Now the Data Members
    private :
        YangModuleCollection    *m_pYangModuleCollection;
        YangUserInterface       *m_pYangUserInterface;
        string                   m_yinForYangUserInterface;
        bool                     m_alreadyInitialized;
    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTYANGINTERFACESINITIALIZEWORKER_H
