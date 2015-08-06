/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorForObjectManager.h"

namespace WaveNs
{

WaveSourceGeneratorForObjectManager::WaveSourceGeneratorForObjectManager (const string &name, const string &nameSpace, const string &objectManagerName)
    : WaveSourceGeneratorBase (name, nameSpace),
      m_objectManagerName     (objectManagerName)
{
}

WaveSourceGeneratorForObjectManager::~WaveSourceGeneratorForObjectManager ()
{
}

string WaveSourceGeneratorForObjectManager::generateClassName () const
{
    return (m_name + "ObjectManager");
}

string WaveSourceGeneratorForObjectManager::generateHIncludes () const
{
    string hIncludes = "#include \"Framework/ObjectModel/WaveObjectManager.h\"\n"
                       "\n";

    return (hIncludes);
}

string WaveSourceGeneratorForObjectManager::generateHClassBegin () const
{
    string classBegin = "class " + generateClassName () + " : public WaveObjectManager\n"
                        "{\n";

    return (classBegin);
}

string WaveSourceGeneratorForObjectManager::generateHClassMemberFunctionsPrivate () const
{
    string memberFunctionsPublic = "    private :\n"
                                   "                 " + generateClassName () + " ();\n"
                                   "\n";

    return (memberFunctionsPublic);
}

string WaveSourceGeneratorForObjectManager::generateHClassMemberFunctionsPublic () const
{
    string memberFunctionsPublic = "    public :\n"
                                   "        virtual ~" + generateClassName () + " ();\n"
                                   "\n"
                                   "        static " + generateClassName () + " *getInstance ();\n"
                                   "        static WaveServiceId getWaveServiceId ();\n";

    return (memberFunctionsPublic);
}

string WaveSourceGeneratorForObjectManager::generateCppMemberFunctions () const
{
    string memberFunctions;

    memberFunctions += generateClassName () + "::" + generateClassName () + " ()\n"
                       "    : WaveObjectManager (\"" + m_objectManagerName + "\")\n"
                       "{\n"
                       "}\n"
                       "\n";

    memberFunctions += generateClassName () + "::~" + generateClassName () + " ()\n"
                       "{\n"
                       "}\n"
                       "\n";

    memberFunctions += generateClassName () + " *" + generateClassName () + ":: getInstance ()\n"
                       "{\n"
                       "    static " + generateClassName () + " *p" + generateClassName () + " = new " + generateClassName () + " ();\n"
                       "\n"
                       "    WaveNs::waveAssert (NULL != p" + generateClassName () + ", __FILE__, __LINE__);\n"
                       "\n"
                       "    return (p" + generateClassName () + ");\n"
                       "}\n"
                       "\n";

    memberFunctions += "WaveServiceId " + generateClassName () + ":: getWaveServiceId ()\n"
                       "{\n"
                       "    return ((getInstance ())->getServiceId ());\n"
                       "}\n"
                       "\n";

    return (memberFunctions);
}

}
