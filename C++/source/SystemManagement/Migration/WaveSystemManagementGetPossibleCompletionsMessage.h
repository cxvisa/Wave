/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTGETPOSSIBLECOMPLETIONSMESSAGE_H
#define WAVESYSTEMMANAGEMENTGETPOSSIBLECOMPLETIONSMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveSystemManagementGetPossibleCompletionsMessage: public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        WaveSystemManagementGetPossibleCompletionsMessage               ();
        virtual        ~WaveSystemManagementGetPossibleCompletionsMessage               ();

        void                            addCompletionNameAndInfoOneByOne                (const string &completionName, const string &completionInfo);
        void                            addCompletionNameByVector                       (const vector<pair <string, string> > &completionNames);
        vector<pair<string, string> >   getCompletionNameAndInfo                        () const;

        string          getCommandName                                                  () const;
        void            setCommandName                                                  (const string &commandName);
        string          getToken                                                        () const;
        void            setToken                                                        (const string &token);
 
    // Now the Data Members
    private :
        string          m_token;
        string          m_commandName;
        vector<pair<string, string> >  m_completionNameAndInfo;

    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYTARGETNODENAMEMESSAGE_H
