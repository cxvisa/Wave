/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef COMMANDLINEINTERFACEMESSAGE_H
#define COMMANDLINEINTERFACEMESSAGE_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class CommandLineInterfaceMessage : public SerializableObject
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                                          CommandLineInterfaceMessage           ();
                                                          CommandLineInterfaceMessage           (const WaveCommandLineInterfaceOperation &commandLineInterfaceOperation, const ResourceId &operationCode);
        virtual                                          ~CommandLineInterfaceMessage           ();

                UI32                                     getMessageIdentifier                   () const;
                void                                     setMessageIdentifier                   (const UI32 &messageIdentifier);

                WaveCommandLineInterfaceOperation        getCommandLineInterfaceOperation       () const;
                void                                     setCommandLineInterfaceOperation       (const WaveCommandLineInterfaceOperation &commandLineInterfaceOperation);

                ResourceId                               getOperationcode                       () const;
                void                                     setOperationcode                       (const ResourceId &operationCode);

                vector<string>                          &getInput                               ();
                void                                     addToInput                             (const string &additionalInput);

                string                                   getTtyName                             () const;
                void                                     setTtyName                             (const string &ttyName);

                WaveCommandLineInterfaceOperationStatus  getCommandLineInterfaceOperationStatus () const;
                void                                     setCommandLineInterfaceOperationStatus (const WaveCommandLineInterfaceOperationStatus &commandLineInterfaceOperationStatus);

                vector<string>                          &getOutput                              ();
                void                                     addToOutput                            (const string &additionalOutput);

                bool                                     getIsLastResponse                      () const;
                void                                     setIsLastResponse                      (const bool &isLastResponse);

                string 									getErrorString() const;
                void 									setErrorString(const string &errorString);

                bool									getIsWyserEaCompatibilityMode() const;
                void 									setIsWyserEaCompatibilityMode(const bool &isWyserEaCompatibilityMode);


    // Now the data members

    private :
        UI32                                    m_messageIdentifier;
        WaveCommandLineInterfaceOperation       m_commandLineInterfaceOperation;
        ResourceId                              m_operationCode;
        vector<string>                          m_input;
        string                                  m_ttyName;
        WaveCommandLineInterfaceOperationStatus m_commandLineInterfaceOperationStatus;
        vector<string>                          m_output;
        bool                                    m_isLastResponse;
        string 									m_errorString;
        bool 									m_isWyserEaCompatibilityMode;

    protected :
    public :
};

}

#endif // COMMANDLINEINTERFACEMESSAGE_H
