/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MAPREDUCEINPUTCONFIGURATION_H
#define MAPREDUCEINPUTCONFIGURATION_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class MapReduceInputConfiguration
{
    private :
    protected :
    public :
                      MapReduceInputConfiguration  ();
        virtual      ~MapReduceInputConfiguration  ();

                UI32  getMaximumNumberOfPartitions () const;
                void  setMaximumNumberOfPartitions (const UI32 &maximumNumberOfPartitions);

        // Now the data members

    private :
        UI32 m_maximumNumberOfPartitions;

    protected :
    public :
};

}

#endif // MAPREDUCEINPUTCONFIGURATION_H
