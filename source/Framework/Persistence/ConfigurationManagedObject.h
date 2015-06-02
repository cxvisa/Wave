/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef CONFIGURATIONMANAGEDOBJECT_H
#define CONFIGURATIONMANAGEDOBJECT_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Types/DateTime.h"

#include <vector>

using namespace WaveNs;

namespace WaveNs
{

class ConfigurationManagedObject : public WaveManagedObject
{
    private :
        virtual void             setupAttributesForPersistence ();
        virtual void             setupAttributesForCreate      ();

    protected :
    public :
                                 ConfigurationManagedObject   (WaveObjectManager *pWaveObjectManager);
        virtual                 ~ConfigurationManagedObject   ();

        static string            getClassName               ();

               UI64              getConfigurationNumber      () const;
               DateTime          getConfigurationTime       () const;
               DateTime          getLatestUpdateTime        () const;

               void              setConfigurationNumber     (const UI64 &configurationNumber);
               void              setConfigurationTime       (const DateTime &configurationTime);
               void              setLatestUpdateTime        (const DateTime &latestUpdateTime);
               void              resetConfigurationManagedObject ();
    // Now the data members

    private :
               UI64              m_configurationNumber;
               DateTime          m_configurationTime;
               DateTime          m_latestUpdateTime;

    protected :
    public :
};

class XPathStringManagedObject : public WaveManagedObject
{
    private :
        virtual void                setupAttributesForPersistence       ();
        virtual void                setupAttributesForCreate            ();
        virtual void                setupKeys                           ();

    protected :
    public :
                                    XPathStringManagedObject            (WaveObjectManager *pWaveObjectManager);
        virtual                    ~XPathStringManagedObject            ();

        static  string              getClassName                        ();

                string              getXPathString                      () const;
                void                setXPathString                      (const string &xPathString);

    // Now the  data members

    private :
                string              m_xPathString;

    protected :
    public :
};

}

#endif //CONFIGURATIONMANAGEDOBJECT_H

