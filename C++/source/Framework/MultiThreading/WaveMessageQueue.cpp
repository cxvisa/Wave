/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/MultiThreading/WaveMessageQueue.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Core/PrismFrameworkMessages.h"

using namespace std;

namespace WaveNs
{

template<class T> WaveMessageQueue<T>::WaveMessageQueue ()
{
}

template<class T> WaveMessageQueue<T>::~WaveMessageQueue ()
{
}

template<class T> void WaveMessageQueue<T>::insertAtTheBack (T *&pWaveMessage)
{
    m_prismMutex.lock ();
    m_messageQueue.push_back (pWaveMessage);
    m_prismMutex.unlock ();
}

template<class T> void WaveMessageQueue<T>::insertAtTheFront (T *&pWaveMessage)
{
    m_prismMutex.lock ();
    m_messageQueue.push_front (pWaveMessage);
    m_prismMutex.unlock ();
}

template<class T> void WaveMessageQueue<T>::removeFromFront ()
{
    m_prismMutex.lock ();
    m_messageQueue.pop_front ();
    m_prismMutex.unlock ();
}

template<class T> WaveMessageStatus WaveMessageQueue<T>::remove (T *&pWaveMessage)
{
    m_prismMutex.lock ();

    WaveMessageStatus                    status  = WAVE_MESSAGE_ERROR_UNKNOWN_MESSAGE;
    std::deque<WaveMessage *>::iterator element = m_messageQueue.begin ();
    std::deque<WaveMessage *>::iterator end     = m_messageQueue.end ();

    while (element != end)
    {
        if (pWaveMessage == (*element))
        {
            m_messageQueue.erase (element);
            status = WAVE_MESSAGE_SUCCESS;
            break;
        }

        element++;
    }

    m_prismMutex.unlock ();

    return (status);
}

template<class T> UI32 WaveMessageQueue<T>::removeTimerExpirationsForTimer (const TimerHandle &timerHandle)
{
    m_prismMutex.lock ();

    std::deque<WaveMessage *>::iterator   element                                = m_messageQueue.begin ();
    std::deque<WaveMessage *>::iterator   end                                    = m_messageQueue.end ();
    PrismTimerExpiredObjectManagerMessage *pPrismTimerExpiredObjectManagerMessage = NULL;
    std::deque<WaveMessage *>             tempMessageQueue;
    UI32                                   numberOfExpirationsEncountered         = 0;

    while (element != end)
    {
        pPrismTimerExpiredObjectManagerMessage = dynamic_cast<PrismTimerExpiredObjectManagerMessage *> (*element);

        prismAssert (NULL != pPrismTimerExpiredObjectManagerMessage, __FILE__, __LINE__);

        if ((pPrismTimerExpiredObjectManagerMessage->getTimerId ()) == timerHandle)
        {
            numberOfExpirationsEncountered++;
            delete pPrismTimerExpiredObjectManagerMessage;
        }
        else
        {
            tempMessageQueue.push_back (pPrismTimerExpiredObjectManagerMessage);
        }

        element++;
    }

    m_messageQueue.clear ();

    element = tempMessageQueue.begin ();
    end     = tempMessageQueue.end ();

    while (element != end)
    {
        m_messageQueue.push_back (*element);
        element++;
    }

    tempMessageQueue.clear ();

    m_prismMutex.unlock ();

    return (numberOfExpirationsEncountered);
}

template<class T> T *WaveMessageQueue<T>::getFromFront ()
{
    m_prismMutex.lock ();

    if (true == (m_messageQueue.empty ()))
    {
        m_prismMutex.unlock ();

        return (NULL);
    }
    else
    {
        T *pTemp = m_messageQueue.front ();

        m_prismMutex.unlock ();

        return (pTemp);
    }
}

template<class T> T *WaveMessageQueue<T>::removeAndGetFromFront ()
{
    m_prismMutex.lock ();

    if (true == (m_messageQueue.empty ()))
    {
        m_prismMutex.unlock ();

        return (NULL);
    }
    else
    {
        T *pTemp = m_messageQueue.front ();

        m_messageQueue.pop_front ();

        m_prismMutex.unlock ();

        return (pTemp);
    }
}

template<class T> UI32 WaveMessageQueue<T>::getSize ()
{
    UI32 numberOfEntriesInTheMessageQueue = 0;

    m_prismMutex.lock ();
    numberOfEntriesInTheMessageQueue = m_messageQueue.size ();
    m_prismMutex.unlock ();

    return (numberOfEntriesInTheMessageQueue);
}

template<class T> bool WaveMessageQueue<T>::isEmpty ()
{
    bool isMessageQueueEmpty = true;

    m_prismMutex.lock ();
    isMessageQueueEmpty = m_messageQueue.empty ();
    m_prismMutex.unlock ();

    return (isMessageQueueEmpty);
}

}
