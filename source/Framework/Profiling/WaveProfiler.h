                            /***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEPROFILER_H
#define WAVEPROFILER_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"

#include <string>

using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif

void __cyg_profile_func_enter (void *pThisFunction, void *pFromCallSite) __attribute__ ((no_instrument_function));
void __cyg_profile_func_exit  (void *pThisFunction, void *pFromCallSite) __attribute__ ((no_instrument_function));
void   main_constructor       (void)                                     __attribute__ ((no_instrument_function, constructor));
void   main_destructor        (void)                                     __attribute__ ((no_instrument_function, destructor));

#ifdef __cplusplus
}
#endif

namespace WaveNs
{

class WaveProfiler
{
    private :
    protected :
    public :
        static string getProfileFileName ();
        static void   setProfileFileName (const string &profileFileName);

    // Now the data members

    private :
        static string         m_profileFileName;

    protected :
    public :
};

}

#endif // WAVEPROFILER_H

