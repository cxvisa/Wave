/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SYSTEMMANAGEMENTTOOLKIT_H
#define SYSTEMMANAGEMENTTOOLKIT_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class SystemManagementToolKit
{
    private :
    protected :
    public :
        static vector<string> getYinPaths          ();
        static void           setYinPaths          (const vector<string> &yinPaths);

        static string         getWyserTagsFilePath ();
        static void           setWyserTagsFilePath (const string &wyserTagsFilePath);

        static string         getHelloSecret       ();

    // Now the data members

    private :
        static vector<string> m_yinPaths;
        static string         m_wyserTagsFilePath;

    protected :
    public :
};

}

#endif // SYSTEMMANAGEMENTTOOLKIT_H
