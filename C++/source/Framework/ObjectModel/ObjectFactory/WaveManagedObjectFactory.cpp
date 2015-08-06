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

WaveManagedObject *WaveManagedObjectFactory::getWaveManagedObjectInstance (const WaveServiceId &prismServiceId, const  string &className)
{
    WaveObjectManager *pWaveObjectManager = getWaveObjectManagerForManagedObject (prismServiceId, className);
    WaveManagedObject *pWaveManagedObject = NULL;

    if (NULL != pWaveObjectManager)
    {
        pWaveManagedObject = pWaveObjectManager->createManagedObjectInstanceWrapper (className);
    }

    if (NULL == pWaveManagedObject)
    {
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Could not create Managed Object instance for  Service : " + FrameworkToolKit::getServiceNameById (prismServiceId) + ", Class Name = " + className + ".");
        trace (TRACE_LEVEL_FATAL, "WaveMessageFactory::getMessageInstance : Have you implemented the createManagedObjectInstance on the object manager yet???.");
        prismAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

WaveObjectManager *WaveManagedObjectFactory::getWaveObjectManagerForManagedObject (const WaveServiceId &prismServiceId, const  string &className)
{
    WaveThread        *pWaveThread        = NULL;
    WaveObjectManager *pWaveObjectManager = NULL;

    pWaveThread = WaveThread::getWaveThreadForServiceId (prismServiceId);

    if (NULL != pWaveThread)
    {
        pWaveObjectManager = pWaveThread->getWaveObjectManagerForManagedClass (className);
    }

    return (pWaveObjectManager);
}

}
