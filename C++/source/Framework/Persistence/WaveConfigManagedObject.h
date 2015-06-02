/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef WAVECONFIGMANAGEDOBJECT_H
#define WAVECONFIGMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Persistence/WaveConfigurationAttributes.h"

using namespace WaveNs;

namespace WaveNs
{

class WaveConfigManagedObject : virtual public WaveConfigurationAttributes, public WaveManagedObject
{
    private :
                void    setupAttributesForPersistence ();
                void    setupAttributesForCreate      ();

    protected :
    public :
                        WaveConfigManagedObject (WaveObjectManager *pWaveObjectManager);
                        WaveConfigManagedObject ();
        virtual        ~WaveConfigManagedObject ();

        static  string  getClassName        ();

        void            setConfigName           (const string &configName);
        string          getConfigName           () const;

        void            setConfigValue          (const string &configValue);
        string          getConfigValue          () const;

        void            setConfigAttributeType  (const ResourceId &configAttributeType);
        ResourceId      getConfigAttributeType  () const;

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVECONFIGMANAGEDOBJECT_H
