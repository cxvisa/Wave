/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmAggregation.h"

namespace WaveNs
{

OrmAggregation::OrmAggregation (const string &name, const string &relatedTo, const OrmRelationType &relationType)
    : OrmAssociation (name, relatedTo, relationType)
{
}

OrmAggregation::~OrmAggregation ()
{
}

OrmRelationUmlType OrmAggregation::getRelationUmlType () const
{
    return (ORM_RELATION_UML_TYPE_AGGREGATION);
}

}
