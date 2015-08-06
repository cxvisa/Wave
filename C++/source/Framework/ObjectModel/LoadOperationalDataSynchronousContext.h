/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LOADOPERATIONALDATASYNCHRONOUSCONTEXT_H
#define LOADOPERATIONALDATASYNCHRONOUSCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class LoadOperationalDataSynchronousContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                           LoadOperationalDataSynchronousContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                           LoadOperationalDataSynchronousContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
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
