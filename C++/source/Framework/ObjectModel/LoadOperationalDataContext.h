/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LOADOPERATIONALDATACONTEXT_H
#define LOADOPERATIONALDATACONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class LoadOperationalDataContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                           LoadOperationalDataContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                           LoadOperationalDataContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                          ~LoadOperationalDataContext ();

        ObjectId           getWaveManagedObjectId     () const;
        void               setWaveManagedObjectId     (const ObjectId &waveManagedObjectId);

        vector<string>     getOperationalDataFields   () const;
        void               setOperationalDataFields   (const vector<string> &operationalDataFields);

        WaveManagedObject *getPWaveManagedObject      () const;
        void               setPWaveManagedObject      (WaveManagedObject * const pWaveManagedObject);
        
		WaveManagedObject *getPOwnerWaveManagedObject () const;
        void               setPOwnerWaveManagedObject (WaveManagedObject * const pOwnerWaveManagedObject);

    // Now the data members

    private :
        ObjectId           m_waveManagedObjctId;
        vector<string>     m_operationalDataFields;
        WaveManagedObject *m_pWaveManagedObject;
        WaveManagedObject *m_pOwnerWaveManagedObject;

    protected :
    public :
};

}

#endif // LOADOPERATIONALDATACONTEXT_H
