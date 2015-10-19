/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVENATIVETEST1SERVICEMESSAGES_H
#define WAVENATIVETEST1SERVICEMESSAGES_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

typedef enum
{
    WAVE_NATIVE_TEST1_SERVICE_MESSAGE1
} WaveNativeTest1ServiceMessageOpCodes;

class WaveNativeTest1ServiceMessage1 : public WaveMessage
{
    private :
    protected :
    public :
       WaveNativeTest1ServiceMessage1 ();
      ~WaveNativeTest1ServiceMessage1 ();

      // Now the data members

      private :
      protected :
      public :
};

}

#endif // WAVENATIVETEST1SERVICEMESSAGES_H
