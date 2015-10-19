/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Framework/Timer/TimerMessages.h"
#include "Framework/Timer/TimerObjectManager.h"

namespace WaveNs
{

TimerObjectManagerAddTimerMessage::TimerObjectManagerAddTimerMessage ()
  : WaveMessage (TimerObjectManager::getWaveServiceId (), TIMER_ADD_TIMER) ,
    m_timerId (0),
    m_pWaveTimerExpirationCallback (NULL),
    m_pWaveTimerExpirationContext (NULL)
{
    m_startInterval.tv_sec          = 0; 
    m_startInterval.tv_usec         = 0;
    m_periodicInterval.tv_sec       = 0;
    m_periodicInterval.tv_usec      = 0;
    m_startTime.tv_sec              = 0;
    m_startTime.tv_usec             = 0;
}

TimerObjectManagerAddTimerMessage::~TimerObjectManagerAddTimerMessage ()
{
}

TimerObjectManagerAddTimerMessage::TimerObjectManagerAddTimerMessage (timeval &startInterval, timeval &periodicInterval, timeval &startTime,
                        WaveTimerExpirationHandler pWaveTimerExpirationCallback, void *pWaveTimerExpirationContext, WaveElement *pWaveTimerSender)
    : WaveMessage (TimerObjectManager::getWaveServiceId (), TIMER_ADD_TIMER)
{
    m_startInterval.tv_sec          =   startInterval.tv_sec;
    m_startInterval.tv_usec         =   startInterval.tv_usec;
    m_periodicInterval.tv_sec       =   periodicInterval.tv_sec;
    m_periodicInterval.tv_usec      =   periodicInterval.tv_usec;
    m_startTime.tv_sec              =   startTime.tv_sec;
    m_startTime.tv_usec             =   startTime.tv_usec;

    m_pWaveTimerExpirationCallback   =   pWaveTimerExpirationCallback;
    m_pWaveTimerExpirationContext    =   pWaveTimerExpirationContext;
    m_pWaveTimerSender               =   pWaveTimerSender;
    m_timerId                         =   0; 

}

TimerHandle TimerObjectManagerAddTimerMessage::getTimerId ()
{
    return m_timerId;
}

timeval TimerObjectManagerAddTimerMessage::getStartInterval ()
{
    return m_startInterval;
}

timeval TimerObjectManagerAddTimerMessage::getPeriodicInterval ()
{
    return m_periodicInterval;
}

timeval TimerObjectManagerAddTimerMessage::getStartTime ()
{
    return m_startTime;
}

WaveTimerExpirationHandler TimerObjectManagerAddTimerMessage::getTimerExpirationCallback ()
{
    return m_pWaveTimerExpirationCallback;
}

void *TimerObjectManagerAddTimerMessage::getTimerExpirationContext ()
{
    return m_pWaveTimerExpirationContext;
}

WaveElement *TimerObjectManagerAddTimerMessage::getTimerSender ()
{
    return m_pWaveTimerSender;
}

void TimerObjectManagerAddTimerMessage::setTimerId (TimerHandle timerId)
{
    m_timerId   =   timerId;
}

TimerObjectManagerDeleteTimerMessage::TimerObjectManagerDeleteTimerMessage ()
    : WaveMessage (TimerObjectManager::getWaveServiceId (), TIMER_DELETE_TIMER),
      m_timerId(0)
{
}

TimerObjectManagerDeleteTimerMessage::TimerObjectManagerDeleteTimerMessage (TimerHandle timerId)
    : WaveMessage (TimerObjectManager::getWaveServiceId (), TIMER_DELETE_TIMER), m_timerId (timerId)
{
}

UI32 TimerObjectManagerDeleteTimerMessage::getTimerId ()
{
    return m_timerId;
}

TimerObjectManagerDeleteAllTimersForServiceMessage::TimerObjectManagerDeleteAllTimersForServiceMessage ()
    : WaveMessage (TimerObjectManager::getWaveServiceId (), TIMER_DELETE_ALL_TIMERS_FOR_SERVICE)
{
}

TimerObjectManagerDeleteAllTimersForServiceMessage::~TimerObjectManagerDeleteAllTimersForServiceMessage ()
{
}

}
