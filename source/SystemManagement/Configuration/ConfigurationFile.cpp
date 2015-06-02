/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/Configuration/ConfigurationFile.h"

namespace WaveNs
{

ConfigurationFile::ConfigurationFile ()
    : m_isAlreadyLoaded (false)
{
}

ConfigurationFile::ConfigurationFile (const string &configurationFilePath)
    : m_configurationFilePath (configurationFilePath),
      m_isAlreadyLoaded (false)

{
}

ConfigurationFile::~ConfigurationFile ()
{
}

string ConfigurationFile::getConfigurationFilePath () const
{
    return (m_configurationFilePath);
}

void ConfigurationFile::setConfigurationFilePath (const string &configurationFilePath)
{
    m_configurationFilePath = configurationFilePath;
}

bool ConfigurationFile::getIsAlreadyLoaded () const
{
    return (m_isAlreadyLoaded);
}

void ConfigurationFile::setIsAlreadyLoaded (const bool &isAlreadyLoaded)
{
    m_isAlreadyLoaded = isAlreadyLoaded;
}

}
