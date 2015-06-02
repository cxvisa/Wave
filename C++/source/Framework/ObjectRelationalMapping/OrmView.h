/***************************************************************************
 *   Copyright (C) 2012-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef ORMVIEW_H
#define ORMVIEW_H

#include "Framework/Attributes/Attribute.h"
#include "Framework/ObjectRelationalMapping/OrmTable.h"

#include <vector>
#include <string>
#include <set>

using namespace std;

namespace WaveNs
{

class OrmView : virtual public OrmTable
{
    private :

    protected :
    public :
                                    OrmView                               (const string &viewName);
                                   ~OrmView                               ();

        string                      getName                                () const;
        string                      getSqlForCreateView                    () const;
        void                        setSqlForCreateView                    (string &viewDefinition);

    // Now the data members


    private :
        string                      m_name;
        string                      m_viewDefinition;

    protected :
    public :
};

}

#endif // ORMVIEW_H
