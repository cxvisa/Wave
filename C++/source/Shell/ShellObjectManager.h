/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef SHELLOBJECTMANAGER_H
#define SHELLOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Shell/ShellWave.h"
#include <iostream>
#include <fstream>

namespace WaveNs
{

class ShellObjectManager;
class BootCompleteForThisLocationEvent;
class WaveAsynchronousContextForBootPhases;

class ShellObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                ShellObjectManager                             ();

        virtual void initialize                                (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void boot                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        virtual void   listenForEvents                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void   bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent);


    protected :
    public :
        virtual                    ~ShellObjectManager ();
        static  ShellObjectManager *getInstance        ();
        static  WaveServiceId      getWaveServiceId  ();

    // Now the data members

    private :
    protected :
    public :
        ShellWave *m_pWaveShell;
        ifstream    m_inputSource;
};

}

#endif // SHELLOBJECTMANAGER_H
