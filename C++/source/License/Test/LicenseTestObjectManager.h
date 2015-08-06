/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LICENSETESTOBJECTMANAGER_H
#define LICENSETESTOBJECTMANAGER_H

#include "Regression/PrismTestObjectManager.h"

namespace WaveNs
{

class LicenseTestObjectManager : public PrismTestObjectManager
{
    private :
        LicenseTestObjectManager ();

    protected :
    public :
        virtual                          ~LicenseTestObjectManager ();
                void                      testRequestHandler       (RegressionTestMessage *pMessage);
        static  LicenseTestObjectManager *getInstance              ();
        static  WaveServiceId            getWaveServiceId        ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // LICENSETESTOBJECTMANAGER_H
