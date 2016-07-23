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
                                             MapReduceInputConfiguration                  ();
                                             MapReduceInputConfiguration                  (const UI32 &maximumNumberOfPartitions);
                                             MapReduceInputConfiguration                  (const MapReduceInputConfiguration &mapReduceInputConfiguration);
        virtual                             ~MapReduceInputConfiguration                  ();

                UI32                         getMaximumNumberOfPartitions                 () const;
                void                         setMaximumNumberOfPartitions                 (const UI32 &maximumNumberOfPartitions);

                MapReduceInputConfiguration &operator =                                   (const MapReduceInputConfiguration &mapReduceInputConfiguration);

        virtual UI32                         computeMaximumNumberOfPartitionsRequired     () const = 0;

        virtual UI32                         getAdjustedMaximumNumberOfPartitionsRequired () const;

        // Now the data members

    private :
        UI32 m_maximumNumberOfPartitions;

    protected :
    public :
};

}

#endif // MAPREDUCEINPUTCONFIGURATION_H
