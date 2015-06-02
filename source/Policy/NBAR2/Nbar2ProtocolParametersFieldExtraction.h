/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLPARAMETERSFIELDEXTRACTION_H
#define NBAR2PROTOCOLPARAMETERSFIELDEXTRACTION_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2ProtocolParametersFieldExtractionParameter.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class Nbar2ProtocolParametersFieldExtraction : public Nbar2Element
{
    private :
        virtual  Nbar2Element *getNbar2ElementByName  (const string &nbar2ElementName);
    protected :
    public :
                 Nbar2ProtocolParametersFieldExtraction ();
        virtual ~Nbar2ProtocolParametersFieldExtraction ();

    // Now the data elements

    private :
        vector<Nbar2ProtocolParametersFieldExtractionParameter *> m_parameter;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLPARAMETERSFIELDEXTRACTION_H

