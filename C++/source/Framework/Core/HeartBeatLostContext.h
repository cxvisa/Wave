/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HEARTBEATLOSTCONTEXT_H
#define HEARTBEATLOSTCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include <vector>
#include <string>

namespace WaveNs
{

class HeartBeatLostContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                      HeartBeatLostContext    (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual      ~HeartBeatLostContext    ();

                void   addNodeIpAddressAndPort (const string &nodeIpAddress, const UI32 &port);
                UI32   getNumberOfNodes        () const;
                string getNodeIpAddressAtIndex (const UI32 &index) const;
                UI32   getNodePortAtIndex      (const UI32 &index) const;

    // Now the data members

    private :
        vector<string> m_nodeIpAddresses;
        vector<UI32>   m_nodePorts;

    protected :
    public :
};

}

#endif // HEARTBEATLOSTCONTEXT_H
