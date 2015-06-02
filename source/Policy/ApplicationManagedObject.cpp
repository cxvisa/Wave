/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/ApplicationManagedObject.h"
#include "Framework/Attributes/Attributes.h"
#include "Framework/Attributes/AttributeUI32Range.h"
#include "Framework/Attributes/AttributeManagedObjectComposition.cpp"
#include "Framework/Attributes/AttributeUri.h"
#include "Policy/CategoryManagedObject.h"
#include "Policy/CategoryManagedObject.h"
#include "Policy/PolicyObjectManager.h"
#include "Policy/SubCategoryManagedObject.h"
#include "Policy/SubCategoryManagedObject.h"
#include "Policy/NBAR2/Nbar2ProtocolPorts.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

ApplicationManagedObject::ApplicationManagedObject (PolicyObjectManager *pPolicyObjectManager)
    : PrismElement (pPolicyObjectManager),
      PrismPersistableObject (ApplicationManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pPolicyObjectManager)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

ApplicationManagedObject::~ApplicationManagedObject ()
{
}

string ApplicationManagedObject::getClassName ()
{
    return ("ApplicationManagedObject");
}

void ApplicationManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeString                                              (&m_applicationGroup,            "applicationGroup"));
    addPersistableAttribute (new AttributeObjectIdAssociation                                 (&m_categoryObjectId,            "categoryObjectId",    CategoryManagedObject::getClassName (), true));
    addPersistableAttribute (new AttributeObjectIdAssociation                                 (&m_subCategoryObjectId,         "subCategoryObjectId", SubCategoryManagedObject::getClassName (), true));
    addPersistableAttribute (new AttributeString                                              (&m_encrypted,                   "encrypted"));
    addPersistableAttribute (new AttributeString                                              (&m_p2pTechnology,               "p2pTechnology"));
    addPersistableAttribute (new AttributeString                                              (&m_tunnel,                      "tunnel"));
    addPersistableAttribute (new AttributeBool                                                (&m_enabled,                     "enabled"));
    addPersistableAttribute (new AttributeUI64                                                (&m_nbarId,                      "nbarId"));
    addPersistableAttribute (new AttributeUI64                                                (&m_engineId,                    "engineId"));
    addPersistableAttribute (new AttributeString                                              (&m_globalId,                    "globalId"));
    addPersistableAttribute (new AttributeUI64                                                (&m_selectorId,                  "selectorId"));
    addPersistableAttribute (new AttributeString                                              (&m_help,                        "help"));
    addPersistableAttribute (new AttributeString                                              (&m_longDescription,             "longDescription"));
    addPersistableAttribute (new AttributeString                                              (&m_applicationProtocol,         "applicationProtocol"));
    addPersistableAttribute (new AttributeUI32Range                                           (&m_tcpPorts,                    "tcpPorts"));
    addPersistableAttribute (new AttributeUI32Range                                           (&m_udpPorts,                    "udpPorts"));
    addPersistableAttribute (new AttributeUI32Range                                           (&m_ipPorts,                     "ipPorts"));
    addPersistableAttribute (new AttributeString                                              (&m_referencesText,              "referencesText"));
    addPersistableAttribute (new AttributeUri                                                 (&m_url,                         "url"));
    addPersistableAttribute (new AttributeString                                              (&m_transportIps,                "transportIps"));
    addPersistableAttribute (new AttributeBool                                                (&m_isRepresentativeApplication, "isRepresentativeApplication"));
    addPersistableAttribute (new AttributeString                                              (&m_dscp,                        "dscp"));
    addPersistableAttribute (new AttributeBool                                                (&m_isCustomApplication,         "isCustomApplication"));
    addPersistableAttribute (new AttributeUI64                                                (&m_popularity,                  "popularity"));
    addPersistableAttribute (new AttributeUI32Range                                           (&m_indicativeTcpPorts,          "indicativeTcpPorts"));
    addPersistableAttribute (new AttributeUI32Range                                           (&m_indicativeUdpPorts,          "indicativeUdpPorts"));
    addPersistableAttribute (new AttributeUI32Range                                           (&m_indicativeIpPorts,           "indicativeIpPorts"));
    addPersistableAttribute (new AttributeString                                              (&m_status,                      "status"));
    addPersistableAttribute (new AttributeString                                              (&m_groupId,                     "groupId"));
    addPersistableAttribute (new AttributeManagedObjectComposition<PfrThresholdManagedObject> (&m_pfrThresholds,               "pfrThresholds",      PfrThresholdManagedObject::getClassName (), true));
}

void ApplicationManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeString                                              (&m_applicationGroup,            "applicationGroup"));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation                                 (&m_categoryObjectId,            "categoryObjectId",    CategoryManagedObject::getClassName (), true));
    addPersistableAttributeForCreate (new AttributeObjectIdAssociation                                 (&m_subCategoryObjectId,         "subCategoryObjectId", SubCategoryManagedObject::getClassName (), true));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_encrypted,                   "encrypted"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_p2pTechnology,               "p2pTechnology"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_tunnel,                      "tunnel"));
    addPersistableAttributeForCreate (new AttributeBool                                                (&m_enabled,                     "enabled"));
    addPersistableAttributeForCreate (new AttributeUI64                                                (&m_nbarId,                      "nbarId"));
    addPersistableAttributeForCreate (new AttributeUI64                                                (&m_engineId,                    "engineId"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_globalId,                    "globalId"));
    addPersistableAttributeForCreate (new AttributeUI64                                                (&m_selectorId,                  "selectorId"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_help,                        "help"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_longDescription,             "longDescription"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_applicationProtocol,         "applicationProtocol"));
    addPersistableAttributeForCreate (new AttributeUI32Range                                           (&m_tcpPorts,                    "tcpPorts"));
    addPersistableAttributeForCreate (new AttributeUI32Range                                           (&m_udpPorts,                    "udpPorts"));
    addPersistableAttributeForCreate (new AttributeUI32Range                                           (&m_ipPorts,                     "ipPorts"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_referencesText,              "referencesText"));
    addPersistableAttributeForCreate (new AttributeUri                                                 (&m_url,                         "url"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_transportIps,                "transportIps"));
    addPersistableAttributeForCreate (new AttributeBool                                                (&m_isRepresentativeApplication, "isRepresentativeApplication"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_dscp,                        "dscp"));
    addPersistableAttributeForCreate (new AttributeBool                                                (&m_isCustomApplication,         "isCustomApplication"));
    addPersistableAttributeForCreate (new AttributeUI64                                                (&m_popularity,                  "popularity"));
    addPersistableAttributeForCreate (new AttributeUI32Range                                           (&m_indicativeTcpPorts,          "indicativeTcpPorts"));
    addPersistableAttributeForCreate (new AttributeUI32Range                                           (&m_indicativeUdpPorts,          "indicativeUdpPorts"));
    addPersistableAttributeForCreate (new AttributeUI32Range                                           (&m_indicativeIpPorts,           "indicativeIpPorts"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_status,                      "status"));
    addPersistableAttributeForCreate (new AttributeString                                              (&m_groupId,                     "groupId"));
    addPersistableAttributeForCreate (new AttributeManagedObjectComposition<PfrThresholdManagedObject> (&m_pfrThresholds,               "pfrThresholds",      PfrThresholdManagedObject::getClassName (), true));
}

string ApplicationManagedObject::getApplicationGroup () const
{
    return (m_applicationGroup);
}

void ApplicationManagedObject::setApplicationGroup (const string &applicationGroup)
{
    m_applicationGroup = applicationGroup;
}

ObjectId ApplicationManagedObject::getCategoryObjectId () const
{
    return (m_categoryObjectId);
}

void ApplicationManagedObject::setCategoryObjectId (const ObjectId &categoryObjectId)
{
    m_categoryObjectId = categoryObjectId;
}

ObjectId ApplicationManagedObject::getSubCategoryObjectId () const
{
    return (m_subCategoryObjectId);
}

void ApplicationManagedObject::setSubCategoryObjectId (const ObjectId &subCategoryObjctId)
{
    m_subCategoryObjectId = subCategoryObjctId;
}

string ApplicationManagedObject::getEncrypted () const
{
    return (m_encrypted);
}

void ApplicationManagedObject::setEncrypted (const string &encrypted)
{
    m_encrypted = encrypted;
}

string ApplicationManagedObject::getP2pTechnology () const
{
    return (m_p2pTechnology);
}

void ApplicationManagedObject::setP2pTechnology (const string &p2pTechnology)
{
    m_p2pTechnology = p2pTechnology;
}

string ApplicationManagedObject::getTunnel () const
{
    return (m_tunnel);
}

void ApplicationManagedObject::setTunnel (const string &tunnel)
{
    m_tunnel = tunnel;
}

bool ApplicationManagedObject::getEnabled () const
{
    return (m_enabled);
}

void ApplicationManagedObject::setEnabled (const bool &enabled)
{
    m_enabled = enabled;
}

UI64 ApplicationManagedObject::getNbarId () const
{
    return (m_nbarId);
}

void ApplicationManagedObject::setNbarId (const UI64 &nbarId)
{
    m_nbarId = nbarId;
}

UI64 ApplicationManagedObject::getEngineId () const
{
    return (m_engineId);
}

void ApplicationManagedObject::setEngineId (const UI64 &engineId)
{
    m_engineId = engineId;
}

string ApplicationManagedObject::getGlobalId () const
{
    return (m_globalId);
}

void ApplicationManagedObject::setGlobalId (const string &globalId)
{
    m_globalId = globalId;
}

UI64 ApplicationManagedObject::getSelectorId () const
{
    return (m_selectorId);
}

void ApplicationManagedObject::setSelectorId (const UI64 &selectorId)
{
    m_selectorId = selectorId;
}

string ApplicationManagedObject::getHelp () const
{
    return (m_help);
}

void ApplicationManagedObject::setHelp (const string &help)
{
    m_help = help;
}

string ApplicationManagedObject::getLongDescription () const
{
    return (m_longDescription);
}

void ApplicationManagedObject::setLongDescription (const string &longdescription)
{
    m_longDescription = longdescription;
}

string ApplicationManagedObject::getApplicationProtocol () const
{
    return (m_applicationProtocol);
}

void ApplicationManagedObject::setApplicationProtocol (const string &applicationProtocol)
{
    m_applicationProtocol = applicationProtocol;
}

UI32Range ApplicationManagedObject::getTcpPorts () const
{
    return (m_tcpPorts);
}

void ApplicationManagedObject::setTcpPorts (const UI32Range &tcpPorts)
{
    m_tcpPorts = tcpPorts;
}

UI32Range ApplicationManagedObject::getUdpPorts () const
{
    return (m_udpPorts);
}

void ApplicationManagedObject::setUdpPorts (const UI32Range &udpPorts)
{
    m_udpPorts = udpPorts;
}

UI32Range ApplicationManagedObject::getIpPorts () const
{
    return (m_ipPorts);
}

void ApplicationManagedObject::setIpPorts (const UI32Range &ipPorts)
{
    m_ipPorts = ipPorts;
}

string ApplicationManagedObject::getReferencesText () const
{
    return (m_referencesText);
}

void ApplicationManagedObject::setReferencesText (const string &referencesText)
{
    m_referencesText = referencesText;
}

Uri ApplicationManagedObject::getUrl () const
{
    return (m_url);
}

void ApplicationManagedObject::setUrl (const Uri &url)
{
    m_url = url;
}

string ApplicationManagedObject::getTransportIps () const
{
    return (m_transportIps);
}

void ApplicationManagedObject::setTransportIps (const string &transportIps)
{
    m_transportIps = transportIps;
}

bool ApplicationManagedObject::getIsRepresentativeApplication () const
{
    return (m_isRepresentativeApplication);
}

void ApplicationManagedObject::setIsRepresentativeApplication (const bool &isRepresentativeApplication)
{
    m_isRepresentativeApplication = isRepresentativeApplication;
}

string ApplicationManagedObject::getDscp () const
{
    return (m_dscp);
}

void ApplicationManagedObject::setDscp (const string &dscp)
{
    m_dscp = dscp;
}

bool ApplicationManagedObject::getIsCustomApplication () const
{
    return (m_isCustomApplication);
}

void ApplicationManagedObject::setIsCustomApplication (const bool &isCustomApplication)
{
    m_isCustomApplication = isCustomApplication;
}

UI64 ApplicationManagedObject::getPopularity () const
{
    return (m_popularity);
}

void ApplicationManagedObject::setPopularity (const UI64 &popularity)
{
    m_popularity = popularity;
}

UI32Range ApplicationManagedObject::getIndicativeTcpPorts () const
{
    return (m_indicativeTcpPorts);
}

void ApplicationManagedObject::setIndicativeTcpPorts (const UI32Range &indicativeTcpPorts)
{
    m_indicativeTcpPorts = indicativeTcpPorts;
}

UI32Range ApplicationManagedObject::getIndicativeUdpPorts () const
{
    return (m_indicativeUdpPorts);
}

void ApplicationManagedObject::setIndicativeUdpPorts (const UI32Range &indicativeUdpPorts)
{
    m_indicativeUdpPorts = indicativeUdpPorts;
}

UI32Range ApplicationManagedObject::getIndicativeIpPorts () const
{
    return (m_indicativeIpPorts);
}

void ApplicationManagedObject::setIndicativeIpPorts (const UI32Range &indicativeIpPorts)
{
    m_indicativeIpPorts = indicativeIpPorts;
}

string ApplicationManagedObject::getStatus () const
{
    return (m_status);
}

void ApplicationManagedObject::setStatus (const string &status)
{
    m_status = status;
}

string ApplicationManagedObject::getGroupId () const
{
    return (m_groupId);
}

void ApplicationManagedObject::setGroupId (const string &groupId)
{
    m_groupId = groupId;
}

PfrThresholdManagedObject *ApplicationManagedObject::getPfrThresholds ()
{
    return (m_pfrThresholds.operator -> ());
}

void ApplicationManagedObject::setPfrThresholds (PfrThresholdManagedObject *pPfrThresholdManagedObject)
{
    m_pfrThresholds = WaveManagedObjectPointer<PfrThresholdManagedObject> (pPfrThresholdManagedObject);
}

void ApplicationManagedObject::loadFromNbar2Protocol (const Nbar2Protocol &nbar2Protocol)
{
    setName     (nbar2Protocol.getName ());
    setEnabled  (nbar2Protocol.getEnabled ());
    setEngineId (nbar2Protocol.getEngineId ());
    setGlobalId (nbar2Protocol.getGlobalId ());
    setHelp     (nbar2Protocol.getHelpString ());
    setNbarId   (nbar2Protocol.getId ());

    const Nbar2ProtocolPorts &nbar2ProtocolPorts = nbar2Protocol.getPorts ();

    string tcpPorts             = nbar2ProtocolPorts.getTcp ();
    string udpPorts             = nbar2ProtocolPorts.getUdp ();
    UI64   ip                   = nbar2ProtocolPorts.getIp  ();
    string ipPorts;
    string applicationProtocol;


    if (0 != ip)
    {
        ipPorts = string ("") + ip;
    }

    if ("" != tcpPorts)
    {
        setTcpPorts (UI32Range (tcpPorts));

        applicationProtocol = "tcp/";
    }

    if ("" != udpPorts)
    {
        setUdpPorts (UI32Range (udpPorts));

        applicationProtocol += "udp/";
    }

    if ("" != ipPorts)
    {
        setIpPorts (UI32Range (ipPorts));

        applicationProtocol += "ip/";
    }

    if (0 < (applicationProtocol.length ()))
    {
        applicationProtocol.erase (applicationProtocol.length () - 1, 1);
    }

    setApplicationProtocol (applicationProtocol);

    setLongDescription (nbar2Protocol.getLongDescription ());
    setSelectorId (nbar2Protocol.getSelectorId ());
    setEnabled (nbar2Protocol.getEnabled ());
    setReferencesText (nbar2Protocol.getReferences ());
    setPopularity (nbar2Protocol.getCommonlyUsed ());

    const Nbar2ProtocolIndicativePorts &nbar2ProtocolIndicativePorts = nbar2Protocol.getIndicativePorts ();

    string indicativeTcpPorts             = nbar2ProtocolIndicativePorts.getTcp ();
    string indicativeUdpPorts             = nbar2ProtocolIndicativePorts.getUdp ();
    UI64   indicativeIp                   = nbar2ProtocolIndicativePorts.getIp  ();
    string indicativeIpPorts;

    if ("" != indicativeTcpPorts)
    {
        setIndicativeTcpPorts (UI32Range (indicativeTcpPorts));
    }

    if ("" != indicativeUdpPorts)
    {
        setIndicativeUdpPorts (UI32Range (indicativeUdpPorts));
    }

    if (0 != indicativeIp)
    {
        indicativeIpPorts = string ("") + indicativeIp;
    }

    if ("" != indicativeIpPorts)
    {
        setIndicativeIpPorts (UI32Range (indicativeIpPorts));
    }

    const Nbar2ProtocolAttributes &nbar2ProtocolAttributes = nbar2Protocol.getAttributes ();

    setApplicationGroup (nbar2ProtocolAttributes.getApplicationGroup ());
    setEncrypted        (nbar2ProtocolAttributes.getEncrypted        ());
    setP2pTechnology    (nbar2ProtocolAttributes.getP2pTechnology    ());
    setTunnel           (nbar2ProtocolAttributes.getTunnel           ());
}

void ApplicationManagedObject::getAttributeNamesForJson (vector<string> &attributeNamesForJson, const WaveManagedObjectShowType &showType)
{
    attributeNamesForJson.push_back ("applicationGroup");
    attributeNamesForJson.push_back ("categoryObjectId");
    attributeNamesForJson.push_back ("encrypted");
    attributeNamesForJson.push_back ("p2pTechnology");
    attributeNamesForJson.push_back ("tunnel");
    attributeNamesForJson.push_back ("enabled");
    attributeNamesForJson.push_back ("nbarId");
    attributeNamesForJson.push_back ("engineId");
    attributeNamesForJson.push_back ("globalId");
    attributeNamesForJson.push_back ("selectorId");
    attributeNamesForJson.push_back ("help");
    attributeNamesForJson.push_back ("longDescription");
    attributeNamesForJson.push_back ("referencesText");
    attributeNamesForJson.push_back ("popularity");
    attributeNamesForJson.push_back ("indicativeTcpPorts");
    attributeNamesForJson.push_back ("indicativeUdpPorts");
    attributeNamesForJson.push_back ("pfrThresholds");
    attributeNamesForJson.push_back ("specificStatus");
    attributeNamesForJson.push_back ("objectUuid");
    attributeNamesForJson.push_back ("subCategoryObjectId");
    attributeNamesForJson.push_back ("name");
    attributeNamesForJson.push_back ("applicationProtocol");
    attributeNamesForJson.push_back ("tcpPorts");
    attributeNamesForJson.push_back ("udpPorts");
}

void ApplicationManagedObject::getJsonNames (vector<string> &jsonNames, const WaveManagedObjectShowType &showType)
{
    jsonNames.push_back ("applicationGroup");
    jsonNames.push_back ("categoryObjectId");
    jsonNames.push_back ("encrypted");
    jsonNames.push_back ("p2pTechnology");
    jsonNames.push_back ("tunnel");
    jsonNames.push_back ("enabled");
    jsonNames.push_back ("nbarId");
    jsonNames.push_back ("engineId");
    jsonNames.push_back ("globalId");
    jsonNames.push_back ("selectorId");
    jsonNames.push_back ("helpString");
    jsonNames.push_back ("longDescription");
    jsonNames.push_back ("references");
    jsonNames.push_back ("popularity");
    jsonNames.push_back ("indicativeTcpPorts");
    jsonNames.push_back ("indicativeUdpPorts");
    jsonNames.push_back ("pfrThresholds");
    jsonNames.push_back ("applicationStatus");
    jsonNames.push_back ("id");
    jsonNames.push_back ("subCategoryObjectId");
    jsonNames.push_back ("name");
    jsonNames.push_back ("appProtocol");
    jsonNames.push_back ("tcpPorts");
    jsonNames.push_back ("udpPorts");
}

void ApplicationManagedObject::getManagedObjectClassNameForJson (string &managedObjectClassNameForJson) const
{
    managedObjectClassNameForJson = "application";
}


}
