/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#include "Framework/Zeroize/ZeroizeForFIPSMessage.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"



namespace WaveNs
{
ZeroizeForFIPSMessage::ZeroizeForFIPSMessage ()
    : ManagementInterfaceMessage (FrameworkToolKit::getServiceNameById(PrismFrameworkObjectManager::getPrismServiceId ()),FRAMEWORK_OBJECT_MANAGER_FIPS_ZEROIZE)
{
    setPriority(WAVE_MESSAGE_PRIORITY_HIGH);
}

ZeroizeForFIPSMessage::~ZeroizeForFIPSMessage ()
{
}
}
