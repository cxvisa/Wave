/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorForWorker.h"

namespace WaveNs
{

WaveSourceGeneratorForWorker::WaveSourceGeneratorForWorker (const string &name, const string &nameSpace)
    : WaveSourceGeneratorBase (name, nameSpace)
{
}

WaveSourceGeneratorForWorker::~WaveSourceGeneratorForWorker ()
{
}

string WaveSourceGeneratorForWorker::generateClassName () const
{
    return (m_name + "Worker");
}

string WaveSourceGeneratorForWorker::generateHIncludes () const
{
    string hIncludes = "#include \"Framework/ObjectModel/WaveWorker.h\"\n"
                       "\n";

    return (hIncludes);
}

string WaveSourceGeneratorForWorker::generateHClassBegin () const
{
    string classBegin = "class " + generateClassName () + " : public WaveWorker\n"
                        "{\n";

    return (classBegin);
}

string WaveSourceGeneratorForWorker::generateHClassMemberFunctionsPublic () const
{
    string memberFunctionsPublic = "    public :\n"
                                   "                 " + generateClassName () + " (WaveObjectManager *pWaveObjectManager);\n"
                                   "        virtual ~" + generateClassName () + " ();\n";

    return (memberFunctionsPublic);
}

string WaveSourceGeneratorForWorker::generateCppMemberFunctions () const
{
    string memberFunctions;

    memberFunctions += generateClassName () + "::" + generateClassName () + " (WaveObjectManager *pWaveObjectManager)\n"
                       "    : WaveWorker (pWaveObjectManager)\n"
                       "{\n"
                       "}\n"
                       "\n";

    memberFunctions += generateClassName () + "::~" + generateClassName () + " ()\n"
                       "{\n"
                       "}\n"
                       "\n";

    return (memberFunctions);
}

}
