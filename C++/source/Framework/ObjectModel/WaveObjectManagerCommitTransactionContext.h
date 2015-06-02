/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEOBJECTMANAGERCOMMITTRANSACTIONCONTEXT_H
#define WAVEOBJECTMANAGERCOMMITTRANSACTIONCONTEXT_H

namespace WaveNs
{

class PrismLinearSequencerContext;
class PrismSynchronousLinearSequencerContext;

class WaveObjectManagerCommitTransactionContext
{
    private :
    protected :
    public :
                                        WaveObjectManagerCommitTransactionContext   ();
                                        WaveObjectManagerCommitTransactionContext   (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                                        WaveObjectManagerCommitTransactionContext   (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        virtual                        ~WaveObjectManagerCommitTransactionContext   ();

                bool                    getIsADelayedCommitTransaction              () const;
                void                    setIsADelayedCommitTransaction              (const bool &isADelayedCommitTransaction);

    // Now the data members

    private :
        bool                            m_isADelayedCommitTransaction;

    protected :
    public :
};

}
#endif // WAVEOBJECTMANAGERCOMMITTRANSACTIONCONTEXT_H

