/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGLEAF_H
#define YANGLEAF_H

#include "Modeling/YANG/ObjectModel/YangDataElement.h"

namespace WaveNs
{

class YangLeaf : public YangDataElement
{
    private :
    protected :
    public :
                             YangLeaf                                ();
        virtual             ~YangLeaf                                ();

        static  string       getYangName                             ();

        static  YangElement *createInstance                          ();

        virtual void         computeCliTargetNodeNameForSelfInternal ();

                bool         getIsEmpty                              () const;
                void         setIsEmpty                              (const bool &isEmpty);

        virtual void         processChildElement                     (YangElement *pYangElement);

                void         displayConfigurtionForLeaf              (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, WaveManagedObject *pWaveManagedObject);

        virtual bool         isValueSameAsDefault                    (const string &valueString, ResourceId &valueType);

        virtual ResourceId                              doesElementValueMatch                                        (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, const string &matchValue);
        virtual WaveYangMemberElementFilterInformation *collectMemberElementFilterInformation (YangDisplayConfigurationContext *pYangDisplayConfigurationContext) const;

    // Now the data members

    private :
        bool m_isEmpty;

    protected :
    public :
};

}

#endif // YANGLEAF_H
