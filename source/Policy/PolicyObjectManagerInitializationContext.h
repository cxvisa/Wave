/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef POLICYOBJECTMANAGERINITIALIZATIONCONTEXT_H
#define POLICYOBJECTMANAGERINITIALIZATIONCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include "Policy/NBAR2/Nbar2.h"
#include "Policy/PfrThreshold/PfrThresholdTemplateRoot.h"

#include <set>
#include <string>

using namespace std;

namespace WaveNs
{

class PolicyObjectManagerInitializationContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                                          PolicyObjectManagerInitializationContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                          PolicyObjectManagerInitializationContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                          ~PolicyObjectManagerInitializationContext ();

                Nbar2                    &getNbar2                                 ();
                set<string>              &getAdjustedCategoryNames                 ();
                string                    getNbar2FileName                         () const;
                void                      loadNbar2                                ();
                void                      computeAdjustedCategoryNames             ();

                PfrThresholdTemplateRoot &getPfrThresholdTemplateRoot              ();
                string                    getPfrThresholdsFileName                 ();
                void                      loadPfrThresholdTemplateRoot             ();

                void                      addSubCategoryToPfrThresholdMapping      (const string &subCategoryName, const ObjectId &pfrThresholdTemplateObjectId);
                void                      getSubCategoryToPfrThresholdMappings     (vector<pair <string, ObjectId> > &subCategoryToPfrThresholdMappings) const;

                void                      addCategoryNameToObjectIdMapping         (const string & categoryName, const ObjectId &categoryObjectId);
                ObjectId                  getCategoryObjectId                      (const string &catefgoryName);

                void                      addSubCategoryNameToObjectIdMapping      (const string & subCategoryName, const ObjectId &subCategoryObjectId);
                ObjectId                  getSubCategoryObjectId                   (const string &subCategoryName);

    // Now the data members

    private :
               Nbar2                    m_nbar2;
               set<string>              m_adjustedCategoryNames;
               PfrThresholdTemplateRoot m_pfrThresholdTemplateRoot;

        static string                   m_nbar2FileName;
        static string                   m_pfrThresholdsFileName;

               map<string, ObjectId>    m_subCategoryToPfrThresholdMap;
               map<string, ObjectId>    m_categoryNameToObjectIdMap;
               map<string, ObjectId>    m_subCategoryNameToObjectIdMap;

    protected :
    public :
};
}
#endif // POLICYOBJECTMANAGERINITIALIZATIONCONTEXT_H
