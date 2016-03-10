/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERVICEINSTANCETOOLKIT_H
#define SERVICEINSTANCETOOLKIT_H

#include <string>
#include <map>

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"

using namespace std;

namespace WaveNs
{

class ExternalNonNativeServiceInstanceManagedObject;

class ServiceInstanceToolKit
{
    private :
             ServiceInstanceToolKit ();

        void initialize                  ();

    protected :
    public :
        virtual                                                     ~ServiceInstanceToolKit   ();
        static  ExternalNonNativeServiceInstanceManagedObject *getServiceInstanceByName (const string &name);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // SERVICEINSTANCETOOLKIT_H
