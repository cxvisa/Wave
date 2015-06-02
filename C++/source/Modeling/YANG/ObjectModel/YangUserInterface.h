/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGUSERINTERFACE_H
#define YANGUSERINTERFACE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"
#include "Modeling/YANG/ObjectModel/YangDataElement.h"
#include "Modeling/YANG/ObjectModel/YangModuleCollection.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

class YangUserInterface : public YangElement
{
    private :
    protected :
    public :
                                      YangUserInterface                  ();
        virtual                      ~YangUserInterface                  ();

        static  string                getYangName                        ();

        static YangElement           *createInstance                     ();

               void                   initializeFromYangModuleCollection (const YangModuleCollection &yangModuleCollection);

               void                   computeCliTargetNodeNameMapForData ();

               vector<YangElement *>  getYangElementsByTargetNodeName    (const string &targetNodeName);

               vector<YangElement *>  getYangElementsByTargetNodeNameForDropNode    (const string &targetNodeNameForDropNode);

               void                   prepareYangElementTreeForData      ();
               void                   debugPrintYangElementTreeForData   (const string &outputFilePath) const;

               void                   propagateNodeSpecificAndMultiPartitionInformationInDataElementTree    ();
               void                   prepareHierarchyInformationForYangElementsInTreeForData               ();

               void                   printConfiguration                 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext);

               YangElement           *getParentYangModuleForGrandChildYangElementByName     (const string &uniqueYangElementName, const string &namespaceString) const;

               void                   lock                                                  ();
               void                   unlock                                                ();


void    applyAnnotationSupplement   ();

void    applyAddModeAnnotation      ();
void    applyCompactElemAnnotation  ();
void    applyDropElemAnnotation     ();
void    applyMultiValueAnnotation   ();
void    applySuppressModeAnnotation ();
void    applyIncompleteCommandAnnotation ();

void applyAddModeAnnotationToTargetNodes (const string &targetNodeName);
void applyCompactElemAnnotationToTargetNodes (const string &targetNodeName);
void applyDropElemAnnotationToTargetNodes (const string &targetNodeName);
void applyMultiValueAnnotationToTargetNodes (const string &targetNodeName);
void applySuppressModeAnnotationToTargetNodes (const string &targetNodeName);
void applyIncompleteCommandAnnotationToTargetNodes (const string &targetNodeName);

    // Now the data members

    private :
           map<string, vector<YangElement *> > m_cliTargetNodeNameMapForData;
           map<string, vector<YangElement *> > m_cliTargetNodeNameMapForDataWithDropNodeName;

           vector<YangElement *>               m_moduleChildElementsForData;
           bool                                m_hierarchyInformationForYangElementsInTreeForDataPrepared;

           PrismMutex                          m_mutexToBlockVisibilityInConcurrentReadThreads;

    protected :
    public :
};

}

#endif // YANGUSERINTERFACE_H
