/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef TIMEROBJECTMANAGER_H
#define TIMEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/Timer/TimerWorker.h"

namespace WaveNs
{

class TimerObjectManager : public WaveLocalObjectManager
{
    private :
                        TimerObjectManager  ();

    protected :
    public :
        virtual                    ~TimerObjectManager  ();
        static  TimerObjectManager *getInstance         ();
        static  WaveServiceId      getWaveServiceId   ();
                void                disable             (PrismAsynchronousContext *pPrismAsynchronousContext);

    // Now the data members

    private :
    protected :
    public :
       TimerWorker *m_pTimerWorker;
};

}

#endif // TIMEROBJECTMANAGER_H
