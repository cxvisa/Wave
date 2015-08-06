/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef PERSISTENCELOCALEXECUTETRANSACTIONCONTEXT_H
#define PERSISTENCELOCALEXECUTETRANSACTIONCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/Types/Types.h"

using namespace std;

namespace WaveNs
{

class PersistenceLocalExecuteTransactionContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                             PersistenceLocalExecuteTransactionContext    (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                             PersistenceLocalExecuteTransactionContext    (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);

        virtual                             ~PersistenceLocalExecuteTransactionContext    ();

                UI32                         getCurrentTransactionId                      () const;
                void                         setCurrentTransactionId                      (const UI32 &currentTransactionId);
                LocationId                   getSenderLocationId                          () const;
                void                         setSenderLocationId                          (const LocationId &locationId);
                bool                         getIsCommit                                  () const;
                void                         setIsCommit                                  (const bool &isCommit);
                bool                         getIsRollback                                () const;
                void                         setIsRollback                                (const bool &isRollback);
                bool                         getIsPrepare                                 () const;
                void                         setIsPrepare                                 (const bool &isPrepare);
                bool                         getIsConfigurationChange                     () const;
                void                         setIsConfigurationChange                     (const bool &isConfigurationChange);
                bool                         getIsConfigurationTimeChange                 () const;
                void                         setIsConfigurationTimeChange                 (const bool &isConfigurationTimeChange);
                ResourceId                   getActiveResult                              () const;
                void                         setActiveResult                              (const ResourceId &result);
                ResourceId                   getStandbyResult                             () const;
                void                         setStandbyResult                             (const ResourceId &result);

    // now the data members

    private :
        UI32                        m_currentTransactionId;
        LocationId                  m_senderLocationId;
        bool                        m_isCommit;
        bool                        m_isRollback;
        bool                        m_isPrepare;
        bool                        m_isConfigurationChange;
        bool                        m_isConfigurationTimeChange;
        ResourceId                  m_activeResult;
        ResourceId                  m_standbyResult;
    protected :
    public :
};

}

#endif // PERSISTENCELOCALEXECUTETRANSACTIONCONTEXT_H
