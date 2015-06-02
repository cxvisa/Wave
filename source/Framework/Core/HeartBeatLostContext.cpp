/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/HeartBeatLostContext.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

HeartBeatLostContext::HeartBeatLostContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
{
}

HeartBeatLostContext::~HeartBeatLostContext ()
{
}

void HeartBeatLostContext::addNodeIpAddressAndPort (const string &nodeIpAddress, const UI32 &nodePort)
{
    m_nodeIpAddresses.push_back (nodeIpAddress);
    m_nodePorts.push_back (nodePort);
}

UI32 HeartBeatLostContext::getNumberOfNodes () const
{
    UI32 numberOfNodeIpAddresses = m_nodeIpAddresses.size ();
    UI32 numberOfNodePorts       = m_nodePorts.size ();

    prismAssert (numberOfNodeIpAddresses == numberOfNodePorts, __FILE__, __LINE__);

    return (numberOfNodeIpAddresses);
}

string HeartBeatLostContext::getNodeIpAddressAtIndex (const UI32 &index) const
{
    prismAssert (index < (m_nodeIpAddresses.size ()), __FILE__, __LINE__);

    return (m_nodeIpAddresses[index]);
}

UI32 HeartBeatLostContext::getNodePortAtIndex (const UI32 &index) const
{
    prismAssert (index < (m_nodePorts.size ()), __FILE__, __LINE__);

    return (m_nodePorts[index]);
}

}
