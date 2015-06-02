/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef LOCKMANAGEMENTOBJECTMANAGERACQUIRELOCKMESSAGE_H
#define LOCKMANAGEMENTOBJECTMANAGERACQUIRELOCKMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

using namespace std;

namespace WaveNs
{

class LockManagementObjectManagerAcquireLockMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :                        
                        LockManagementObjectManagerAcquireLockMessage  ();
                        LockManagementObjectManagerAcquireLockMessage  (const string &serviceString);
        virtual        ~LockManagementObjectManagerAcquireLockMessage  ();

        const string&   getServiceString ();

                
    // Now the data members

    private :
        string m_serviceString;
        

    protected :
    public :
};

}

#endif // LOCKMANAGEMENTOBJECTMANAGERACQUIRELOCKMESSAGE_H
