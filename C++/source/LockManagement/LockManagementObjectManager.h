/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveObjectManager.h"
#include "LockManagement/LockManagedObject.h"
#include "LockManagement/LockManagementObjectManagerAcquireLockMessage.h"
#include "LockManagement/LockManagementObjectManagerReleaseLockMessage.h"
#include "LockManagement/LockManagementMessagingContext.h"

#ifndef LOCKMANAGEMENTOBJECTMANAGER_H
#define LOCKMANAGEMENTOBJECTMANAGER_H

namespace WaveNs
{

class LockManagementObjectManager : public WaveObjectManager
{
    private :
                              LockManagementObjectManager ();

                virtual       WaveMessage             *createMessageInstance    (const UI32 &operationCode);
                virtual       WaveManagedObject        *createManagedObjectInstance (const string &managedClassName);


                void          failover                    (FailoverAsynchronousContext *pFailoverAsynchronousContext);

    protected :
    public :
        virtual                                 ~LockManagementObjectManager        ();
        static  string                           getClassName                       ();
        static  LockManagementObjectManager     *getInstance                        ();
        static  WaveServiceId                   getWaveServiceId                  ();
        void    boot                             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void    executeAcquireLockMessageHandler (LockManagementObjectManagerAcquireLockMessage *pLockManagementObjectManagerAcquireLockMessage);
        void    executeReleaseLockMessageHandler (LockManagementObjectManagerReleaseLockMessage *pLockManagementObjectManagerReleaseLockMessage);

        ResourceId validateAcquireLockStep                      (LockManagementMessagingContext *pLockManagementMessagingContext);
        ResourceId queryLockManagedObjectFromServiceStringStep  (LockManagementMessagingContext *pLockManagementMessagingContext);
        ResourceId createLockManagedObjectInDataBaseStep        (LockManagementMessagingContext *pLockManagementMessagingContext);
        ResourceId deleteLockManagedObjectFromDataBaseStep      (LockManagementMessagingContext *pLockManagementMessagingContext);
        ResourceId setServiceStringFromAcquireMessageStep       (LockManagementMessagingContext *pLockManagementMessagingContext);
        ResourceId setServiceStringFromReleaseMessageStep       (LockManagementMessagingContext *pLockManagementMessagingContext);
        
    // Now the data members

    private :
    protected :
    public :
};

}

#endif // LOCKMANAGEMENTOBJECTMANAGER_H
