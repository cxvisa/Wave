/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef WAVEPOSTPERSISTENTBOOTMESSAGES_H
#define WAVEPOSTPERSISTENTBOOTMESSAGES_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class WavePostPersistenceBootMessage : public WaveMessage
{
    private :
        virtual void           setupAttributesForSerialization();
    protected :
    public :
                               WavePostPersistenceBootMessage      ();
                               WavePostPersistenceBootMessage      (bool isPostbootRequired, bool executeConfigReplaySequence, bool executeNodeReadySequence, bool isBannerOutputToClientsRequired);
                               WavePostPersistenceBootMessage      (const UI32 &event, const UI32 &parameter, const ResourceId &recoveryType);
                virtual       ~WavePostPersistenceBootMessage      ();
                bool           getExecuteConfigReplaySequence       () const;
                void           setExecuteConfigReplaySequence       (bool executeConfigReplaySequence);
                bool           getExecuteNodeReadySequence          () const;
                void           setExecuteNodeReadySequence          (bool executeNodeReadySequence);
                bool           getIsPostbootRequired                () const;
                void           setIsPostbootRequired                (bool isPostbootRequired);
                bool           getIsBannerOutputToClientsRequired   () const;
                void           setIsBannerOutputToClientsRequired   (bool isBannerOutputToClientsRequired);
		void                   setEventId(const UI32 &eventId);
        UI32                   getEventId() const;
		void                   setParameter(const UI32 &parameter);
        UI32                   getParameter() const;
        void                   setRecoveryType(const ResourceId &recoveryType);
        ResourceId             getRecoveryType() const;

    // Now the data members
    private :
                bool           m_isPostbootRequired;
                bool           m_executeConfigReplaySequence;
                bool           m_executeNodeReadySequence;
                bool           m_isBannerOutputToClientsRequired;
                UI32           m_eventId;
                UI32           m_parameter;
                ResourceId     m_recoveryType;

    protected :
    public :
};

class WavePostPersistenceBootServiceAndWaveSlotsMessage : public WaveMessage
{
    private :
        virtual void            setupAttributesForSerialization                     ();
    protected :
    public :
                                WavePostPersistenceBootServiceAndWaveSlotsMessage  ();
        virtual                ~WavePostPersistenceBootServiceAndWaveSlotsMessage  ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // WAVEPOSTPERSISTENTBOOTMESSAGES_H
