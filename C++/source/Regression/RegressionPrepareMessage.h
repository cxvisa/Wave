/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONPREPAREMESSAGE_H
#define REGRESSIONPREPAREMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class RegressionPrepareMessage : public PrismMessage
{
    private :
    protected :
    public :
                        RegressionPrepareMessage        (PrismServiceId id);
                        RegressionPrepareMessage        ();
                       ~RegressionPrepareMessage        ();
        void            setupAttributesForSerialization ();
        void            addInputString                  (const string &inputString);
        vector<string> &getInputStrings                 ();

    // Now the data members

    private :
        vector<string> m_inputStrings;

    protected :
    public :
};

}

#endif // REGRESSIONPREPAREMESSAGE_H
