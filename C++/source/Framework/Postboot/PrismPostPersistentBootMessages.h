/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PRISMPOSTPERSISTENTBOOTMESSAGES_H
#define PRISMPOSTPERSISTENTBOOTMESSAGES_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class PrismPostPersistenceBootMessage : public WaveMessage
{
    private :
        virtual void           setupAttributesForSerialization();
    protected :
    public :
                               PrismPostPersistenceBootMessage      ();
                               PrismPostPersistenceBootMessage      (bool isPostbootRequired, bool executeConfigReplaySequence, bool executeNodeReadySequence, bool isBannerOutputToClientsRequired);
                               PrismPostPersistenceBootMessage      (const UI32 &event, const UI32 &parameter, const ResourceId &recoveryType);
                virtual       ~PrismPostPersistenceBootMessage      ();
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

class PrismPostPersistenceBootServiceAndWaveSlotsMessage : public WaveMessage
{
    private :
        virtual void            setupAttributesForSerialization                     ();
    protected :
    public :
                                PrismPostPersistenceBootServiceAndWaveSlotsMessage  ();
        virtual                ~PrismPostPersistenceBootServiceAndWaveSlotsMessage  ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // PRISMPOSTPERSISTENTBOOTMESSAGES_H
