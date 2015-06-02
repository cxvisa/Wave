/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMNATIVETEST1SERVICEMESSAGES_H
#define PRISMNATIVETEST1SERVICEMESSAGES_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

typedef enum
{
    WAVE_NATIVE_TEST1_SERVICE_MESSAGE1
} PrismNativeTest1ServiceMessageOpCodes;

class PrismNativeTest1ServiceMessage1 : public PrismMessage
{
    private :
    protected :
    public :
       PrismNativeTest1ServiceMessage1 ();
      ~PrismNativeTest1ServiceMessage1 ();

      // Now the data members

      private :
      protected :
      public :
};

}

#endif // PRISMNATIVETEST1SERVICEMESSAGES_H
