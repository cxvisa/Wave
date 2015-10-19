/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/ReservedWaveLocalObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

ReservedWaveLocalObjectManager::ReservedWaveLocalObjectManager ()
    : WaveLocalObjectManager (getWaveServiceName ())
{
}

ReservedWaveLocalObjectManager::~ReservedWaveLocalObjectManager ()
{
}

ReservedWaveLocalObjectManager *ReservedWaveLocalObjectManager::getInstance ()
{
    static ReservedWaveLocalObjectManager *pReservedWaveLocalObjectManager = new ReservedWaveLocalObjectManager ();

    WaveNs::waveAssert (NULL != pReservedWaveLocalObjectManager, __FILE__, __LINE__);

    return (pReservedWaveLocalObjectManager);
}

WaveServiceId ReservedWaveLocalObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string ReservedWaveLocalObjectManager::getWaveServiceName ()
{
    return ("_Reserved For Wave Internal Purposes_");
}

}

