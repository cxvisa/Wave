/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ORMENTITY_H
#define ORMENTITY_H

#include <string>

using namespace std;

namespace WaveNs
{

class OrmEntity
{
    private :
    protected :
    public :
                        OrmEntity       (const string &name);
        virtual        ~OrmEntity       ();
		string  getName         () const;
        virtual string  getSqlForCreate (const string &schema) const = 0;
	virtual string  getTypeForUpgradeMO () const = 0;

    // Now the data members

    private :
	        string          m_name;
    protected :
    public :
};

}

#endif // ORMENTITY_H
