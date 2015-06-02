/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2INFOPP_H
#define NBAR2INFOPP_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Nbar2InfoPp : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2InfoPp ();
        virtual ~Nbar2InfoPp ();

    // Now the data elements

    private :
        string m_type;
        string m_ppVersion;
        string m_iosVersion;
        string m_platform;
        UI64   m_engineVersion;

    protected :
    public :
};

}

#endif // NBAR2INFOPP_H

