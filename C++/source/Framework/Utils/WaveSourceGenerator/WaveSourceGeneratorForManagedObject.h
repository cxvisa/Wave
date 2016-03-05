/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESOURCEGENERATORFORMANAGEDOBJECT_H
#define WAVESOURCEGENERATORFORMANAGEDOBJECT_H

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"

namespace WaveNs
{

class WaveSourceGeneratorForManagedObject : public WaveSourceGeneratorBase
{
    private :
    protected :
    public :
                        WaveSourceGeneratorForManagedObject  (const string &name, const string &nameSpace);
        virtual        ~WaveSourceGeneratorForManagedObject  ();

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

#endif // WAVESOURCEGENERATORFORMANAGEDOBJECT_H
