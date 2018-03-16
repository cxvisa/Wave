/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECURITYLOCALOBJECTMANAGER_H
#define SECURITYLOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class SecurityLocalObjectManager : public WaveLocalObjectManager
{
    private:
        SecurityLocalObjectManager ();

    protected:
    public:
        virtual ~SecurityLocalObjectManager ();

        static string getServiceName ();
        static SecurityLocalObjectManager *getInstance ();

        // Now the data members

    private:
    protected:
    public:
};

}

#endif // SECURITYLOCALOBJECTMANAGER_H
