/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LICENSEOBJECTMANAGER_H
#define LICENSEOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class LicenseObjectManager : public WaveObjectManager
{
    private :
        LicenseObjectManager ();

    protected :
    public :
        virtual                      ~LicenseObjectManager ();
        static  LicenseObjectManager *getInstance          ();
        static  PrismServiceId        getPrismServiceId    ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // LICENSEOBJECTMANAGER_H
