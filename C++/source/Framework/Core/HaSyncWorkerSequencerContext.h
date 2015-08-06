/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                   *
 ***************************************************************************/

#ifndef HASYNCWORKERSEQUENCERCONTEXT_H
#define HASYNCWORKERSEQUENCERCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"

using namespace std;

namespace WaveNs
{

class StartHaSyncDumpContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                StartHaSyncDumpContext   (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                StartHaSyncDumpContext   (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                ~StartHaSyncDumpContext   ();
    // Now the data members

    private : 
        vector<WaveServiceId> m_waveServiceIdsVector;
        vector<WaveServiceId> m_waveServiceIdsToCommunicate;
        vector<void *>         m_validationDetailsVector;
        vector<UI32>           m_validationDetailsSizesVector;

        map<string, void *>    m_validationResultsVector;
        map<string, UI32>      m_validationResultsSizesVector;

        WaveMessage *         m_standbyMessage;
        UI32                   m_haVersion;
        bool                   m_isDbSyncRequired;
        bool                   m_isDbResumeRequired;
        UI32                   m_contextInfo;
        string                 m_haPeerIp;
        SI32                   m_haPeerPort;
        

    protected :
    public :
        vector<WaveServiceId> &getWaveServiceIdsToCommunicate ();
        vector<WaveServiceId> &getWaveServiceIdsVector        ();

        void                    addValidationDetailsForService  (const WaveServiceId &prismServiceId, void *pValidationDetials, const UI32 size);
        vector<void *>         &getValidationDetailsVector      ();
        vector<UI32>           &getValidationDetailsSizesVector ();
        void                    addValidationResultsForService (const WaveServiceId &prismServiceId, void *const &pValidationResults, const UI32 &validationResultsSize);

        void                    getValidationResultsForService  (const WaveServiceId &prismServiceId, void *&pValidationResults, UI32 &size);
        void                    setStandbyMessage               (WaveMessage *standbyMessage);
        WaveMessage *          getStandbyMessage               ();
        void                    setHaVersion                    (const UI32 &haVersion);
        UI32                    getHaVersion                    ();
        void                    setIsDbSyncRequired             (const bool &isDbSyncRequired);
        bool                    getIsDbSyncRequired             ();
        void                    setIsDbResumeRequired           (const bool &isDbResumeRequired);
        bool                    getIsDbResumeRequired           ();
        UI32                    getContextInfo                  ();
        void                    setContextInfo                  (const UI32 &contextInfo);
        string                  getHaPeerIp                     () const;
        void                    setHaPeerIp                     (const string& haPeerIp);
        SI32                    getHaPeerPort                   () const;
        void                    setHaPeerPort                   (const SI32& port);    
};

class ReceiveHaSyncDumpContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                ReceiveHaSyncDumpContext   (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                ReceiveHaSyncDumpContext   (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                ~ReceiveHaSyncDumpContext   ();
        void                    setIsDbSyncRequired             (const bool &isDbSyncRequired);
        bool                    getIsDbSyncRequired             ();
        UI32                    getContextInfo                  ();
        void                    setContextInfo                  (const UI32 &contextInfo);
        string                  getHaPeerIp                     () const;
        void                    setHaPeerIp                     (const string& haPeerIp);
        SI32                    getHaPeerPort                   () const;
        void                    setHaPeerPort                   (const SI32& port);    
    // Now the data members

    private :
        bool                   m_isDbSyncRequired;
        UI32                   m_contextInfo;
        string                 m_haPeerIp;
        SI32                   m_haPeerPort;

    protected :
    public :
};


}

#endif // PRISMFRAMEWORKOBJECTMANAGERHASYNCWORKERSEQUENCERCONTEXT_H 
