/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REMOVEEXTERNALNONNATIVESERVICEINSTANCECONTEXT_H
#define REMOVEEXTERNALNONNATIVESERVICEINSTANCECONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"

namespace WaveNs
{

class RemoveExternalNonNativeServiceInstanceContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 RemoveExternalNonNativeServiceInstanceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~RemoveExternalNonNativeServiceInstanceContext ();

        const string         &getApplicationName          () const;
              void            setApplicationName          (const string &applicationName);

        const vector<string> &getApplicationInstanceNames () const;
              void            setApplicationInstanceNames (const vector <string> &applicationNames);

        const ObjectId       &getApplicationObjectId      () const;
              void            setApplicationObjectId      (const ObjectId &applicationObjectId);

    // Now the Data Members

    private :
        string         m_applicationName;
        vector<string> m_applicationInstanceNames;
        ObjectId       m_applicationObjectId;

    protected :
    public :
};

}

#endif // REMOVEEXTERNALNONNATIVESERVICEINSTANCECONTEXT_H
