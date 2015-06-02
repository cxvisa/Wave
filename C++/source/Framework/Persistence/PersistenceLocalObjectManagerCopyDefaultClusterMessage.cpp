/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Description : This is a dummy message created to do copy default to   *
 *                 startup in a cluster.                                   * 
 *   Author : Anil ChannaveeraSetty                                        *
 *   Date : Oct/05/2010                                                    * 
 ***************************************************************************/


#include "Framework/Persistence/PersistenceLocalObjectManagerCopyDefaultClusterMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerCopyDefaultClusterMessage::PersistenceLocalObjectManagerCopyDefaultClusterMessage()
: PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (),PERSISTENCE_COPY_DEFAULT_CLUSTER) 
{ }

PersistenceLocalObjectManagerCopyDefaultClusterMessage::~PersistenceLocalObjectManagerCopyDefaultClusterMessage()
{ }

}

