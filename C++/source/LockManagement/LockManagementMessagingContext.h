/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef LOCKMANAGEMENTMESSAGINGCONTEXT_h
#define LOCKMANAGEMENTMESSAGINGCONTEXT_h

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "LockManagement/LockManagedObject.h"

namespace WaveNs
{

class LockManagementMessagingContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                    LockManagementMessagingContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                   ~LockManagementMessagingContext ();
       LocationId                   getLocationId () const;
       const string&                getServiceString () const;
       LockManagedObject*           getPLockManagedObject () const;
       void                         setLocationId (const LocationId locationId);
       void                         setServiceString (const string &serviceString);
       void                         setPLockManagedObject (LockManagedObject* lockManagedObject);


    // Now the data members

    private :
        LocationId                  m_locationId;
        string                      m_serviceString;
        LockManagedObject*          m_lockManagedObject;

    protected :
    public :
};

}

#endif // LOCKMANAGEMENTMESSAGINGCONTEXT_h

