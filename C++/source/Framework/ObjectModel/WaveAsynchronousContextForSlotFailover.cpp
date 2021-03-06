/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForSlotFailover.h"

namespace WaveNs
{

WaveAsynchronousContextForSlotFailover::WaveAsynchronousContextForSlotFailover (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_slotNumber (0)
{
}

WaveAsynchronousContextForSlotFailover::~WaveAsynchronousContextForSlotFailover ()
{
}

UI32 WaveAsynchronousContextForSlotFailover::getSlotNumber () const
{
    return (m_slotNumber);
}

void WaveAsynchronousContextForSlotFailover::setSlotNumber (const UI32 slotNumber)
{
    m_slotNumber = slotNumber;
}

}
