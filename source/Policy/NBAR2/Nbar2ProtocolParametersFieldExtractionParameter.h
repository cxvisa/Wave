/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLPARAMETERSFIELDEXTRACTIONPARAMETER_H
#define NBAR2PROTOCOLPARAMETERSFIELDEXTRACTIONPARAMETER_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Nbar2ProtocolParametersFieldExtractionParameter : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2ProtocolParametersFieldExtractionParameter ();
        virtual ~Nbar2ProtocolParametersFieldExtractionParameter ();

    // Now the data elements

    private :
        string m_helpString;
        UI64   m_id;
        string m_name;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLPARAMETERSFIELDEXTRACTIONPARAMETER_H

