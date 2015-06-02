/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "SystemManagement/Migration/WaveSystemManagementGetPossibleCompletionsMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"

namespace WaveNs
{

WaveSystemManagementGetPossibleCompletionsMessage::WaveSystemManagementGetPossibleCompletionsMessage ()
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_GET_POSSIBLE_COMPLETIONS_MESSAGE)
{
}

WaveSystemManagementGetPossibleCompletionsMessage::~WaveSystemManagementGetPossibleCompletionsMessage ()
{
}

void WaveSystemManagementGetPossibleCompletionsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
}

void WaveSystemManagementGetPossibleCompletionsMessage::addCompletionNameAndInfoOneByOne (const string &completionName, const string &completionInfo)
{
    m_completionNameAndInfo.push_back (make_pair(completionName, completionInfo));
}

void WaveSystemManagementGetPossibleCompletionsMessage::addCompletionNameByVector (const vector<pair <string, string> > &completionNameAndInfo)
{
    m_completionNameAndInfo = completionNameAndInfo;
}

vector<pair<string, string> > WaveSystemManagementGetPossibleCompletionsMessage::getCompletionNameAndInfo () const
{
    return (m_completionNameAndInfo);
}

string WaveSystemManagementGetPossibleCompletionsMessage::getCommandName () const
{
    return (m_commandName);
}

void WaveSystemManagementGetPossibleCompletionsMessage::setCommandName (const string &commandName)
{
    m_commandName = commandName;
}

string WaveSystemManagementGetPossibleCompletionsMessage::getToken () const
{
    return (m_token);
}

void WaveSystemManagementGetPossibleCompletionsMessage::setToken (const string &token)
{
    m_token = token;
}
}
