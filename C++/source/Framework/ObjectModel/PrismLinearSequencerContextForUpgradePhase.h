/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef PRISMLINEARSEQUENCERCONTEXTFORUPGRADEPHASE_H
#define PRISMLINEARSEQUENCERCONTEXTFORUPGRADEPHASE_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectRelationalMapping/OMSpecificSchemaChangeInfoForUpgrade.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class PrismLinearSequencerContextForUpgradePhase : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                           PrismLinearSequencerContextForUpgradePhase (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual           ~PrismLinearSequencerContextForUpgradePhase ();

/*
        vector<string>     getNewManagedObjects         () const;
        void               setNewManagedObjects         (const vector<string> &newManagedObjects);

        vector<string>     getChangedManagedObjects     () const;
        void               setChangedManagedObjects     (const vector<string> &changedManagedObjects);
*/
        OMSpecificSchemaChangeInfoForUpgrade* getSchemaChangeInfo () const;  
        void                                  setSchemaChangeInfo (OMSpecificSchemaChangeInfoForUpgrade* pSchemaChangeInfo);   
    // Now the data members

    private :
/*
        vector<string>     m_newManagedObjects;
        vector<string>     m_changedManagedObjects;
*/
        OMSpecificSchemaChangeInfoForUpgrade* m_schemaChangeInfo;

    protected :
    public :
};

}

#endif // PRISMLINEARSEQUENCERCONTEXTFORUPGRADEPHASE_H 
