/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/SystemManagementToolKit.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

vector<string> SystemManagementToolKit::m_yinPaths;
string         SystemManagementToolKit::m_wyserTagsFilePath;

vector<string> SystemManagementToolKit::getYinPaths ()
{
    return (m_yinPaths);
}

void SystemManagementToolKit::setYinPaths (const vector<string> &yinPaths)
{
    UI32 numberOfYinPaths = yinPaths.size ();
    UI32 i                = 0;

    for (i = 0; i < numberOfYinPaths; i++)
    {
        string yinPath = yinPaths[i];

        if (0 < (yinPath.size ()))
        {
            if ('/' != yinPath[0])
            {
                yinPath = (FrameworkToolKit::getProcessInitialWorkingDirectory ()) + "/" + yinPath;
            }

            m_yinPaths.push_back (yinPath);
        }
    }
}

string SystemManagementToolKit::getWyserTagsFilePath ()
{
    return (m_wyserTagsFilePath);
}

void SystemManagementToolKit::setWyserTagsFilePath (const string &wyserTagsFilePath)
{
    m_wyserTagsFilePath = wyserTagsFilePath;

    if (0 < (m_wyserTagsFilePath.size ()))
    {
        if ('/' != m_wyserTagsFilePath[0])
        {
            m_wyserTagsFilePath = (FrameworkToolKit::getProcessInitialWorkingDirectory ()) + "/" + m_wyserTagsFilePath;
        }
    }
}

string SystemManagementToolKit::getHelloSecret ()
{
    return ("LdorredhIpseMhySSyhMespIhderrodL");
}

}
