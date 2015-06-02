/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
***************************************************************************/

#ifndef APPLICATIONSPECIFICSERVICES_H
#define APPLICATIONSPECIFICSERVICES_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class ApplicationSpecificServices
{
    private :
    protected :     
    public :
                                                 ApplicationSpecificServices ();
                                     virtual    ~ApplicationSpecificServices ();

        static   ApplicationSpecificServices    *getInstance                    ();
                                        void     setPrismServiceId              (PrismServiceId prismServiceId);
                                        bool     isApplicationSpecificServiceId (PrismServiceId prismServiceId);   

    // Now the data members

    private :
                 vector<PrismServiceId>        m_PrismServiceId;
    protected :
    public :
};

}

#endif //APPLICATIONSPECIFICSERVICES_H 
