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
                                        void     setWaveServiceId              (WaveServiceId waveServiceId);
                                        bool     isApplicationSpecificServiceId (WaveServiceId waveServiceId);   

    // Now the data members

    private :
                 vector<WaveServiceId>        m_WaveServiceId;
    protected :
    public :
};

}

#endif //APPLICATIONSPECIFICSERVICES_H 
