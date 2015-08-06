/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONPREPAREMESSAGE_H
#define REGRESSIONPREPAREMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class RegressionPrepareMessage : public WaveMessage
{
    private :
    protected :
    public :
                        RegressionPrepareMessage        (WaveServiceId id);
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
