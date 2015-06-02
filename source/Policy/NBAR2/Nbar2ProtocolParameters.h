/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLPARAMETERS_H
#define NBAR2PROTOCOLPARAMETERS_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2ProtocolParametersSubClassification.h"
#include "Policy/NBAR2/Nbar2ProtocolParametersFieldExtraction.h"

namespace WaveNs
{

class Nbar2ProtocolParameters : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2ProtocolParameters ();
        virtual ~Nbar2ProtocolParameters ();

    // Now the data elements

    private :
        Nbar2ProtocolParametersSubClassification m_subClassification;
        Nbar2ProtocolParametersFieldExtraction   m_filedExtraction;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLPARAMETERS_H

