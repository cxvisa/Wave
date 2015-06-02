/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mandar Datar                                                 *
 ***************************************************************************/

#ifndef COPYFILEWAVECLIENTMESSAGE_H
#define COPYFILEWAVECLIENTMESSAGE_H

#include <vector>
#include "ManagementInterface/ManagementInterfaceMessage.h"

using namespace std;

namespace WaveNs
{

class CopyFileWaveClientMessage : public ManagementInterfaceMessage
{
    private :
            void            setupAttributesForSerialization             ();

    protected :
    public :
                            CopyFileWaveClientMessage                   (const string &sourceFileName, const string &destinationFileName, UI32 &copyFileFlag, const vector<string> &vectorOfDestinationIpAddresses);
                            CopyFileWaveClientMessage                   ();
    virtual                ~CopyFileWaveClientMessage                   ();

            string          getSourceFileName                           () const;
            void            setSourceFileName                           (const string &sourceFileName);
            string          getDestinationFileName                      () const;
            void            setDestinationFileName                      (const string &destinationFileName);
            UI32            getCopyFileFlag                             () const;
            void            setCopyFileFlag                             (const UI32 &copyFileFlag);
            vector<string>  getVectorOfDestinationIpAddressesAndPorts   () const;
            void            setVectorOfDestinationIpAddressesAndPorts   (const vector<string> &vectorOfDestinationIpAddressesAndPorts);


    // Now the data members

    private :
        string              m_sourceFileName;
        string              m_destinationFileName;
        UI32                m_copyFileFlag;
        vector<string>      m_vectorOfDestinationIpAddressesAndPorts;


    protected :
    public :
};

class CopyFileToHaPeerWaveClientMessage : public ManagementInterfaceMessage
{
    private :
            void            setupAttributesForSerialization             ();

    protected :
    public :
                            CopyFileToHaPeerWaveClientMessage           (const string &sourceFileName, const string &destinationFileName);
                            CopyFileToHaPeerWaveClientMessage           ();
    virtual                ~CopyFileToHaPeerWaveClientMessage           ();

            string          getSourceFileName                           () const;
            void            setSourceFileName                           (const string &sourceFileName);
            string          getDestinationFileName                      () const;
            void            setDestinationFileName                      (const string &destinationFileName);

    // Now the data members

    private :
        string              m_sourceFileName;
        string              m_destinationFileName;

    protected :
    public :
};

}

#endif // COPYFILEWAVECLIENTMESSAGE_H
