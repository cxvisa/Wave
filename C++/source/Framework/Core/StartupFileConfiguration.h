/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef STARTUPFILECONFIGURATION_H
#define STARTUPFILECONFIGURATION_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Types/Types.h"
#include <vector>
#include <string>

namespace WaveNs
{

class StartupFileConfiguration : virtual public SerializableObject
{
    private :
    protected :
        virtual void setupAttributesForSerialization                        ();
        virtual void setupAttributesForSerializationInAttributeOrderFormat  ();

    public :
                            StartupFileConfiguration    ();
                           ~StartupFileConfiguration    ();

        UI32                getVersion                 () const;
        void                setVersion                 (const UI32 &version);
        UI32                getStartupFileType         () const;
        void                setStartupFileType         (const UI32 &startupFileType);
        string              getStartupFileName         () const;
        void                setStartupFileName         (const string &startupFileName);
        string              getStartupFile             () const;
        void                setStartupFile             (const string &startupFile);

        void                display                    () const;

    // now the data members

    private :
        UI32        m_version;
        UI32        m_startupFileType;
        string      m_startupFileName;
        string      m_startupFile;

    protected :
    public :

    friend class WaveFrameworkObjectManagerHaSyncWorker;
};

}

#endif // STARTUPFILECONFIGURATION_H
