/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef LOCKMANAGEMENTOBJECTMANAGERRELEASELOCKMESSAGE_H
#define LOCKMANAGEMENTOBJECTMANAGERRELEASELOCKMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

using namespace std;

namespace WaveNs
{

class LockManagementObjectManagerReleaseLockMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :                        
                        LockManagementObjectManagerReleaseLockMessage  ();
                        LockManagementObjectManagerReleaseLockMessage  (const string &serviceString);
        virtual        ~LockManagementObjectManagerReleaseLockMessage  ();

        const string&   getServiceString ();

    // Now the data members

    private :
        string m_serviceString;

    protected :
    public :
};

}

#endif // LOCKMANAGEMENTOBJECTMANAGERRELEASELOCKMESSAGE_H
