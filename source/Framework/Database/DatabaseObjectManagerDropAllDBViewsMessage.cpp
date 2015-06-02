/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Ghosh                                                 *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerDropAllDBViewsMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessage.h"

namespace WaveNs
{

DatabaseObjectManagerDropAllDBViewsMessage::DatabaseObjectManagerDropAllDBViewsMessage ()
    : PrismMessage                               (DatabaseObjectManagerExecuteQueryMessage::getDatabaseObjectManagerServiceId (), DATABASE_OBJECT_MANAGER_DROP_DB_VIEWS)
{
}

DatabaseObjectManagerDropAllDBViewsMessage::~DatabaseObjectManagerDropAllDBViewsMessage ()
{
}

}
