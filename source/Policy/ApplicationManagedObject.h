/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONMANAGEDOBJECT_H
#define APPLICATIONMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Types/UI32Range.h"
#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "Framework/Types/Uri.h"
#include "Policy/NBAR2/Nbar2Protocol.h"
#include "Policy/PfrThresholdManagedObject.h"

namespace WaveNs
{

class PolicyObjectManager;

class ApplicationManagedObject : public WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence    ();
        virtual void setupAttributesForCreate         ();

        virtual void getAttributeNamesForJson         (vector<string> &attributeNamesForJson,      const WaveManagedObjectShowType &showType = WAVE_MANAGED_OBJECT_SHOW_ALL);
        virtual void getJsonNames                     (vector<string> &jsonNames,                  const WaveManagedObjectShowType &showType = WAVE_MANAGED_OBJECT_SHOW_ALL);
        virtual void getManagedObjectClassNameForJson (string         &managedObjectClassNameForJson) const;

    protected :
    public :
                                           ApplicationManagedObject       (PolicyObjectManager *pPolicyObjectManager);
        virtual                           ~ApplicationManagedObject       ();

        static  string                     getClassName                   ();

                string                     getApplicationGroup            () const;
                void                       setApplicationGroup            (const string &applicationGroup);

                ObjectId                   getCategoryObjectId            () const;
                void                       setCategoryObjectId            (const ObjectId &categoryObjectId);

                ObjectId                   getSubCategoryObjectId         () const;
                void                       setSubCategoryObjectId         (const ObjectId &subCategoryObjctId);

                string                     getEncrypted                   () const;
                void                       setEncrypted                   (const string &encrypted);

                string                     getP2pTechnology               () const;
                void                       setP2pTechnology               (const string &p2pTechnology);

                string                     getTunnel                      () const;
                void                       setTunnel                      (const string &tunnel);

                bool                       getEnabled                     () const;
                void                       setEnabled                     (const bool &enabled);

                UI64                       getNbarId                      () const;
                void                       setNbarId                      (const UI64 &nbarId);

                UI64                       getEngineId                    () const;
                void                       setEngineId                    (const UI64 &engineId);

                string                     getGlobalId                    () const;
                void                       setGlobalId                    (const string &globalId);

                UI64                       getSelectorId                  () const;
                void                       setSelectorId                  (const UI64 &selectorId);

                string                     getHelp                        () const;
                void                       setHelp                        (const string &help);

                string                     getLongDescription             () const;
                void                       setLongDescription             (const string &longdescription);

                string                     getApplicationProtocol         () const;
                void                       setApplicationProtocol         (const string &applicationProtocol);

                UI32Range                  getTcpPorts                    () const;
                void                       setTcpPorts                    (const UI32Range &tcpPorts);

                UI32Range                  getUdpPorts                    () const;
                void                       setUdpPorts                    (const UI32Range &udpPorts);

                UI32Range                  getIpPorts                     () const;
                void                       setIpPorts                     (const UI32Range &ipPorts);

                string                     getReferencesText              () const;
                void                       setReferencesText              (const string &referencesText);

                Uri                        getUrl                         () const;
                void                       setUrl                         (const Uri &url);

                string                     getTransportIps                () const;
                void                       setTransportIps                (const string &transportIps);

                bool                       getIsRepresentativeApplication () const;
                void                       setIsRepresentativeApplication (const bool &isRepresentativeApplication);

                string                     getDscp                        () const;
                void                       setDscp                        (const string &dscp);

                bool                       getIsCustomApplication         () const;
                void                       setIsCustomApplication         (const bool &isCustomApplication);

                UI64                       getPopularity                  () const;
                void                       setPopularity                  (const UI64 &popularity);

                UI32Range                  getIndicativeTcpPorts          () const;
                void                       setIndicativeTcpPorts          (const UI32Range &indicativeTcpPorts);

                UI32Range                  getIndicativeUdpPorts          () const;
                void                       setIndicativeUdpPorts          (const UI32Range &indicativeUdpPorts);

                UI32Range                  getIndicativeIpPorts           () const;
                void                       setIndicativeIpPorts           (const UI32Range &indicativeIpPorts);

                string                     getStatus                      () const;
                void                       setStatus                      (const string &status);

                string                     getGroupId                     () const;
                void                       setGroupId                     (const string &groupId);

                PfrThresholdManagedObject *getPfrThresholds               ();
                void                       setPfrThresholds               (PfrThresholdManagedObject *pPfrThresholdManagedObject);

                void                       loadFromNbar2Protocol          (const Nbar2Protocol &nbar2Protocol);

        // Now the data members

    private :
        string                                              m_applicationGroup;
        ObjectId                                            m_categoryObjectId;
        ObjectId                                            m_subCategoryObjectId;
        string                                              m_encrypted;
        string                                              m_p2pTechnology;
        string                                              m_tunnel;
        bool                                                m_enabled;
        UI64                                                m_nbarId;
        UI64                                                m_engineId;
        string                                              m_globalId;
        UI64                                                m_selectorId;
        string                                              m_help;
        string                                              m_longDescription;
        string                                              m_applicationProtocol;
        UI32Range                                           m_tcpPorts;
        UI32Range                                           m_udpPorts;
        UI32Range                                           m_ipPorts;
        string                                              m_referencesText;
        Uri                                                 m_url;
        string                                              m_transportIps;
        bool                                                m_isRepresentativeApplication;
        string                                              m_dscp;
        bool                                                m_isCustomApplication;
        UI64                                                m_popularity;
        UI32Range                                           m_indicativeTcpPorts;
        UI32Range                                           m_indicativeUdpPorts;
        UI32Range                                           m_indicativeIpPorts;
        string                                              m_status;
        string                                              m_groupId;
        WaveManagedObjectPointer<PfrThresholdManagedObject> m_pfrThresholds;

    protected :
    public :
};

}

#endif // APPLICATIONMANAGEDOBJECT_H
