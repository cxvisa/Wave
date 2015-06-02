/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mithun B S
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXTFORUPDATE_H
#define WAVEMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXTFORUPDATE_H

#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class WaveManagedObjectSynchronousQueryContextForUpdate: public WaveManagedObjectSynchronousQueryContext
{
    private :
    protected :
    public :
                                                WaveManagedObjectSynchronousQueryContextForUpdate   (const string &classToQueryFor);
        virtual                                ~WaveManagedObjectSynchronousQueryContextForUpdate   ();

                void                            getSqlForUpdate                                     (string &sql);
                WaveManagedObject *             getWaveManagedObjectToAddUpdateAttributes           ();

                void                            setAttributeObjectIdVectorAssociation               (AttributeObjectIdVectorAssociation *pAttributeObjectIdVectorAssociation);
                void                            addOrderField                                       (const string &orderField, const bool &ascending = true);

                void                            addNTupleFormatForOrderField                        (const string &keyName, const char &tupleSeparator, const UI32 &numberOfTuples);

                void                            addSelectField                                      (const string &selectField);
                void                            addSelectFieldForObjectId                           (const string &selectField);
                void                            addSelectFields                                     (const vector<string> &selectFields);
                vector<string>                  getSelectFields                                     () const;
                vector<string>                  getSelectFieldsInManagedObject                      () const;
                bool                            getLoadOneToManyRelationships                       () const;
                void                            setLoadOneToManyRelationships                       (const bool &loadOneToManyRelationships);
                bool                            getLoadCompositions                                 () const;
                void                            setLoadCompositions                                 (const bool loadCompositions);
                void                            addLimitForQueryResults                             (UI32 limitForQueryResults);

                UI32                            getPageSizeForQueryResults                          ();
                void                            setPageSizeForQueryResults                          (UI32 limitForQueryResults);
                void                            setPageQueryContext                                 (WaveObjectManager* callingOm);
                bool                            isPageQueryContextSet                               ();
                string                          getPageQuerySql                                     ();
                void                            moveOffsetOnSuccessfulQuery                         ();
                string                          getSqlWithPagingEnabled                             (WaveObjectManager* callingOm);


    // Now the data members
    private :
                WaveManagedObject *             m_WaveManagedObjectToAddUpdateAttributes;
    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTSYNCHRONOUSQUERYCONTEXTFORUPDATE_H
