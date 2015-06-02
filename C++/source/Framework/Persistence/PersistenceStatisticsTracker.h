/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/
    
#ifndef PERSISTENCESTATISTICSTRACKER_H
#define PERSISTENCESTATISTICSTRACKER_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class PersistenceStatisticsTracker
{
    private :
    protected :
    public :
        static  void                incrementPrepareTransactionsRequested                           (UI32 serviceId);
        static  void                incrementPrepareTransactionsRequested                           (UI32 serviceId, UI32 numberOfTransactions);
        static  void                incrementPrepareTransactionsExecuted                            (UI32 serviceId);
        static  void                incrementPrepareTransactionsMarkedExecutedOnPrimary             (UI32 serviceId);
        static  void                incrementPrepareTransactionsMarkedDisconnectedOnSecondary       (UI32 serviceId);
        static  void                incrementCommitTransactionsRequested                            (UI32 serviceId);
        static  void                incrementCommitTransactionsRequested                            (UI32 serviceId, UI32 numberOfTransactions);
        static  void                incrementCommitTransactionsExecuted                             (UI32 serviceId);
        static  void                incrementRollbackTransactionsRequested                          (UI32 serviceId);
        static  void                incrementRollbackTransactionsRequested                          (UI32 serviceId, UI32 numberOfTransactions);
        static  void                incrementRollbackTransactionsExecuted                           (UI32 serviceId);

        static  string              getPrepareTransactionsRequestedStatistics                       ();
        static  string              getPrepareTransactionsExecutedStatistics                        ();
        static  string              getPrepareTransactionsMarkedExecutedOnPrimaryStatistics         ();
        static  string              getPrepareTransactionsMarkedDisconnectedOnSecondaryStatistics   ();
        static  string              getCommitTransactionsRequestedStatistics                        ();
        static  string              getCommitTransactionsExecutedStatistics                         ();
        static  string              getRollbackTransactionsRequestedStatistics                      ();
        static  string              getRollbackTransactionsExecutedStatistics                       ();

        static  string              getAllTransactionStatistics                                     ();

        static  void                clearPrepareTransactionsRequestedMap                            ();
        static  void                clearPrepareTransactionsExecutedMap                             ();
        static  void                clearPrepareTransactionsMarkedExecutedOnPrimaryMap              ();
        static  void                clearPrepareTransactionsMarkedDisconnectedOnSecondaryMap        ();
        static  void                clearCommitTransactionsRequestedMap                             ();
        static  void                clearCommitTransactionsExecutedMap                              ();
        static  void                clearRollbackTransactionsRequestedMap                           ();
        static  void                clearRollbackTransactionsExecutedMap                            ();
        
        static  void                clearAllTransactionStatistics                                   ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // PERSISTENCESTATISTICSTRACKER_H
