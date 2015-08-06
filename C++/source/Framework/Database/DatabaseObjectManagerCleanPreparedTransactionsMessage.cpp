/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerCleanPreparedTransactionsMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManager.h"

namespace WaveNs
{

DatabaseObjectManagerCleanPreparedTransactionsMessage::DatabaseObjectManagerCleanPreparedTransactionsMessage ()
    : PrismMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_CLEAN_PREPARED_TRANSACTIONS)
{
}

DatabaseObjectManagerCleanPreparedTransactionsMessage::~DatabaseObjectManagerCleanPreparedTransactionsMessage ()
{
}

}
