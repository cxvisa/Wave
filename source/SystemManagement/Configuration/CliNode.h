/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLINODE_H
#define CLINODE_H

#include "Framework/Types/Types.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class CliNode
{
    private :
    protected :
    public :
                  CliNode                               ();
                  CliNode                               (const string &cliNodeName);
                 ~CliNode                               ();

         void     destroyAndClearChildren               ();

         string   getCliNodeName                        () const;
         void     setCliNodeName                        (const string &cliNodeName);

         void     addChild                              (const string &childCliNodeName);
         void     addChild                              (CliNode * const pChildCliNode);
         bool     isAKnownChild                         (const string &childCliNodeName) const;
         CliNode *getChild                              (const string &childCliNodeName);

         void     addCommandLine                        (const string &commandLine);

         void     getChildrenCliNodeNames               (vector<string> &childrenCliNodeNames);
         void     getChildrenCliNodeNamesForCommandLine (const string &commandLine, vector<string> &childrenCliNodeNames);

        // Now the data members

    private :
        string                 m_cliNodeName;
        vector<CliNode *>      m_children;
        map<string, CliNode *> m_childrenMap;

    protected :
    public :
};

}

#endif // CLINODE_H
