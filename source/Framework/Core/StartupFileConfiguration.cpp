/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#include "Framework/Core/StartupFileConfiguration.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"

using namespace std;

namespace WaveNs
{

StartupFileConfiguration::StartupFileConfiguration ()
    : SerializableObject (),
      m_version (0),
      m_startupFileType (0),
      m_startupFileName (""),
      m_startupFile ("")
{
}

StartupFileConfiguration::~StartupFileConfiguration ()
{
}

void StartupFileConfiguration::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeUI32     (&m_version,            "version"));
    addSerializableAttribute (new AttributeUI32     (&m_startupFileType,    "startupFileType"));
    addSerializableAttribute (new AttributeString   (&m_startupFileName,    "startupFileName"));
    addSerializableAttribute (new AttributeString   (&m_startupFile,        "startupFile"));
}

void StartupFileConfiguration::setupAttributesForSerializationInAttributeOrderFormat ()
{
    SerializableObject::setupAttributesForSerializationInAttributeOrderFormat ();

    addAttributeNameForOrderToNameMapping ("version");
    addAttributeNameForOrderToNameMapping ("startupFileType");
    addAttributeNameForOrderToNameMapping ("startupFileName");
    addAttributeNameForOrderToNameMapping ("startupFile");
}


void StartupFileConfiguration::display () const
{
    trace (TRACE_LEVEL_INFO, string ("___________________________________________________"));

    trace (TRACE_LEVEL_INFO, string ("Version            : ") + m_version);
    trace (TRACE_LEVEL_INFO, string ("Startup File Type  : ") + m_startupFileType);
    trace (TRACE_LEVEL_INFO, string ("Startup File Name  : ") + m_startupFileName);
    trace (TRACE_LEVEL_INFO, string ("Startup File       : ") + m_startupFile);

    trace (TRACE_LEVEL_INFO, string ("___________________________________________________"));
}

UI32 StartupFileConfiguration::getVersion () const
{
    return (m_version);
}

void StartupFileConfiguration::setVersion (const UI32 &version)
{
    m_version = version;
}

UI32 StartupFileConfiguration::getStartupFileType () const
{
    return (m_startupFileType);
}

void StartupFileConfiguration::setStartupFileType (const UI32 &startupFileType)
{
    m_startupFileType = startupFileType;
}

string StartupFileConfiguration::getStartupFileName () const
{
    return (m_startupFileName);
}

void StartupFileConfiguration::setStartupFileName (const string &startupFileName)
{
    m_startupFileName = startupFileName;
}

string StartupFileConfiguration::getStartupFile () const
{
    return (m_startupFile);
}

void StartupFileConfiguration::setStartupFile (const string &startupFile)
{
    m_startupFile = startupFile;
}

}
