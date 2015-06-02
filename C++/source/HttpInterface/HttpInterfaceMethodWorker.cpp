/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/HttpInterfaceMethodWorker.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"

namespace WaveNs
{

HttpInterfaceMethodWorker::HttpInterfaceMethodWorker (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const WaveHttpInterfaceMethod& waveHttpInterfaceMethod)
    : WaveWorker (pHttpInterfaceReceiverObjectManager),
      m_waveHttpInterfaceMethod (waveHttpInterfaceMethod)
{
    pHttpInterfaceReceiverObjectManager->addHttpInterfaceMethodWorker (waveHttpInterfaceMethod, this);
}

HttpInterfaceMethodWorker::~HttpInterfaceMethodWorker()
{
}

WaveHttpInterfaceMethod HttpInterfaceMethodWorker::getWaveHttpInterfaceMethod () const
{
    return (m_waveHttpInterfaceMethod);
}

}
