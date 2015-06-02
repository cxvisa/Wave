/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mandar Datar                                                 *
 ***************************************************************************/

#include "File/Local/Test/FileTestMessages.h"
#include "File/Local/Test/FileLocalMessagingTestObjectManagerTypes.h"
#include "File/Local/Test/FileLocalMessagingTestObjectManager.h"

namespace WaveNs
{

CopyFileWaveClientMessage::CopyFileWaveClientMessage (const string &sourceFileName, const string &destinationFileName, UI32 &copyFileFlag, const vector<string> &vectorOfDestinationIpAddressesAndPorts)
    : ManagementInterfaceMessage                (FileLocalMessagingTestObjectManager::getServiceName (), FILE_LOCAL_TEST_COPY_FILE_WAVE_CLIENT_MESSAGE),
      m_sourceFileName                          (sourceFileName),
      m_destinationFileName                     (destinationFileName),
      m_copyFileFlag                            (copyFileFlag),
      m_vectorOfDestinationIpAddressesAndPorts  (vectorOfDestinationIpAddressesAndPorts)
{
}

CopyFileWaveClientMessage::CopyFileWaveClientMessage ()
    : ManagementInterfaceMessage (FileLocalMessagingTestObjectManager::getServiceName (), FILE_LOCAL_TEST_COPY_FILE_WAVE_CLIENT_MESSAGE),
      m_copyFileFlag                            (0)
{
}

CopyFileWaveClientMessage::~CopyFileWaveClientMessage ()
{
}

void CopyFileWaveClientMessage::setupAttributesForSerialization ()
{   
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString          (&m_sourceFileName,                         "sourceFileName"));
     addSerializableAttribute (new AttributeString          (&m_destinationFileName,                    "destinationFileName"));
     addSerializableAttribute (new AttributeUI32            (&m_copyFileFlag,                           "copyFileFlag"));
     addSerializableAttribute (new AttributeStringVector    (&m_vectorOfDestinationIpAddressesAndPorts, "vectorOfDestinationIpAddressesAndPorts"));
}

string CopyFileWaveClientMessage::getSourceFileName () const
{   
    return (m_sourceFileName);
}

void CopyFileWaveClientMessage::setSourceFileName (const string &sourceFileName)
{   
    m_sourceFileName = sourceFileName;
}

string CopyFileWaveClientMessage::getDestinationFileName () const
{   
    return (m_destinationFileName);
}

void CopyFileWaveClientMessage::setDestinationFileName (const string &destinationFileName)
{   
    m_destinationFileName = destinationFileName;
}

UI32 CopyFileWaveClientMessage::getCopyFileFlag () const
{   
    return (m_copyFileFlag);
}

void CopyFileWaveClientMessage::setCopyFileFlag (const UI32 &copyFileFlag)
{   
    m_copyFileFlag = copyFileFlag;
}

vector<string> CopyFileWaveClientMessage::getVectorOfDestinationIpAddressesAndPorts () const
{   
    return (m_vectorOfDestinationIpAddressesAndPorts);
}

void CopyFileWaveClientMessage::setVectorOfDestinationIpAddressesAndPorts (const vector<string> &vectorOfDestinationIpAddressesAndPorts)
{   
    m_vectorOfDestinationIpAddressesAndPorts = vectorOfDestinationIpAddressesAndPorts;
}



CopyFileToHaPeerWaveClientMessage::CopyFileToHaPeerWaveClientMessage (const string &sourceFileName, const string &destinationFileName)
    : ManagementInterfaceMessage                (FileLocalMessagingTestObjectManager::getServiceName (), FILE_LOCAL_TEST_COPY_FILE_TO_HA_PEER_WAVE_CLIENT_MESSAGE),
      m_sourceFileName                          (sourceFileName),
      m_destinationFileName                     (destinationFileName)
{
}

CopyFileToHaPeerWaveClientMessage::CopyFileToHaPeerWaveClientMessage ()
    : ManagementInterfaceMessage (FileLocalMessagingTestObjectManager::getServiceName (), FILE_LOCAL_TEST_COPY_FILE_TO_HA_PEER_WAVE_CLIENT_MESSAGE)
{
}

CopyFileToHaPeerWaveClientMessage::~CopyFileToHaPeerWaveClientMessage ()
{
}

void CopyFileToHaPeerWaveClientMessage::setupAttributesForSerialization ()
{   
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_sourceFileName,      "sourceFileName"));
     addSerializableAttribute (new AttributeString (&m_destinationFileName, "destinationFileName"));
}

string CopyFileToHaPeerWaveClientMessage::getSourceFileName () const
{   
    return (m_sourceFileName);
}

void CopyFileToHaPeerWaveClientMessage::setSourceFileName (const string &sourceFileName)
{   
    m_sourceFileName = sourceFileName;
}

string CopyFileToHaPeerWaveClientMessage::getDestinationFileName () const
{   
    return (m_destinationFileName);
}

void CopyFileToHaPeerWaveClientMessage::setDestinationFileName (const string &destinationFileName)
{   
    m_destinationFileName = destinationFileName;
}

}
