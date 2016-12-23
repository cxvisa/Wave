/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "Framework/Utils/WaveMutex.h"

#include <magic.h>
#include <string>

using namespace std;

namespace WaveNs
{

class FileUtils
{
    private :
    protected :
    public :
        static void   initialize         ();
        static string getMimeTypeForFile (const string &filePath);

        // Now the data members

    private :
        static magic_t   s_magic;
        static WaveMutex s_mutex;

    protected :
    public :
};

}

#endif // FIlEUTILS_H
