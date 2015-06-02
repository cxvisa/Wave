/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGELEMENTFACTORY_H
#define YANGELEMENTFACTORY_H

#include <string>
#include <map>

using namespace std;

namespace WaveNs
{

class YangElement;

typedef YangElement * (*YangElementInstantiator) ();

class YangElementFactory
{
    private :
    protected :
    public :
        static bool         isAKnownYangName           (const string &yangName);
        static void         addYangElementInstantiator (const string &yangName, YangElementInstantiator yangElementInstantiator);
        static YangElement *createYangElement          (const string &yangName);

        static void         initialize                 ();

    // Now the data members

    private :
        static map<string, YangElementInstantiator> m_yangElementInstantiatorMap;

    protected :
    public :
};

}

#endif // YANGELEMENTFACTORY_H
