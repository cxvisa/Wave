/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICEINSTANCECONTEXT_H
#define ADDEXTERNALNONNATIVESERVICEINSTANCECONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"

namespace WaveNs
{

class AddExternalNonNativeServiceInstanceContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 AddExternalNonNativeServiceInstanceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~AddExternalNonNativeServiceInstanceContext ();

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

#endif // ADDEXTERNALNONNATIVESERVICEINSTANCECONTEXT_H
