/******************************************************************************************
 *  @file : DatabaseObjectManagerCalculateDbCksumMessage.h                                *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                               *
 *   All rights reserved.                                                                 *
 *   Description : declares a message DatabaseObjectManagerCalculateDbCksumMessage.       *
                   The handler calculates the checksum for the local database.            *
 *   Author : Pritee Ghosh                                                                *
 *   Date   : 02/22/2011                                                                  *
 ******************************************************************************************/

#ifndef DATABASEOBJECTMANAGERCALCULATEDBCKSUMMESSAGE_H
#define DATABASEOBJECTMANAGERCALCULATEDBCKSUMMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace std;

namespace WaveNs
{

    class DatabaseObjectManagerCalculateDbCksumMessage : public WaveMessage
    { 

        private :
            virtual void    setupAttributesForSerialization                     ();
        protected :
        public :
                            DatabaseObjectManagerCalculateDbCksumMessage        ();
            virtual         ~DatabaseObjectManagerCalculateDbCksumMessage       (); 

            string          getDbCksumForNode                                   () const;
            void            setDbCksumForNode                                   (const string &checksum);

            bool            getPauseTheService                                  () const;
            void            setPauseTheService                                  (bool pauseTheService);

    // Now the data members
        private :
            string          m_checksum;
            bool            m_pauseTheService;
            
    };

}

#endif // DATABASEOBJECTMANAGERCALCULATEDBCKSUMMESSAGE_H
