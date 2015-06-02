/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ATTRIBUTEMANAGEDOBJECTONETOONERELATIONBASE_H
#define ATTRIBUTEMANAGEDOBJECTONETOONERELATIONBASE_H


#include "Framework/Attributes/Attribute.h"
#if 0
#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "WaveResourceIdEnums.h"
#endif

namespace WaveNs
{

class AttributeManagedObjectOneToOneRelationBase : public Attribute 
{
    private :
    protected :
                                                                       AttributeManagedObjectOneToOneRelationBase           (AttributeType &attributeType, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational, const bool &canBeEmpty = false);
                                                                       AttributeManagedObjectOneToOneRelationBase           (const AttributeManagedObjectOneToOneRelationBase &attribute);
                AttributeManagedObjectOneToOneRelationBase            &operator =                                           (const AttributeManagedObjectOneToOneRelationBase &attribute);

    public :
        virtual void                                                   setCanBeEmpty                                        (const bool canBeEmpty);
        virtual bool                                                   getCanBeEmpty                                        () const;

        virtual void                                                   setRelatedObjectId                                   (const ObjectId &relatedObjectId);
        virtual ObjectId                                               getRelatedObjectId                                   () const;
        virtual void                                                   loadRelatedObjectIdFromPostgresQueryResult           (PGresult *pResult, const UI32 &row);
                void                                                   popOneToOneCompositionsFromResult                    (map<ObjectId, WaveManagedObject*> &oidTopManagedObjectMap);
        virtual void                                                   storeComposedObjectPointer                           (WaveManagedObject *pWaveChildManagedObject);

    // Now the data members

    private :
        bool          m_canBeEmpty;
        ObjectId      m_relatedObjectId;
};

}

#endif // ATTRIBUTEMANAGEDOBJECTVECTORCOMPOSITIONTEMPLATEBASE_H

