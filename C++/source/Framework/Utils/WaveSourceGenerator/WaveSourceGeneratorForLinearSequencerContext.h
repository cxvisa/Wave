/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESOURCEGENERATORFORLINEARSEQUENCERCONTEXT_H
#define WAVESOURCEGENERATORFORLINEARSEQUENCERCONTEXT_H

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"

namespace WaveNs
{

class WaveSourceGeneratorForLinearSequencerContext : public WaveSourceGeneratorBase
{
    private :
    protected :
    public :
                        WaveSourceGeneratorForLinearSequencerContext (const string &name, const string &nameSpace);
        virtual        ~WaveSourceGeneratorForLinearSequencerContext ();

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

#endif // WAVESOURCEGENERATORFORLINEARSEQUENCERCONTEXT_H
