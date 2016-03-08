/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
#define ADDEXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class AddExternalNonNativeServiceInstanceMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                 AddExternalNonNativeServiceInstanceMessage ();
                 AddExternalNonNativeServiceInstanceMessage (const string &applicationName, const string &applicationInstanceName);
                 AddExternalNonNativeServiceInstanceMessage (const string &applicationName, const vector<string> &applicationInstanceNames);
        virtual ~AddExternalNonNativeServiceInstanceMessage ();

        const string         &getApplicationName          () const;
              void            setApplicationName          (const string &applicationName);

        const vector<string> &getApplicationInstanceNames () const;
              void            setApplicationInstanceNames (const vector <string> &applicationNames);

    // Now the Data Members

    private :
        string         m_applicationName;
        vector<string> m_applicationInstanceNames;

    protected :
    public :
};

}

#endif // ADDEXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
