/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#ifndef CLIBLOCKCONTEXT
#define CLIBLOCKCONTEXT

#include "Framework/Types/Types.h"

using namespace std;

namespace WaveNs
{

class CliBlockContext
{
    private :
    protected :
    public :
                                    CliBlockContext                      ();
                                    CliBlockContext                      (ResourceId reason);
                                    CliBlockContext                      (const CliBlockContext &context);
                                   ~CliBlockContext                      ();
          CliBlockContext&          operator=                            (const CliBlockContext &context);

    const ResourceId                getReason                           () const;  
          void                      setReason                           (ResourceId reason);
                
           // Now the data members

    private :
            ResourceId              m_reason;

    protected :
    public :

};
}

#endif // CLIBLOCKCONTEXT
