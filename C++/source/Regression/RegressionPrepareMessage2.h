/***************************************************************************
 *   Copyright (C) 2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef REGRESSIONPREPAREMESSAGE2_H
#define REGRESSIONPREPAREMESSAGE2_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class RegressionPrepareMessage2 : public WaveMessage
{
    private :
    protected :
    public :
                        RegressionPrepareMessage2       (WaveServiceId id);
                        RegressionPrepareMessage2       ();
                       ~RegressionPrepareMessage2       ();
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

#endif // REGRESSIONPREPAREMESSAGE2_H
