/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESERVERPAGEDIRECTORY_H
#define WAVESERVERPAGEDIRECTORY_H

#include "Framework/Types/Types.h"

#include <map>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveServerPage;
class WaveServerPageDirectoryEntry;

class WaveServerPageDirectory
{
    private :
    protected :
    public :
                                WaveServerPageDirectory              ();
        virtual                ~WaveServerPageDirectory              ();

        static  bool            isAKnownServerPage                   (const string &path);

        static  void            registerServerPage                   (WaveServerPage *pWaveServerPage);
        static  void            registerServerPage                   (const string &path, WaveServerPage *pWaveServerPage);
        static  WaveServerPage *getWaveServerPage                    (const string &path);

        static  void            getUriParameterValuesForRelativePath (const string &path, map<string, string> &uriParamterValues);

        static  ResourceId      print                                (UI32 argc, vector<string> argv);

    // Now the data members

    private :
        static map<string, WaveServerPage *> m_serverPageMap;
        static WaveServerPageDirectoryEntry  m_waveServerPageDirectoryRoot;

    protected :
    public :
};

}

#endif // WAVESERVERPAGEDIRECTORY_H
