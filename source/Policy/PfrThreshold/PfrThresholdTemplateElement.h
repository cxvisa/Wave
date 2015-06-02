/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PFRTHRESHOLDTEMPLATEELEMENT_H
#define PFRTHRESHOLDTEMPLATEELEMENT_H

#include "Policy/PfrThreshold/PfrThresholdElement.h"
#include "Framework/Types/Types.h"
#include "Policy/PfrThreshold/PfrThresholdTemplateElementSubCategoryCollection.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class PfrThresholdTemplateElement : public PfrThresholdElement
{
    private :
    protected :
    public :
                        PfrThresholdTemplateElement ();
        virtual        ~PfrThresholdTemplateElement ();

                string                                            getTemplateName          () const;
                SI32                                              getLossRate              () const;
                SI32                                              getOneWayDelay           () const;
                SI32                                              getJitter                () const;
                SI32                                              getLossRatePriority      () const;
                SI32                                              getOneWayDelayPriority   () const;
                SI32                                              getJitterPriority        () const;

                PfrThresholdTemplateElementSubCategoryCollection &getSubCategoryCollection ();

    // Now the data members

    private :
        string                                           m_templateName;
        SI32                                             m_lossRate;
        SI32                                             m_oneWayDelay;
        SI32                                             m_jitter;
        SI32                                             m_lossRatePriority;
        SI32                                             m_oneWayDelayPriority;
        SI32                                             m_jitterPriority;

        PfrThresholdTemplateElementSubCategoryCollection m_subCateforyCollection;

    protected :
    public :
};

}

#endif // PFRTHRESHOLDTEMPLATEELEMENT_H
