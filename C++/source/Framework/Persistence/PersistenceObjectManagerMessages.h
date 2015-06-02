/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERMESSAGES_H
#define PERSISTENCEOBJECTMANAGERMESSAGES_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerAddXPathStringsMessage : public ManagementInterfaceMessage
{
    private:
                void                        setupAttributesForSerialization                             ();
    protected :
    public :
                                            PersistenceObjectManagerAddXPathStringsMessage              (const vector<string> &xPathStrings);
                                            PersistenceObjectManagerAddXPathStringsMessage              ();
        virtual                            ~PersistenceObjectManagerAddXPathStringsMessage              ();

                vector<string>              getXPathStrings                                             () const;
                void                        setXPathStrings                                             (const vector<string> &xPathStrings);

    // Now the data members

    private :
        vector<string>              m_xPathStrings;

    protected :
    public :
};

class PersistenceObjectManagerDeleteXPathStringsMessage : public ManagementInterfaceMessage
{
    private:
                void                        setupAttributesForSerialization                             ();
    protected :
    public :
                                            PersistenceObjectManagerDeleteXPathStringsMessage           (const vector<string> &xPathStrings);
                                            PersistenceObjectManagerDeleteXPathStringsMessage           ();
        virtual                            ~PersistenceObjectManagerDeleteXPathStringsMessage           ();

                vector<string>              getXPathStrings                                             () const;
                void                        setXPathStrings                                             (const vector<string> &xPathStrings);

    // Now the data members

    private :
        vector<string>              m_xPathStrings;

    protected :
    public :
};

class PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage : public ManagementInterfaceMessage
{
    private:
                void                        setupAttributesForSerialization                                        ();
    protected :
    public :
                                            PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage  (const vector<string> &xPathStrings);
                                            PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage  ();
        virtual                            ~PersistenceObjectManagerGetLastUpdateTimestampsForXPathStringsMessage  ();

                vector<string>              getXPathStrings                                                        () const;
                void                        setXPathStrings                                                        (const vector<string> &xPathStrings);

                vector<UI64>                getLastUpdatedTimestamps                                               () const;
                void                        setLastUpdatedTimestamps                                               (const vector<UI64> &lastUpdatedTimestamps);

    // Now the data members

    private :
        vector<string>              m_xPathStrings;
        vector<UI64>                m_lastUpdatedTimestamps;

    protected :
    public :
};

class PersistenceObjectManagerResetXPathStringsTimestampsMessage : public ManagementInterfaceMessage
{
    private:
                void            setupAttributesForSerialization                              ();
    protected :
    public :
                                PersistenceObjectManagerResetXPathStringsTimestampsMessage   ();
        virtual                ~PersistenceObjectManagerResetXPathStringsTimestampsMessage   ();

    // Now the data members

    private :

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGERMESSAGES_H
