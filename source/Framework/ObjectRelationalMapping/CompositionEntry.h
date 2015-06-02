/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMPOSITIONENTRY_H
#define COMPOSITIONENTRY_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <string>

using namespace std;

namespace WaveNs
{

class CompositionEntry
{
    private :
    protected :
    public :
                                CompositionEntry            (const string &parentClassName, const string &childCalssName, const string &compositionName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        virtual                ~CompositionEntry            ();

                void            getSqlForInsertIntoParent   (string &sql);
                void            getSqlForDeleteFromParent   (string &sql);

        const   string         &getParentClassName          () const;
        const   string         &getChildClassName           () const;
        const   string         &getCompositionName          () const;
                string          getCompositionTableName     () const;

        // Now the data members

    private :
        string   m_parentClassName;
        string   m_childClassName;
        string   m_compositionName;
        ObjectId m_parentObjectId;
        ObjectId m_childObjectId;
    protected :
    public :
};

class AssociationEntry : public CompositionEntry
{
    public :
               AssociationEntry        (const string &parentClassName, const string &childCalssName, const string &associationName, const ObjectId &parentObjectId, const ObjectId &childObjectId);

        string getAssociationTableName () const;
};

}

#endif // COMPOSITIONENTRY_H
