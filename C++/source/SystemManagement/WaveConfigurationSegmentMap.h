/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECONFIGURATIONSEGMENTMAP_H
#define WAVECONFIGURATIONSEGMENTMAP_H

#include "Framework/Utils/WaveMutex.h"

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContextBase.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

typedef void (*ConfigurationSegmentQueryContextModificationFunction)      (WaveElement *pWaveElement, WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);
typedef bool (*ConfigurationSegmentQueryContextModificationFunction2)     (WaveElement *pWaveElement, WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);

class WaveClientSynchronousConnection;

class ConfigurationSegmentInformation
{
    private:
    protected:
    public:
                                        ConfigurationSegmentInformation                     (const string &managedObjectClassName, WaveElement *pWaveElement);
                                       ~ConfigurationSegmentInformation                     ();
                        string          getManagedObjectClassName                           () const;

                        void            setParameters                                       (const bool &isSingleton, const bool &nodeSpecificSupported, const bool &partitionSupported);
                        bool            getIsSingleton                                      () const;
                        bool            getIsNodeSpecificSupported                          () const;
                        bool            getPartitionSupported                               () const;

                        void            setParentInformation                                (const vector<string> &parentClassNames, const vector<bool> &parentIsSingletonFlags, const vector<bool> &parentIsSkippedForDisplay);

                        void            setIsLocalManagedObject                             (const bool &isLocalManagedObject);
                        bool            getIsLocalManagedObject                             () const;

                        void            debugPrint                                          () const;

                        UI32            getNumberOfManagedObjectClassNamesInOrmHierarchy    () const;
                        bool            getParentIsSingletonAtIndex                         (const UI32 &index) const;
                        string          getParentManagedObjectClassNameAtIndex              (const UI32 &index) const;

                        void            applySetNTupleSortingFunction                       (WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);
                        void            applyCustomQueryFilterFunction                      (WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);
                        bool            applyAddCustomOrderFieldFunction                    (WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);

            const       vector<string> &getUserDefinedKeyCombination                        () const;
                        AttributeType   getAttributeTypeForAttributeInKeyCombination        (const string &keyString) const;

                        Attribute*      getClonedAttributeForKey                            (const string &keyString) const;

    // Now the data members

    private :
            string                      m_managedObjectClassName;
            WaveElement               *m_pWaveElement;
            bool                        m_isSingleton;
            bool                        m_nodeSpecificSupported;
            bool                        m_partitionSupported;
            vector<string>              m_parentManagedObjectClassNames;
            vector<bool>                m_parentIsSingletonFlags;
            vector<bool>                m_parentIsSkippedForDisplay;
            vector<string>              m_userDefinedKeyCombination;
            map<string, Attribute *>    m_userDefinedKeyCombinationToPAttributeMap;
            bool                        m_isLocalManagedObject;                         // Cached from OrmRepository.
};

class ConfigurationSegmentImportantInfo 
{
    private :
    protected :
    public :
                                        ConfigurationSegmentImportantInfo (const string &configurationSegmentName, const string &managedObjectName, const string &serverName, WaveClientSynchronousConnection *pWaveClientSynchronousConnection);
                                       ~ConfigurationSegmentImportantInfo                   ();

            string                      getConfigurationSegmentName                         () const;
            void                        setConfigurationSegmentName                         (const string &configurationSegmentName);

            string                      getManagedObjectName                                () const;
            void                        setManagedObjectName                                (const string &managedObjectName);
            
            string                      getServerName                                       () const;
            void                        setServerName                                       (const string &serverName);

            WaveClientSynchronousConnection*    getWaveClientSynchronousConnection          () const;
            void                                setWaveClientSynchronousConnection          (WaveClientSynchronousConnection *pWaveClientSynchronousConnection);

    // Data Members
    private :
            string                              m_configurationSegmentName;
            string                              m_managedObjectName;
            string                              m_serverName;
            WaveClientSynchronousConnection    *m_pWaveClientSynchronousConnection;
    protected :
    public :
};


class WaveConfigurationSegmentMap
{
    private :
    protected :
    public :
        static bool   isAKnownConfigurationSegmentName                          (const string &configurationSegmentName);
        static void   addConfigurationSegmentInformation                        (const string &configurationSegmentName, const string &managedObjectClassName, WaveElement *pWaveElement = NULL);
        static string getManagedObjectClassNameByConfigurationSegmentName       (const string &configurationSegmentName);
        static void   getAllConfigurationSegmentNamesAndManagedObjectClassNames (vector<string> &configurationSegmentNames, vector<string> &managedObjectClassNames);

        static void   print                                               ();

        static void                             updateConfigurationSegmentHierarchyInformation  (const string &configurationSegmentName, const vector<string> &parentClassNames, const vector<bool> &parentIsSingletonFlags, const vector<bool> &parentIsSkippedForDisplay);
        static void                             updateConfigurationSegmentParameterInformation  (const string &configurationSegmentName, const bool &isSingleton, const bool &nodeSpecificSupported, const bool &partitionSupported);
        static ConfigurationSegmentInformation *getPConfigurationSegmentInformation             (const string &configurationSegmentName);

        static void                             registerSetNTupleSortingFunction                (ConfigurationSegmentQueryContextModificationFunction setNTupleSortingFunction);
        static void                             registerCustomQueryFilterFunction               (ConfigurationSegmentQueryContextModificationFunction customQueryFilterFunction);
        static void                             registerAddCustomOrderFieldFunction             (ConfigurationSegmentQueryContextModificationFunction2 addCustomOrderFieldFunction);
        static void                             applySetNTupleSortingFunction                   (WaveElement *pWaveElement, WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);
        static void                             applyCustomQueryFilterFunction                  (WaveElement *pWaveElement, WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);
        static bool                             applyAddCustomOrderFieldFunction                (WaveElement *pWaveElement, WaveManagedObjectQueryContextBase &waveManagedObjectQueryContextBase);

        static void                             setConfigurationSegmentNameForNodeSpecificList      (const string &configurationSegmentNameForNodeSpecificList);
        static void                             setConfigurationSegmentNameForMultiPartitionList    (const string &configurationSegmentNameForMultiPartitionList);
        static void                             cacheManagedObjectClassNameForNodeSpecificList      ();
        static void                             cacheManagedObjectClassNameForMultiPartitionList    ();

        static string                           getManagedObjectClassNameForNodeSpecificList        ();
        static string                           getManagedObjectClassNameForMultiPartitionList      ();
        
        static void                             addToConfigSegmentImportantInfoMap                  (const string &configurationSegmentName, const string &managedObjectName, const string &serverName, WaveClientSynchronousConnection *pWaveClientSynchronousConnection);

        static ConfigurationSegmentImportantInfo *  getConfigurationSegmentImportantInfoFromMap     (const string &configurationSegmentName);

        static void                             cacheIsLocalManagedObjectInformation                ();

    // Now the data members

    private :
        static map<string, ConfigurationSegmentInformation *>           m_configurationSegmentMap;
        static WaveMutex                                               m_configurationSegmentMapMutex;

        static ConfigurationSegmentQueryContextModificationFunction     s_setNTupleSortingFunction;
        static ConfigurationSegmentQueryContextModificationFunction     s_customQueryFilterFunction;
        static ConfigurationSegmentQueryContextModificationFunction2    s_addCustomOrderFieldFunction;
        static WaveMutex                                               s_queryContextModificationFunctionsMutex;

        // cache.
        static string                                                   s_configurationSegmentForNodeSpecificList;
        static string                                                   s_configurationSegmentForMultiPartitionList;
        static string                                                   s_managedObjectClassNameForNodeSpecificList;
        static string                                                   s_managedObjectClassNameForMultiPartitionList;
        
        static map<string, ConfigurationSegmentImportantInfo *>         m_configSegmentImportantInfoMap; // Configuration Segment Name --> ConfigurationSegmentImportantInfo *
        static WaveMutex                                               m_configSegmentImportantInfoMapMutex;

    protected :
    public :
};



}

#endif // WAVECONFIGURATIONSEGMENTMAP_H
