/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef WAVECONFIGURATIONATTRIBUTES_H
#define WAVECONFIGURATIONATTRIBUTES_H

#include "Framework/ObjectModel/SerializableObject.h"
#include "Framework/Types/WaveCValue.h"
#include "Framework/Attributes/Attribute.h"

using namespace WaveNs;

namespace WaveNs
{

class WaveConfigurationAttributes : virtual public SerializableObject
{
    private :
    protected :
                virtual void setupAttributesForSerialization                        ();
                virtual void setupAttributesForSerializationInAttributeOrderFormat  ();
    public :
                        WaveConfigurationAttributes (string configName, string configValue, ResourceId configType);
                        WaveConfigurationAttributes ();
        virtual        ~WaveConfigurationAttributes ();

        string          getConfigName               ();
        string          getConfigValue              ();
        ResourceId      getConfigType               ();
        void            loadWaveConfiguration       (const string &globalConfig);
        void            getAttributeValue           (const ResourceId attributeType, const string attributeValue, WaveCValue *pCValue);

    static void         getConfigurationVectors     (vector<WaveConfigurationAttributes> &configAttributes, vector<string> &configNames, vector<string> &configValues, vector<ResourceId> &configTypes);   
    // Now the data members
    private :   
    protected :
                string      m_configName;
                string      m_configValue;
                ResourceId  m_configAttributeType;
    public :

};

}

#endif // WAVECONFIGURATIONATTRIBUTES_H
