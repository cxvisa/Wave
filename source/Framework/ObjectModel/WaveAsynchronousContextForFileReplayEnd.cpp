/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForFileReplayEnd.h"

namespace WaveNs
{

WaveAsynchronousContextForFileReplayEnd::WaveAsynchronousContextForFileReplayEnd (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext)
{
}

WaveAsynchronousContextForFileReplayEnd::~WaveAsynchronousContextForFileReplayEnd ()
{
}

}
