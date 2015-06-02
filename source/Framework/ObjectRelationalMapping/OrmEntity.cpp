/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmEntity.h"

namespace WaveNs
{

OrmEntity::OrmEntity (const string &name)
	: m_name (name)
{
}

OrmEntity::~OrmEntity ()
{
}

string  OrmEntity::getName () const
{
	return (m_name);
}

}
