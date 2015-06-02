/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka / Mandar Datar                     *
 ***************************************************************************/

#ifndef YANGDATAELEMENT_H
#define YANGDATAELEMENT_H

#include "Modeling/YANG/ObjectModel/YangElement.h"
#include "Modeling/YANG/ObjectModel/YangDisplayConfigurationContext.h"

namespace WaveNs
{

class YangDataElement : public YangElement
{
    private :
    protected :
    public :
                        YangDataElement                    (const string &yangName, const string &name);
                        YangDataElement                    (const string &yangName);
        virtual        ~YangDataElement                    ();

        virtual string  getCliTargetNodeNameForData        () const;

        virtual void    computeIsConfigurationForSelf      ();
        virtual void    computeFirstDataElementInHierarchy ();

        virtual UI32    getDataIndex                       () const;
                void    setDataIndex                       (const UI32 &dataIndex);

        virtual void    processAttribute                   (const string &attributeName, const string &attributeValue);
        virtual void    processChildElement                (YangElement *pYangElement);
        virtual void    unprocessChildElement              (YangElement *pYangElement);

        virtual bool            isYangElementForData                            () const;

                ResourceId      getValueString                                  (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, WaveManagedObject *pWaveManagedObject, string &valueString, ResourceId &valueType);
                ResourceId      getValueStringForAttribute                      (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, WaveManagedObject *pWaveManagedObject, Attribute *pAttribute, string &valueString, ResourceId &valueType, const bool &checkForAttributeDefaultValue);
                void            getKeyStringForAssociatedManagedObject          (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, const ObjectId &objectId, string &valueString);
                ResourceId      getAttributeValueStringForDisplayConfiguration  (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, Attribute *pAttribute, string &displayString, WaveManagedObject *pWaveManagedObject, ResourceId &valueType , Attribute *&pFinalAttribute, const bool &checkForAttributeDefaultValue);
                void            displayConfigurtionForSingleElement             (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, WaveManagedObject *pWaveManagedObject, const bool &displayOnMatch, const string &stringToMatch, const bool &checkForYangDefault);
                void            getConfigurtionForSingleElement                 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, WaveManagedObject *pWaveManagedObject, bool &nothingToPrint, bool &printNoConfig, string &configString, bool &incompleteCommand, string &configValue, const bool &checkForYangDefault);

        virtual bool            isValueSameAsDefault                            (const string &valueString, ResourceId &valueType);

        virtual bool            evaluateWhenConditions                          (YangDisplayConfigurationContext *pYangDisplayConfigurationContext);

        virtual void            applyFormattingToConfigString                   (string &configString) const;

                ResourceId      formatValueString                               (string &valueString, const ResourceId &valueType) const;

        virtual bool            considerForHFileForCLanguage                    () const;

    // Now the data members

    private :
        UI32                        m_dataIndex;

    protected :
    public :
};

}

#endif // YANGDATAELEMENT_H
