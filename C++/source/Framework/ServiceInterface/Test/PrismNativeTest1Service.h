/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMNATIVETEST1SERVICE_H
#define PRISMNATIVETEST1SERVICE_H

#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ServiceInterface/Test/PrismNativeTest1ServiceMessages.h"

namespace WaveNs
{

class PrismNativeTest1Service : public WaveObjectManager
{
    private :
        PrismNativeTest1Service ();

    protected :
    public :
                                       ~PrismNativeTest1Service                ();

        static PrismNativeTest1Service *getInstance                            ();
        static PrismServiceId           getPrismServiceId                      ();

               void                     prismNativeTest1ServiceMessage1Handler (PrismNativeTest1ServiceMessage1 *pMsg);

    // Now the Data Memebers

    private :
    protected :
    public :
};

}

#endif // PRISMNATIVETEST1SERVICE_H
