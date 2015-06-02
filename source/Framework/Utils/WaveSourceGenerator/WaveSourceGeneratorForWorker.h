/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESOURCEGENERATORFORWORKER_H
#define WAVESOURCEGENERATORFORWORKER_H

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"

namespace WaveNs
{

class WaveSourceGeneratorForWorker : public WaveSourceGeneratorBase
{
    private :
    protected :
    public :
                        WaveSourceGeneratorForWorker (const string &name, const string &nameSpace);
        virtual        ~WaveSourceGeneratorForWorker ();

        virtual string  generateClassName                   () const;
        virtual string  generateHIncludes                   () const;
        virtual string  generateHClassBegin                 () const;
        virtual string  generateHClassMemberFunctionsPublic () const;
        virtual string  generateCppMemberFunctions          () const;

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // WAVESOURCEGENERATORFORWORKER_H
