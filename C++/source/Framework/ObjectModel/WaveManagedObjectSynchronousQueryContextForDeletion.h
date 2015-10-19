/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXTFORDELETION_H
#define WAVEMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXTFORDELETION_H

#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectRelationalMapping/OrmTable.h"

namespace WaveNs
{

class WaveManagedObjectSynchronousQueryContextForDeletion : public WaveManagedObjectSynchronousQueryContext
{
    private :
                void                            getSqlForDeleteFromDerivationAndAuxilliaryTables    (string &sql, string instanceIdSql, OrmTable *pTable);
    protected :
    public :
                                                WaveManagedObjectSynchronousQueryContextForDeletion (const string &classToQueryFor);
        virtual                                ~WaveManagedObjectSynchronousQueryContextForDeletion ();

                UI32                            getPageSizeForQueryResults                          ();

                void                            setPageSizeForQueryResults                          (UI32 limitForQueryResults);
                void                            setPageQueryContext                                 (WaveObjectManager* callingOm);
                bool                            isPageQueryContextSet                               ();
                string                          getPageQuerySql                                     ();
                void                            moveOffsetOnSuccessfulQuery                         ();
                string                          getSqlWithPagingEnabled                             (WaveObjectManager* callingOm);
                void                            getSqlForDelete                                     (string &sql);
                void                            getSqlForDeletingCompositions                       (string &sql, set<string> compositions = set<string>());
                void                            getSqlForDeletingCompositionsPerTable               (string &sql, set<string> compositions, OrmTable *pTable);
                void                            getSqlForPartialDeleteFromVectorCompositions        (string &sql, string &parentClassName, string &compositionName);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXTFORDELETION_H
