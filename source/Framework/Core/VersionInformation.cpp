/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#include "Framework/Core/VersionInformation.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"

using namespace std;

namespace WaveNs
{

VersionInformation::VersionInformation ()
    : SerializableObject (),
      m_firmwareVersion (""),
      m_haVersion (0)
{
}

VersionInformation::~VersionInformation ()
{
}

void VersionInformation::setupAttributesForSerialization ()
{
    SerializableObject::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_firmwareVersion,  "firmwareVersion"));
    addSerializableAttribute (new AttributeUI32   (&m_haVersion,        "haVersion"));
}

void VersionInformation::display () const
{
    trace (TRACE_LEVEL_INFO, string ("___________________________________________________"));

    trace (TRACE_LEVEL_INFO, string ("Firmware Version   : ") + m_firmwareVersion);
    trace (TRACE_LEVEL_INFO, string ("HA Version         : ") + m_haVersion);

    trace (TRACE_LEVEL_INFO, string ("___________________________________________________"));
}

string VersionInformation::getFirmwareVersion () const
{
    return (m_firmwareVersion);
}

void VersionInformation::setFirmwareVersion (const string &firmwareVersion)
{
    m_firmwareVersion = firmwareVersion;
}

UI32 VersionInformation::getHaVersion () const
{
    return (m_haVersion);
}

void VersionInformation::setHaVersion (const UI32 &haVersion)
{
    m_haVersion = haVersion;
}

}
