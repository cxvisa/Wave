/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORUPGRADEPHASE_H
#define WAVEASYNCHRONOUSCONTEXTFORUPGRADEPHASE_H

#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectRelationalMapping/OMSpecificSchemaChangeInfoForUpgrade.h"

namespace WaveNs
{

class FirmwareVersion
{
    private :
    protected :
    public :
                        FirmwareVersion ();
                        FirmwareVersion (const string &majorNumber, const string &minorNumber, const string &patchString, const string &description);
                       ~FirmwareVersion ();

        bool            isSameVersion   (const string &versionString);
                       
    private :
        string          m_majorNumber;
        string          m_minorNumber;
        string          m_patchString;
        string          m_description;
    protected :
    public :
};

class WaveAsynchronousContextForUpgradePhase : public WaveAsynchronousContextForBootPhases 
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForUpgradePhase  (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForUpgradePhase  ();
        
/*
        vector<string>          getNewManagedObjects                    () const;
        void                    setNewManagedObjects                    (const vector<string> &newManagedObjects);

        vector<string>          getChangedManagedObjects                () const;
        void                    setChangedManagedObjects                (const vector<string> &changedManagedObjects);
*/
        OMSpecificSchemaChangeInfoForUpgrade* getSchemaChangeInfo       () const;  
        void                                  setSchemaChangeInfo       (OMSpecificSchemaChangeInfoForUpgrade* pSchemaChangeInfo);
 
        bool                    checkFromVersionString                  (const string &versionString);
        bool                    checkToVersionString                    (const string &versionString);

    // Now the data members

    private :
        /*
        vector<string>  m_changedManagedObjects;
        vector<string>  m_newManagedObjects;
        */
        
        OMSpecificSchemaChangeInfoForUpgrade* m_schemaChangeInfo;
        FirmwareVersion m_fromVersion;
        FirmwareVersion m_toVersion;

    protected :
    public :
};



}

#endif // WAVEASYNCHRONOUSCONTEXTFORUPGRADEPHASE_H
