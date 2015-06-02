/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mithun B S                                                   *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmToolKit.h"

namespace WaveNs
{

ResourceId OrmToolKit::getDatabaseSchema (DatabaseSchema &databaseSchema)
{
    return (DatabaseSchema::getDatabaseSchema (databaseSchema));
}

}
