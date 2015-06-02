/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PFRTHRESHOLDTEMPLATEROOT_H
#define PFRTHRESHOLDTEMPLATEROOT_H

#include "Framework/Types/Types.h"
#include "Policy/PfrThreshold/PfrThresholdElement.h"
#include "Policy/PfrThreshold/PfrThresholdTemplateElement.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class PfrThresholdTemplateRoot : public PfrThresholdElement
{
    private :
        virtual  PfrThresholdElement *getPfrThresholdElementByName  (const string &nbar2ElementName);

    protected :
    public :
                                                       PfrThresholdTemplateRoot        ();
        virtual                                       ~PfrThresholdTemplateRoot        ();

                void                                   load                            (const string &pfrThresholdsFileName);

                vector<PfrThresholdTemplateElement *> &getPfrThresholdTemplateElements ();


    // Now the data members

    private :
        vector<PfrThresholdTemplateElement *> m_pfrThresholdTemplateElements;

    protected :
    public :
};

}

#endif // PFRTHRESHOLDTEMPLATEROOT_H

