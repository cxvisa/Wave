/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CREATEEXTERNALNONNATIVESERVICEMESSAGEMESSAGE_H
#define CREATEEXTERNALNONNATIVESERVICEMESSAGEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class AddExternalNonNativeServiceMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                 AddExternalNonNativeServiceMessage ();
        virtual ~AddExternalNonNativeServiceMessage ();

    // Now the Data Members

    private :
        string m_name;

    protected :
    public :
};

}

#endif // CREATEEXTERNALNONNATIVESERVICEMESSAGEMESSAGE_H
