/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Shell/ShellObjectManager.h"
#include "Shell/ShellRegression.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

ShellObjectManager::ShellObjectManager ()
    : WaveLocalObjectManagerForUserSpecificTasks ("Shell")
{
    setAllowAutomaticallyUnlistenForEvents (false);

    m_pWaveShell = new ShellWave (this);
}

ShellObjectManager *ShellObjectManager::getInstance ()
{
    static ShellObjectManager *pShellObjectManager = NULL;

    if (NULL == pShellObjectManager)
    {
        pShellObjectManager = new ShellObjectManager ();
        WaveNs::waveAssert (NULL != pShellObjectManager, __FILE__, __LINE__);
    }

    return (pShellObjectManager);
}

ShellObjectManager::~ShellObjectManager ()
{
    if (NULL != m_pWaveShell)
    {
        delete m_pWaveShell;
    }
}

WaveServiceId ShellObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void ShellObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "ShellObjectManager::initialize : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ShellObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    trace (TRACE_LEVEL_DEVEL, "ShellObjectManager::boot : Entering ...");

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ShellObjectManager::listenForEvents (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    listenForEvent (WaveFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION, reinterpret_cast<WaveEventHandler> (&ShellObjectManager::bootCompleteForThisLocationEventHandler));

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

void ShellObjectManager::bootCompleteForThisLocationEventHandler (const BootCompleteForThisLocationEvent *&pBootCompleteForThisLocationEvent)
{
    // Since we told framework not to unlistenEvents, we must explicitly unlisten for events since we are going to go into an infinite while loop.

    unlistenEvents ();

    reply (reinterpret_cast<const WaveEvent *&> (pBootCompleteForThisLocationEvent));

    if (false == (FrameworkToolKit::getIsRunningAsADaemon ()))
    {
        trace (TRACE_LEVEL_INFO, "Now Entering Shell Mode.");

        m_pWaveShell->shellExecuteHandler ();
    }
}

}
