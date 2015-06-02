/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YINPARSER_H
#define YINPARSER_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class YangElement;

class YinParser
{
    private :
    protected :
    public :
                                      YinParser                ();
                                     ~YinParser                ();
        static YangElement           *parseFile                (const string &yinFileName);
        static vector<YangElement *>  parseFiles               (const vector<string> &yinFileNames);
        static vector<YangElement *>  parseDiretory            (const string &directoryPath, vector<string> &yinFileNames);
        static vector<YangElement *>  parseDirectoriesAndFiles (const vector<string> &directoryPaths, const vector<string> &yinFileNames, vector<string> &outputYinFileNames);
        static ResourceId             debugParse               (UI32 argc, vector<string> argv);

        static YangElement           *parseYangUserInterface   (const string &serializedYin);

    // now the data members

    private :
    protected :
    public :
};

}

#endif // YINPARSER_H
