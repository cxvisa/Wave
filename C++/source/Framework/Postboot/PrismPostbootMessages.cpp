/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/Postboot/PrismPostbootMessages.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

ExecutePostbootPassTableMessage::ExecutePostbootPassTableMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId(), FRAMEWORK_OBJECT_MANAGER_EXECUTE_POSTBOOT_PASSES)
{
}

ExecutePostbootPassTableMessage::~ExecutePostbootPassTableMessage ()
{
}

}
