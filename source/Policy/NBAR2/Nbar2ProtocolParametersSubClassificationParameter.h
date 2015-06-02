/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLPARAMETERSSUBCLASSIFICATIONPARAMETER_H
#define NBAR2PROTOCOLPARAMETERSSUBCLASSIFICATIONPARAMETER_H

#include "Policy/NBAR2/Nbar2Element.h"

namespace WaveNs
{

class Nbar2ProtocolParametersSubClassificationParameter : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2ProtocolParametersSubClassificationParameter ();
        virtual ~Nbar2ProtocolParametersSubClassificationParameter ();

    // Now the data elements

    private :
        string m_helpString;
        string m_name;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLPARAMETERSSUBCLASSIFICATIONPARAMETER_H

