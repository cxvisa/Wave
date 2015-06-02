/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLPARAMETERSSUBCLASSIFICATION_H
#define NBAR2PROTOCOLPARAMETERSSUBCLASSIFICATION_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2ProtocolParametersSubClassificationParameter.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class Nbar2ProtocolParametersSubClassification : public Nbar2Element
{
    private :
        Nbar2Element *getNbar2ElementByName (const string &nbar2ElementName);

    protected :
    public :
                 Nbar2ProtocolParametersSubClassification ();
        virtual ~Nbar2ProtocolParametersSubClassification ();

    // Now the data elements

    private :
        vector<Nbar2ProtocolParametersSubClassificationParameter *> m_content;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLPARAMETERSSUBCLASSIFICATION_H

