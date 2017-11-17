/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleCore/Isle.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "IsleObjectModel/IsleLocalManagedObject.h"
#include "NetworkModel/Local/NetworkModelLocalObjectManager.h"
#include "NetworkModel/Global/NetworkModelObjectManager.h"
#include "Framework/Core/Wave.h"
#include "NetworkMapper/Local/NetworkMapperLocalObjectManager.h"
#include "NetworkMapper/Global/NetworkMapperObjectManager.h"
#include "NetworkModel/Global/Test/NetworkModelTestObjectManager.h"

using namespace WaveNs;

namespace IsleNs
{

void Isle::initialize ()
{

    OrmRepository::addMostBaseClass (IsleManagedObject::getClassName      ());
    OrmRepository::addMostBaseClass (IsleLocalManagedObject::getClassName ());

    registerServices ();
}

void Isle::registerServices ()
{
    Wave::registerNativeService (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkModelLocalObjectManager::getInstance));
    Wave::registerNativeService (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkMapperLocalObjectManager::getInstance));

    Wave::registerNativeService (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkModelObjectManager::getInstance));
    Wave::registerNativeService (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkMapperObjectManager::getInstance));

    Wave::registerNativeService (reinterpret_cast<NativeWaveServiceInstantiator> (NetworkModelTestObjectManager::getInstance));
}

}
