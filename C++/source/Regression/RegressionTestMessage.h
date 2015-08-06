/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONTESTMESSAGE_H
#define REGRESSIONTESTMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class RegressionTestMessage : public PrismMessage
{
    private :
        RegressionTestMessage (WaveServiceId serviceCode);

    protected :
    public :
                      RegressionTestMessage ();
                     ~RegressionTestMessage ();
        virtual void  setupAttributesForSerialization ();

    // Now the data members

    private :
    protected :
    public :

    friend class RegressionTestObjectManager;
};

}

#endif // REGRESSIONTESTMESSAGE_H
