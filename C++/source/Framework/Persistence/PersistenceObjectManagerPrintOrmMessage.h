/**************************************************************************************
 *  @file : PersistenceObjectManagerPrintOrmMessage.h                                 *
 *   Copyright (C) 2011 Vidyasagara Guntaka                                           *
 *   All rights reserved.                                                             *
 *   Description : Declares a message Persistence OM handled message used to print    *
 *                 ORM repository information.                                        *
 *   Author : Brian Adaniya                                                           *
 *   Date   : 11/07/2011                                                              *
 **************************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERPRINTORMMESSAGE_H
#define PERSISTENCEOBJECTMANAGERPRINTORMMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"


namespace WaveNs
{

class PersistenceObjectManagerPrintOrmMessage : public ManagementInterfaceMessage
{
    private :
                void            setupAttributesForSerialization         ();
    protected :
    public :
                                PersistenceObjectManagerPrintOrmMessage ();
                                PersistenceObjectManagerPrintOrmMessage (const vector<string> &arguments);
        virtual                ~PersistenceObjectManagerPrintOrmMessage ();

        const   vector<string> &getOrmArgs                              () const;

                string          getOrmInfo                              () const;
                void            setOrmInfo                              (const string &ormInfo);

                
            

    // Now the data members
    private :
                vector<string>  m_ormArgs;
                string          m_ormInfo;

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGERPRINTORMMESSAGE_H
