/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEOBJECTMANAGERCOMMITTRANSACTIONCONTEXT_H
#define WAVEOBJECTMANAGERCOMMITTRANSACTIONCONTEXT_H

namespace WaveNs
{

class WaveLinearSequencerContext;
class WaveSynchronousLinearSequencerContext;

class WaveObjectManagerCommitTransactionContext
{
    private :
    protected :
    public :
                                        WaveObjectManagerCommitTransactionContext   ();
                                        WaveObjectManagerCommitTransactionContext   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                                        WaveObjectManagerCommitTransactionContext   (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
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

