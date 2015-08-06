/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONSERVICEMESSAGES_H
#define APPLICATIONSERVICEMESSAGES_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

typedef enum
{
    APPLICATION_SERVICE_GENERIC_MESSAGE = 0
} ApplicationServiceOperationCodes;

typedef enum
{
    APPLICATION_SERVICE_GENERIC_MESSAGE_INPUT_BUFFER1 = 0,
    APPLICATION_SERVICE_GENERIC_MESSAGE_OUTPUT_BUFFER1 = 1
} ApplicationServiceMessageBufgferTags;

class ApplicationServiceMessage : public PrismMessage
{
    private :
    protected :
        void setupAttributesForSerialization ();

    public :
              ApplicationServiceMessage ();
              ApplicationServiceMessage (WaveServiceId prismServiceId);
             ~ApplicationServiceMessage ();

        void *getInputBuffer1           (UI32 &bufferLength);
        void *getOutputBuffer1          (UI32 &bufferLength);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // APPLICATIONSERVICEMESSAGES_H
