/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ORMCOLUMN_H
#define ORMCOLUMN_H

#include "Framework/ObjectRelationalMapping/OrmEntity.h"

#include <string>

using namespace std;

namespace WaveNs
{

class OrmColumn : public OrmEntity
{
    private :
    protected :
    public :
                OrmColumn      (const string &name, const string &sqlType, const string &typeForUpgradeMO, const bool &isPrimary = false);
               ~OrmColumn      ();

        	string  getSqlType     () const;
	virtual string  getTypeForUpgradeMO () const;

        	string getSqlForCreate (const string &schema) const;

        	bool   getIsPrimary    () const;
        	void   setIsPrimary    (const bool &isPrimary);

    // Now the data members

    private :
        string m_sqlType;
        string m_typeForUpgradeMO; // This value indicates the Wave Attribute type of the OrmColumn
        bool   m_isPrimary;

    protected :
    public :
};

}

#endif // ORMCOLUMN_H
