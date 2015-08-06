/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForConfigReplayEnd.h"

namespace WaveNs
{

WaveAsynchronousContextForConfigReplayEnd::WaveAsynchronousContextForConfigReplayEnd (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext)
{
}

WaveAsynchronousContextForConfigReplayEnd::~WaveAsynchronousContextForConfigReplayEnd ()
{
}

}
