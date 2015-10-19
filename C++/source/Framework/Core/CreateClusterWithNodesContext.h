/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CREATECLUSTERWITHNODESCONTEXT_H
#define CREATECLUSTERWITHNODESCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class CreateClusterWithNodesContext : public WaveLinearSequencerContext
{
    private :
        bool doesLocationExist (const LocationId &locationId);

    protected :
    public :
                                CreateClusterWithNodesContext   (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                CreateClusterWithNodesContext   (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                ~CreateClusterWithNodesContext   ();
        void                    addNewLocationId                (const LocationId &locationId);
        void                    removeNewLocationId             (const LocationId &locationId);
        UI32                    getNumberOfNewLocationIds       ();
        LocationId              getNewLocationIdAt              (const UI32 &i);
        void                    addValidationDetailsForService  (const WaveServiceId &waveServiceId, void *pValidationDetials, const UI32 size);
        vector<WaveServiceId> &getWaveServiceIdsVector        ();
        vector<void *>         &getValidationDetailsVector      ();
        vector<UI32>           &getValidationDetailsSizesVector ();
        void                    addValidaionResultsLocation     (const string &ipAddress, const SI32 &port);
        UI32                    getNumberOfResultsLocations     ();
        void                    getResultsLocationAt            (const UI32 &i, string &ipAddress, SI32 &port);
        void                    addValidationResultsForService  (const string &ipAddress, const SI32 &port, const WaveServiceId &waveServiceId, void *const &pValidationResults, const UI32 &validationResultsSize);
        void                    getValidationResultsForService  (const string &ipAddress, const SI32 &port, const WaveServiceId &waveServiceId, void *&pValidationResults, UI32 &validationResultsSize);
        vector<WaveServiceId> &getWaveServiceIdsToCommunicate ();

        void                    addToSuccessfullyAddedLocationIdVector (LocationId locationId);
        vector<LocationId>      getSuccessfullyAddedLocationIdVector   () const ;
        void                    addToFailedLocationIdVector            (LocationId locationId);
        vector<LocationId>      getFailedLocationIdVector              () const ;
        bool                    isAFailedLocation                      (LocationId locationId);
        void                    clearFailedLocationIdVector            ();
        bool                    getIsDeletion                          ()    const;
        void                    setIsDeletion                          (bool deletion);
        bool                    getIsCreateClusterContext              () const;
        void                    setIsCreateClusterContext              (const bool &isCreateClusterContext);
    // Now the data members

    private :
        vector<LocationId>     m_newLocationIdsVector;
        vector<WaveServiceId> m_waveServiceIdsVector;
        vector<void *>         m_validationDetailsVector;
        vector<UI32>           m_validationDetailsSizesVector;

        vector<WaveServiceId> m_waveServiceIdsToCommunicate;

        vector<string>         m_waveLocationIpAddressesForValidationResultsVector;
        vector<SI32>           m_waveLocationPortsForValidationResultsVector;
        map<string, void *>    m_waveLocationValidationResultsVector;
        map<string, UI32>      m_waveLocationValidationResultsSizesVector;
        bool                   m_isDeletion;
        vector<LocationId>     m_successfullyAddedLocationIdVector;
        vector<LocationId>     m_failedLocationIds;
        bool                   m_isCreateClusterContext;

    protected :
    public :
};

}

#endif // CREATECLUSTERWITHNODESCONTEXT_H
