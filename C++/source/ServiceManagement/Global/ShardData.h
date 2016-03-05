/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SHARDDATA_H
#define SHARDDATA_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class ShardData : virtual public WaveManagedObject
{
    private :
    protected :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    public :
                 ShardData (WaveObjectManager *pWaveObjectManager);
        virtual ~ShardData ();

        static string getClassName ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // SHARDDATA_H
