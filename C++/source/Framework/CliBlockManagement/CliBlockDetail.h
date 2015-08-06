/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#ifndef CLIBLOCKDETAIL
#define CLIBLOCKDETAIL

#include "Framework/Types/Types.h"
#include "Framework/CliBlockManagement/CliBlockContext.h"
#include "Framework/CliBlockManagement/CliBlockServiceIndependentMessage.h"

using namespace std;

namespace WaveNs
{

class CliBlockDetail
{
    private :
    protected :
    public :
                                    CliBlockDetail                      ();
                                    CliBlockDetail                      (WaveServiceId prismServiceId, LocationId originator, const CliBlockContext &cliBlockContext);
                                    CliBlockDetail                      (const CliBlockServiceIndependentMessage &cliBlockServiceIndependentMessage);
                                    CliBlockDetail                      (const CliBlockDetail &detail);
                                   ~CliBlockDetail                      ();
          CliBlockDetail&           operator=                           (const CliBlockDetail &detail);

    const WaveServiceId            getWaveServiceId                   () const;
    const LocationId                getOriginator                       () const;  
    const CliBlockContext&          getCliBlockContext                  () const;
                
           // Now the data members

    private :
            WaveServiceId            m_waveServiceId;
            LocationId                m_originator;
            CliBlockContext           m_cliBlockContext; 

    protected :
    public :

};
}

#endif // CLIBLOCKDETAIL
