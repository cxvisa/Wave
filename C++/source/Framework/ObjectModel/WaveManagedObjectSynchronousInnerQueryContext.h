/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTSYNCHRONOUSINNERQUERYCONTEXT_H 
#define WAVEMANAGEDOBJECTSYNCHRONOUSINNERQUERYCONTEXT_H

#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectRelationalMapping/OrmTable.h"

namespace WaveNs
{

class WaveManagedObjectSynchronousInnerQueryContext : public WaveManagedObjectSynchronousQueryContext
{
    private :
    protected :
    public :
                                                WaveManagedObjectSynchronousInnerQueryContext       (const string &classToQueryFor);
        virtual                                ~WaveManagedObjectSynchronousInnerQueryContext       ();

                UI32                            getPageSizeForQueryResults                          ();

                void                            setPageSizeForQueryResults                          (UI32 limitForQueryResults);
                void                            setPageQueryContext                                 (WaveObjectManager* callingOm);
                bool                            isPageQueryContextSet                               ();
                string                          getPageQuerySql                                     ();
                void                            moveOffsetOnSuccessfulQuery                         ();
                string                          getSqlWithPagingEnabled                             (WaveObjectManager* callingOm);

                string                          getSqlForSelect                                     (const bool &forCount = false);
                void                            addSelectField                                      (const string &selectField);
                void                            addSelectFields                                     (const vector<string> &selectFields);
                void                            addSelectFieldForObjectIdClassId                    (const string &selectField);
                void                            addSelectFieldForObjectIdInstanceId                 (const string &selectField);
                void                            addSelectFieldForObjectIdWithSuffix                 (const string &selectField, string objectIdSuffix);
                void                            addSelectFieldForObjectId                           (const string &selectField);
                bool                            isSelectFieldAlreadyAdded                           (const string &selectField) const;

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTSYNCHRONOUSINNERQUERYCONTEXT_H 
