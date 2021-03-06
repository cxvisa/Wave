/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef TIMERMESSAGES_H
#define TIMERMESSAGES_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Timer/TimerTypes.h"

namespace WaveNs
{

class TimerObjectManagerAddTimerMessage : public WaveMessage
{
    private :
    protected :
    public :
        virtual                            ~TimerObjectManagerAddTimerMessage   ();
                                            TimerObjectManagerAddTimerMessage   ();
                                            TimerObjectManagerAddTimerMessage   (timeval &startInterval, timeval &periodicInterval, timeval &startTime, WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext, WaveElement *pWaveTimerSender);
                TimerHandle                 getTimerId                          ();
                timeval                     getStartInterval                    ();
                timeval                     getPeriodicInterval                 ();
                timeval                     getStartTime                        ();
                WaveTimerExpirationHandler getTimerExpirationCallback          ();
                void                       *getTimerExpirationContext           ();
                WaveElement               *getTimerSender                      ();
                void                        setTimerId                          (TimerHandle timerId);

    // Now the data members

    private :
        timeval                     m_startInterval;
        timeval                     m_periodicInterval;
        timeval                     m_startTime;
        TimerHandle                 m_timerId;
        WaveTimerExpirationHandler m_pWaveTimerExpirationCallback;
        void                       *m_pWaveTimerExpirationContext;
        WaveElement               *m_pWaveTimerSender;
    protected :
    public :
};

class TimerObjectManagerDeleteTimerMessage : public WaveMessage
{
    private :
    protected :
    public :
                    TimerObjectManagerDeleteTimerMessage    ();
                    TimerObjectManagerDeleteTimerMessage    (TimerHandle timerId);
        UI32        getTimerId                              ();
    // Now the data members

    private :
    protected :
    public :
        UI32        m_timerId;

};

class TimerObjectManagerDeleteAllTimersForServiceMessage : public WaveMessage
{
    private :
    protected :
    public :
                    TimerObjectManagerDeleteAllTimersForServiceMessage  ();
                   ~TimerObjectManagerDeleteAllTimersForServiceMessage  ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // TIMERMESSAGES_H
