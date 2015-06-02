/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMMESSAGEQUEUE_H
#define PRISMMESSAGEQUEUE_H

#include <deque>
#include "Framework/Messaging/Local/PrismMessage.h"
#include "Framework/Utils/PrismMutex.h"

using namespace std;

namespace WaveNs
{

template<class T> class PrismMessageQueue // This is a thread safe class
{
    private :
    protected :
    public :
                            PrismMessageQueue              ();
                           ~PrismMessageQueue              ();
        void                insertAtTheBack                (T *&pPrismMessage);
        void                insertAtTheFront               (T *&pPrismMessage);
        void                removeFromFront                ();
        WaveMessageStatus  remove                          (T *&pPrismMessage);
        UI32                removeTimerExpirationsForTimer (const TimerHandle &timerHandle);
        UI32                getSize                        ();
        T                  *getFromFront                   ();
        T                  *removeAndGetFromFront          ();
        bool                isEmpty                        ();

    // Now the data members

    private :
        std::deque<T *> m_messageQueue;
        PrismMutex      m_prismMutex;
    protected :
    public :
};

}

#endif //PRISMMESSAGEQUEUE_H
