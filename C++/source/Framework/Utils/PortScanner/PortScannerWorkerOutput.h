/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PORTSCANNERWORKEROUTPUT_H
#define PORTSCANNERWORKEROUTPUT_H

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceWorkerResponseMessage.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class PortScannerWorkerOutput : public MapReduceWorkerResponseMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                              PortScannerWorkerOutput ();
        virtual              ~PortScannerWorkerOutput ();

                vector<UI32>  getAllOpenPorts         () const;
                void          setAllOpenPorts         (const vector<UI32> &allOpenPorts);

                vector<UI32>  getAllClosedPorts       () const;
                void          setAllClosedPorts       (const vector<UI32> &allClosedPorts);

                vector<UI32>  getAllTimedOutPorts     () const;
                void          setAllTimedOutPorts     (const vector<UI32> &allTimedOutPorts);

                vector<UI32>  getAllNotTriedPorts     () const;
                void          setAllNotTriedPorts     (const vector<UI32> &allNotTriedPorts);

        // Now the data members

    private :
        vector<UI32> m_allOpenPorts;
        vector<UI32> m_allClosedPorts;
        vector<UI32> m_allTimedOutPorts;
        vector<UI32> m_allNotTriedPorts;

    protected :
    public :
};

}

#endif // PORTSCANNERWORKEROUTPUT_H

