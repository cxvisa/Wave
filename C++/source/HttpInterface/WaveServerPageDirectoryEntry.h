/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESERVERPAGEDIRECTORYENTRY_H
#define WAVESERVERPAGEDIRECTORYENTRY_H

#include "Framework/Types/Types.h"
#include <map>

using namespace std;

namespace WaveNs
{

class WaveServerPage;

class WaveServerPageDirectoryEntry
{
    private :
    protected :
    public :
                                      WaveServerPageDirectoryEntry         (const string &nodeName, WaveServerPage *pWaveServerPage);
                                     ~WaveServerPageDirectoryEntry         ();

        bool                          isAKnownImmediateSibling             (const string &immediateSiblingName);
        WaveServerPageDirectoryEntry *getImmediateSibling                  (const string &immediateSiblingName);
        bool                          isAKnownSibling                      (const string &siblingName);
        WaveServerPageDirectoryEntry *getSibling                           (const string &siblingName);
        void                          addImmediateSibling                  (const string &immediateSiblingName, WaveServerPage *pWaveServerPage = NULL);
        void                          addSibling                           (const string &siblingName, WaveServerPage *pWaveServerPage = NULL);
        void                          print                                (const string &prefix = "") const;
        WaveServerPage               *getWaveServerPageForRelativePath     (const string &path);
        WaveServerPage               *getPWaveServerPage                   ();
        void                          setPWaveServerPage                   (WaveServerPage *pWaveServerPage);
        void                          getUriParameterValuesForRelativePath (const string &path, map<string, string> &uriParamterValues);

    // Now the data members

    private :
    string                                       m_nodeName;
    string                                       m_uriParameterName;
    WaveServerPage								*m_pWaveServerPage;
    map<string, WaveServerPageDirectoryEntry *>  m_siblingsMap;

    protected :
    public :
};

#endif // WAVESERVERPAGEDIRECTORYENTRY_H

}
