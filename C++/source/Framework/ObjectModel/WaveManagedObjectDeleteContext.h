/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTDELETECONTEXT_H
#define WAVEMANAGEDOBJECTDELETECONTEXT_H

#include "ObjectId.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveManagedObjectUpdateContext.h"

namespace WaveNs
{

class WaveManagedObject;

class WaveManagedObjectDeleteContext : public WaveManagedObjectUpdateContext 
{
    private :
    protected :
    public :
                    WaveManagedObjectDeleteContext              (WaveMessage* pWaveMessage, WaveElement* pWaveElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps);
        virtual    ~WaveManagedObjectDeleteContext              ();

        bool        isNeedToDeleteManagedObject                 () const;
        void        setNeedToDeleteManagedObject                (const bool &needToDeleteManagedObject);

   // Now the data members
    private :
        string      m_managedObjectClassName;
        bool        m_needToDeleteManagedObject;

    protected :
    public :
};

}
#endif // WAVEMANAGEDOBJECTDELETECONTEXT_H

