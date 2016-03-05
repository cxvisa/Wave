/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorForLinearSequencerContext.h"

namespace WaveNs
{

WaveSourceGeneratorForLinearSequencerContext::WaveSourceGeneratorForLinearSequencerContext (const string &name, const string &nameSpace)
    : WaveSourceGeneratorBase (name, nameSpace)
{
}

WaveSourceGeneratorForLinearSequencerContext::~WaveSourceGeneratorForLinearSequencerContext ()
{
}

string WaveSourceGeneratorForLinearSequencerContext::generateClassName () const
{
    return (m_name + "Context");
}

string WaveSourceGeneratorForLinearSequencerContext::generateHIncludes () const
{
    string hIncludes = "#include \"Framework/Utils/WaveLinearSequencerContext.h\"\n"
                       "\n";

    return (hIncludes);
}

string WaveSourceGeneratorForLinearSequencerContext::generateHClassBegin () const
{
    string classBegin = "class " + generateClassName () + " : public WaveLinearSequencerContext\n"
                        "{\n";

    return (classBegin);
}

string WaveSourceGeneratorForLinearSequencerContext::generateHClassMemberFunctionsPublic () const
{
    string memberFunctionsPublic = "    public :\n"
                                   "                 " + generateClassName () + " (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);\n"
                                   "        virtual ~" + generateClassName () + " ();\n";

    return (memberFunctionsPublic);
}

string WaveSourceGeneratorForLinearSequencerContext::generateCppMemberFunctions () const
{
    string memberFunctions;

    memberFunctions += generateClassName () + "::" + generateClassName () + " (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)\n"
                       "    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)\n"
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
