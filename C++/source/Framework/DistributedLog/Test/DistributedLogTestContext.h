/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGTESTCONTEXT_H
#define DISTRIBUTEDLOGTESTCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"

namespace WaveNs
{

class DistributedLogTestContext : public PrismLinearSequencerContext
{
    private:
    protected:
    public:
                                DistributedLogTestContext       (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                ~DistributedLogTestContext       (); 

                UI64            getOriginalMaxAllowedLogEntries () const;
                void            setOriginalMaxAllowedLogEntries (const UI64 &originalMaxAllowedLogEntries);

                UI64            getCurrentMaxAllowedLogEntries  () const;
                void            setCurrentMaxAllowedLogEntries  (const UI64 &currentMaxAllowedLogEntries);

                UI64            getFirstLogId                   () const;
                void            setFirstLogId                   (const UI64 &firstLogId);

                UI64            getNextLogId                    () const;
                void            setNextLogId                    (const UI64 &nextLogId);

                WaveServiceId  getWaveServiceId               () const;
                void            setWaveServiceId               (const WaveServiceId &prismServiceId);

                ObjectId        getManagedObjectId              () const;
                void            setManagedObjectId              (const ObjectId &managedObjectId);

                UI32            getNumberOfFailures             () const;
                void            setNumberOfFailures             (UI32 numberOfFailures);
                void            incrementNumberOfFailures       ();
        
    // Now the data members
    private:
                UI64            m_originalMaxAllowedLogEntries;
                UI64            m_currentMaxAllowedLogEntries;
                UI64            m_firstLogId;
                UI64            m_nextLogId;
                WaveServiceId  m_prismServiceId;
                ObjectId        m_managedObjectId;
                UI32            m_numberOfFailures;

    protected:
    public:
};

}

#endif // DISTRIBUTEDLOGTESTCONTEXT_H
