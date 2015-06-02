/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACECLIENTTESTMESSAGES_H
#define MANAGEMENTINTERFACECLIENTTESTMESSAGES_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class ManagementInterfaceClientTestMessage1 : public ManagementInterfaceMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 ManagementInterfaceClientTestMessage1 ();
        virtual ~ManagementInterfaceClientTestMessage1 ();

    // now the data members

    private :
    protected :
    public :
};

class ManagementInterfaceClientTestMessage2 : public ManagementInterfaceMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 ManagementInterfaceClientTestMessage2 ();
        virtual ~ManagementInterfaceClientTestMessage2 ();

    // now the data members

    private :
    protected :
    public :
};

class ManagementInterfaceClientTestMessage3 : public ManagementInterfaceMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 ManagementInterfaceClientTestMessage3 ();
        virtual ~ManagementInterfaceClientTestMessage3 ();

    // now the data members

    private :
    protected :
    public :
};

class ManagementInterfaceClientTestMessage4 : public ManagementInterfaceMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                 ManagementInterfaceClientTestMessage4 ();
        virtual ~ManagementInterfaceClientTestMessage4 ();
                void   setupInputBuffer1            ();
                void   setupOutputBuffer1           ();
                bool   validateInputBuffer1         ();
                bool   validateOutputBuffer1        ();
                void   setInputLargeBuffer1         ();
                bool   validateInputLargeBuffer1    ();

                void        setCompletionStatusType      (const UI32 &completionStatusType);
                ResourceId  getRequestedCompletionStatus ();
    // Now the data members

    private :
        bool m_isLargInputBuffer1Set;
        UI32 m_completionStatusType;

    protected :
    public :
};

}

#endif // MANAGEMENTINTERFACECLIENTTESTMESSAGES_H
