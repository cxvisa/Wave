/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForFileReplayEnd.h"

namespace WaveNs
{

WaveAsynchronousContextForFileReplayEnd::WaveAsynchronousContextForFileReplayEnd (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext)
{
}

WaveAsynchronousContextForFileReplayEnd::~WaveAsynchronousContextForFileReplayEnd ()
{
}

}
