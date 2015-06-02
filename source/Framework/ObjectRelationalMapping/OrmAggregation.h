/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ORMAGGREGATION_H
#define ORMAGGREGATION_H

#include "Framework/ObjectRelationalMapping/OrmAssociation.h"

namespace WaveNs
{

class OrmAggregation : public OrmAssociation
{
    private :
    protected :
    public :
                                    OrmAggregation     (const string &name, const string &relatedTo, const OrmRelationType &relationType);
                                   ~OrmAggregation     ();
        virtual OrmRelationUmlType  getRelationUmlType () const;

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // ORMAGGREGATION_H
