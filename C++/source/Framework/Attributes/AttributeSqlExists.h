/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef ATTRIBUTESQLEXISTS_H
#define ATTRIBUTESQLEXISTS_H

#include "Framework/Attributes/Attribute.h"
#include "WaveResourceIdEnums.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousInnerQueryContext.h"

namespace WaveNs
{

class AttributeSqlExists : public Attribute
{
    private :
        virtual bool                        validate                                () const;
        virtual bool                        isConditionOperatorSupported            (AttributeConditionOperator attributeConditionOperator);

    protected :
    public :
                                            // This Attribute can be added in Where condition of Outer query context only if the outer context is Synchronous
                                            AttributeSqlExists                      (WaveManagedObjectSynchronousInnerQueryContext *pWaveManagedObjectSynchronousInnerQueryContext);

        virtual                            ~AttributeSqlExists                      ();
                AttributeSqlExists         &operator =                              (const AttributeSqlExists &attribute);
        virtual string                      getSqlType                              ();
        virtual void                        setupOrm                                (OrmTable *pOrmTable);
        virtual string                      getSqlForCreate                         ();
        virtual void                        getSqlForInsert                         (string &sqlForPreValues, string &sqlForInsert, string &sqlForInsert2, bool isFirst = false);
        virtual void                        getSqlForUpdate                         (string &sqlForUpdate, string &sqlForUpdate2, bool isFirst = false);
        virtual void                        getSqlForSelect                         (string &sqlForSelect, AttributeConditionOperator attributeConditionOperator = WAVE_ATTRIBUTE_CONDITION_OPERATOR_EQUAL);
        virtual void                        toString                                (string &valueString);
        virtual void                        fromString                              (const string &valueString);
        virtual void                       *getPData                                ();
        virtual void                        setValue                                (const void *pData);
        virtual Attribute                  *clone                                   ();

        virtual void                        loadFromPostgresQueryResult             (PGresult *pResult, const UI32 &row, const string &schema, WaveObjectManager *pWaveObjectManager = NULL);
        virtual void                        loadFromPostgresAuxilliaryQueryResult   (map<string, PGresult *> &auxilliaryResultsMap, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pWaveObjectManager = NULL);

        virtual void                        updateOrmRelations                      (const WavePersistableObject *pWavePersistableObject);
        virtual WaveManagedObject          *getComposedManagedObject                (const ObjectId &childObjectId);
        virtual bool                        isDeletableForOperation                 (const WaveManagedObjectOperation &operation);
        virtual void                        updateKeyString                         (const WavePersistableObject *pWavePersistableObject);
        virtual void                        getRestRowData                          (string &restRowData);
        static  map<string, string>         getSupportedConversions                 ();
        virtual void                        setDefaultValue                         ();
        virtual void                        getCValue                               (WaveCValue *pCValue);
                bool                        isCurrentValueSameAsDefault             () const;
    // Now the data members

    private :
                WaveManagedObjectSynchronousInnerQueryContext *m_pWaveManagedObjectSynchronousInnerQueryContext;

    protected :
    public :
};

}

#endif // ATTRIBUTESQLEXISTS_H

