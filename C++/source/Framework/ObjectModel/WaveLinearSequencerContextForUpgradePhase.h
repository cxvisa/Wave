/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVELINEARSEQUENCERCONTEXTFORUPGRADEPHASE_H
#define WAVELINEARSEQUENCERCONTEXTFORUPGRADEPHASE_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectRelationalMapping/OMSpecificSchemaChangeInfoForUpgrade.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveLinearSequencerContextForUpgradePhase : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                           WaveLinearSequencerContextForUpgradePhase (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual           ~WaveLinearSequencerContextForUpgradePhase ();

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

#endif // WAVELINEARSEQUENCERCONTEXTFORUPGRADEPHASE_H 
