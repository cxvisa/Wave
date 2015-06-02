/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef VERSIONINFORMATION_H
#define VERSIONINFORMATION_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Types/Types.h"
#include <string>

namespace WaveNs
{

class VersionInformation : virtual public SerializableObject
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                            VersionInformation       ();
                           ~VersionInformation       ();

        string              getFirmwareVersion         () const;
        void                setFirmwareVersion         (const string &firmwareVersion);
        UI32                getHaVersion               () const;
        void                setHaVersion               (const UI32 &haVersion);

        void                display                    () const;

    // now the data members

    private :
        string      m_firmwareVersion;
        UI32        m_haVersion;

    protected :
    public :

    friend class PrismFrameworkObjectManagerHaSyncWorker;
};

}

#endif // VERSIONINFORMATION_H
