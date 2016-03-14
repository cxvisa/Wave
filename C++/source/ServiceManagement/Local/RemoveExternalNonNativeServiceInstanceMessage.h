/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REMOVEEXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
#define REMOVEEXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class RemoveExternalNonNativeServiceInstanceMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                 RemoveExternalNonNativeServiceInstanceMessage ();
                 RemoveExternalNonNativeServiceInstanceMessage (const string &applicationName, const string &applicationInstanceName);
                 RemoveExternalNonNativeServiceInstanceMessage (const string &applicationName, const vector<string> &applicationInstanceNames);
        virtual ~RemoveExternalNonNativeServiceInstanceMessage ();

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

#endif // REMOVEEXTERNALNONNATIVESERVICEINSTANCEMESSAGE_H
