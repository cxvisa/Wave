/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGEQUEUE_H
#define WAVEMESSAGEQUEUE_H

#include <deque>
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/WaveMutex.h"

using namespace std;

namespace WaveNs
{

template<class T> class WaveMessageQueue // This is a thread safe class
{
    private :
    protected :
    public :
                            WaveMessageQueue              ();
                           ~WaveMessageQueue              ();
        void                insertAtTheBack                (T *&pWaveMessage);
        void                insertAtTheFront               (T *&pWaveMessage);
        void                removeFromFront                ();
        WaveMessageStatus  remove                          (T *&pWaveMessage);
        UI32                removeTimerExpirationsForTimer (const TimerHandle &timerHandle);
        UI32                getSize                        ();
        T                  *getFromFront                   ();
        T                  *removeAndGetFromFront          ();
        bool                isEmpty                        ();

    // Now the data members

    private :
        std::deque<T *> m_messageQueue;
        WaveMutex      m_waveMutex;
    protected :
    public :
};

}

#endif //WAVEMESSAGEQUEUE_H
