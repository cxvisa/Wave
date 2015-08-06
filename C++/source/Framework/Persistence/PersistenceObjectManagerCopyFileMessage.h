/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERCOPYFILEMESSAGE_H
#define PERSISTENCEOBJECTMANAGERCOPYFILEMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerCopyFileMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceObjectManagerCopyFileMessage (const ResourceId &startupFileType, const string &startupFileName = "", const bool &isLocalFileCopy = false);
                        PersistenceObjectManagerCopyFileMessage ();
        virtual        ~PersistenceObjectManagerCopyFileMessage ();

                void        setStartupFileName                     (const string &startupFileName);
                string      getStartupFileName                     () const;
                void        setStartupFileType                     (const ResourceId &startupFileType);
                ResourceId  getStartupFileType                     () const;
                bool        getIsLocalFileCopy                     () const;
                void        setIsLocalFileCopy                     (const bool &isLocalFileCopy);

    // Now the data members

    private :
        ResourceId  m_startupFileType;
        string      m_startupFileName;
        bool        m_isLocalFileCopy;

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGERCOPYFILEMESSAGE_H
