/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2INFO_H
#define NBAR2INFO_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2InfoPp.h"

namespace WaveNs
{

class Nbar2Info : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2Info ();
        virtual ~Nbar2Info ();

    // Now the data members

    private :
        string      m_type;
        string      m_fileVersion;
        Nbar2InfoPp m_nbar2InfoPp;

    protected :
    public :
};

}

#endif // NBAR2INFO_H

