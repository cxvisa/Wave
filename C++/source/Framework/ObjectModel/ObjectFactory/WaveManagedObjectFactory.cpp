/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/ObjectFactory/WaveManagedObjectFactory.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
namespace WaveNs
{

WaveManagedObject *WaveManagedObjectFactory::getWaveManagedObjectInstance (const WaveServiceId &waveServiceId, const  string &className)
{
    WaveObjectManager *pWaveObjectManager = getWaveObjectManagerForManagedObject (waveServiceId, className);
    WaveManagedObject *pWaveManagedObject = NULL;

    if (NULL != pWaveObjectManager)
    {
        pWaveManagedObject = pWaveObjectManager->createManagedObjectInstanceWrapper (className);
    }

    if (NULL == pWaveManagedObject)
    {
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Could not create Managed Object instance for  Service : " + FrameworkToolKit::getServiceNameById (waveServiceId) + ", Class Name = " + className + ".");
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Have you implemented the createManagedObjectInstance on the object manager yet???.");
        waveAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

WaveObjectManager *WaveManagedObjectFactory::getWaveObjectManagerForManagedObject (const WaveServiceId &waveServiceId, const  string &className)
{
    WaveThread        *pWaveThread        = NULL;
    WaveObjectManager *pWaveObjectManager = NULL;

    pWaveThread = WaveThread::getWaveThreadForServiceId (waveServiceId);

    if (NULL != pWaveThread)
    {
        pWaveObjectManager = pWaveThread->getWaveObjectManagerForManagedClass (className);
    }

    return (pWaveObjectManager);
}

}
