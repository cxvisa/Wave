/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESOURCEGENERATORFOROBJECTMANAGER_H
#define WAVESOURCEGENERATORFOROBJECTMANAGER_H

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"

namespace WaveNs
{

class WaveSourceGeneratorForObjectManager : public WaveSourceGeneratorBase
{
    private :
    protected :
    public :
                        WaveSourceGeneratorForObjectManager  (const string &name, const string &nameSpace, const string &m_objectManagerName);
        virtual        ~WaveSourceGeneratorForObjectManager  ();

        virtual string  generateClassName                    () const;
        virtual string  generateHIncludes                    () const;
        virtual string  generateHClassBegin                  () const;
        virtual string  generateHClassMemberFunctionsPrivate () const;
        virtual string  generateHClassMemberFunctionsPublic  () const;
        virtual string  generateCppMemberFunctions           () const;

    // Now the Data Members

    private :
        string m_objectManagerName;

    protected :
    public :
};

}

#endif // WAVESOURCEGENERATORFOROBJECTMANAGER_H
