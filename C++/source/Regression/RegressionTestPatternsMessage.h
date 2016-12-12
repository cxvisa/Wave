/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONTESTPATTERNSMESSAGE_H
#define REGRESSIONTESTPATTERNSMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class RegressionTestPatternsMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

                     RegressionTestPatternsMessage   (WaveServiceId serviceCode);

    protected :
    public :
                 RegressionTestPatternsMessage ();
        virtual ~RegressionTestPatternsMessage ();

        const string &getTestPatterns () const;
              void    setTestPatterns (const string &testPatterns);

    // Now the data members

    private :
        string m_testPatterns;

    protected :
    public :

    friend class RegressionTestObjectManager;
};

}

#endif // REGRESSIONTESTPATTERNSMESSAGE_H
