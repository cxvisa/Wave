
/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef TIMERWORKER_H
#define TIMERWORKER_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Timer/TimerMessages.h"
#include "Framework/Utils/WaveMutex.h"
#include <vector>
#include <map>

extern "C" void waveProcessAlarmSignal ();

namespace WaveNs
{

class TimerData;

class TimerWorker : public WaveWorker
{
    private :
                void        addTimerToList                          (TimerData *pTimerInfo);
                UI32        removeTimer                             (TimerObjectManagerDeleteTimerMessage *pMessage, UI32 timerId);
                void        removeTimerFromServiceTimersMultimap    (WaveServiceId serviceId, UI32 timerId);
                int         restartTimer                            ();
                UI32        binarySearch                            (int first, int last, timeval &key);
                void        showPendingTimers                       ();
                void        addTimer                                (TimerObjectManagerAddTimerMessage *pMessage);
                void        deleteTimer                             (TimerObjectManagerDeleteTimerMessage *pMessage);
                void        deleteAllTimersForService               (TimerObjectManagerDeleteAllTimersForServiceMessage *pMessage);
                void        removeAllTimers                         ();
                ResourceId  removeAllTimersForService               (UI32 serviceId);

    protected :
    public :
                            TimerWorker                             (WaveObjectManager *pWaveObjectManager);
                           ~TimerWorker                             ();

                void        timerSendOneWay                         (WaveMessage *pWaveMessage);
                void        timerReply                              (WaveMessage *pWaveMessage);
        static  void        processTimeOut                          ();
        static  void        resetMaxDelay                           ();
        static  void        showMaxDelay                            ();
                void        deleteAllTimers                         ();

        // Now the data members

    private :
                vector<TimerData *>             m_timerList;
                multimap<WaveServiceId, UI32>  m_timerIdsByServiceId;
                UI32                            m_nTimers;
                WaveMutex                      m_mutex;
                UI32                            m_currTimerId;
                timeval                         m_maxDelay;

    protected :
    public :

};

class TimerData
{
    private :
    protected :
    public :
                TimerData                       ();
               ~TimerData                       ();

        // Now the data members

    private :
    protected :
    public :
                timeval                     m_periodicInterval;
                timeval                     m_expirationTime;
                UI32                        m_timerId;
                WaveTimerExpirationHandler  m_pWaveTimerExpirationCallback;
                void                       *m_pWaveTimerExpirationContext;
                WaveElement                *m_pWaveTimerSender;
                WaveServiceId               m_serviceId;
};

}
#endif //TIMERWORKER_H

