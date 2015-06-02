/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESOURCEGENERATORFORMESSAGE_H
#define WAVESOURCEGENERATORFORMESSAGE_H

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"

namespace WaveNs
{

class WaveSourceGeneratorForMessage : public WaveSourceGeneratorBase
{
    private :
    protected :
    public :
                        WaveSourceGeneratorForMessage        (const string &name, const string &nameSpace);
        virtual        ~WaveSourceGeneratorForMessage        ();

        virtual string  generateClassName                    () const;
        virtual string  generateHIncludes                    () const;
        virtual string  generateHClassBegin                  () const;
        virtual string  generateHClassMemberFunctionsPrivate () const;
        virtual string  generateHClassMemberFunctionsPublic  () const;
        virtual string  generateCppMemberFunctions           () const;

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // WAVESOURCEGENERATORFORMESSAGE_H
