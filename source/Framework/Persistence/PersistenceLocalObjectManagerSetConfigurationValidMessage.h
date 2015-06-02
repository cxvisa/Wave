/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERSETCONFIGURATIONVALIDMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERSETCONFIGURATIONVALIDMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerSetConfigurationValidMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerSetConfigurationValidMessage (const bool &validity, const string &schemaFileName = "");
                        PersistenceLocalObjectManagerSetConfigurationValidMessage ();
        virtual        ~PersistenceLocalObjectManagerSetConfigurationValidMessage ();

                void    setConfigurationValidity                          (const bool &validity);
                bool    getConfigurationValidity                          () const;

                void    setSchemaFile                                     (const string &schemaFileName);
                string  getSchemaFile                                     () const;
    // Now the data members

    private :
        bool            m_isConfigurationValid;
        string          m_schemaFile;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERSETCONFIGURATIONVALIDMESSAGE_H
