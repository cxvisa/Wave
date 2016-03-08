/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICEMESSAGEMESSAGE_H
#define ADDEXTERNALNONNATIVESERVICEMESSAGEMESSAGE_H

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
                 AddExternalNonNativeServiceMessage (const string &applicationName);
                 AddExternalNonNativeServiceMessage (const vector<string> &applicationNames);
        virtual ~AddExternalNonNativeServiceMessage ();

        const vector<string> &getApplicationNames () const;
              void            setApplicationNames (const vector <string> &applicationNames);

    // Now the Data Members

    private :
        vector<string> m_applicationNames;

    protected :
    public :
};

}

#endif // ADDEXTERNALNONNATIVESERVICEMESSAGEMESSAGE_H
