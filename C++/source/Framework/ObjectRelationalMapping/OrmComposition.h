/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ORMCOMPOSITION_H
#define ORMCOMPOSITION_H

#include "Framework/ObjectRelationalMapping/OrmAssociation.h"

namespace WaveNs
{

class OrmComposition : public OrmAssociation
{
    private :
    protected :
    public :
                                    OrmComposition     (const string &name, const string &relatedTo, const OrmRelationType &relationType, const bool &canBeEmpty = false);
                                   ~OrmComposition     ();
        virtual OrmRelationUmlType  getRelationUmlType () const;

                bool                getDisableValidations       () const;
                void                setDisableValidations       (bool disableValidations);
        virtual string              getSqlForCreate2            (const string &parentName, const string &scehma) const;
                string              getSqlForDisableValidation  (const string &parentName, const string &schema) const;
                string              getSqlForEnableValidation   (const string &parentName, const string &schema) const;

    // Now the data members

    private :
         bool    m_disableValidations;

    protected :
    public :
};

}

#endif // ORMCOMPOSITION_H
