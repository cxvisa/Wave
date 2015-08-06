/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef TIMERSIGNALOBJECTMANAGER_H
#define TIMERSIGNALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"


namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;

class TimerSignalObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                TimerSignalObjectManager ();
        void catchTimerAlarm          ();

    protected :
    public :
        virtual                          ~TimerSignalObjectManager ();
        static  TimerSignalObjectManager *getInstance              ();
        static  WaveServiceId            getWaveServiceId        ();
                void                      boot                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // TIMERSIGNALOBJECTMANAGER_H
