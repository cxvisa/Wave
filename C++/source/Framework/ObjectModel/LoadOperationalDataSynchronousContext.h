/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LOADOPERATIONALDATASYNCHRONOUSCONTEXT_H
#define LOADOPERATIONALDATASYNCHRONOUSCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class LoadOperationalDataSynchronousContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                           LoadOperationalDataSynchronousContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                           LoadOperationalDataSynchronousContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                          ~LoadOperationalDataSynchronousContext ();

        ObjectId           getWaveManagedObjectId                () const;
        void               setWaveManagedObjectId                (const ObjectId &waveManagedObjectId);

        vector<string>     getOperationalDataFields              () const;
        void               setOperationalDataFields              (const vector<string> &operationalDataFields);

        WaveManagedObject *getPWaveManagedObject                 () const;
        void               setPWaveManagedObject                 (WaveManagedObject * const pWaveMAnagedObject);

    // Now the data members

    private :
        ObjectId           m_waveManagedObjctId;
        vector<string>     m_operationalDataFields;
        WaveManagedObject *m_pWaveManagedObject;

    protected :
    public :
};

}

#endif // LOADOPERATIONALDATASYNCHRONOUSCONTEXT_H
