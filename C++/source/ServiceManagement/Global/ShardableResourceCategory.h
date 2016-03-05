/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SHARDABLERESOURCECATEGORY_H
#define SHARDABLERESOURCECATEGORY_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class ShardableResourceCategory : virtual public WaveManagedObject
{
    private :
    protected :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    public :
                 ShardableResourceCategory (WaveObjectManager *pWaveObjectManager);
        virtual ~ShardableResourceCategory ();

        static string getClassName ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // SHARDABLERESOURCECATEGORY_H
