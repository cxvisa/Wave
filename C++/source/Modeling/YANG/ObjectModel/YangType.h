/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGTYPE_H
#define YANGTYPE_H

#include "Modeling/YANG/ObjectModel/YangElement.h"
#include "Framework/Attributes/Attribute.h"

namespace WaveNs
{

class YangType : public YangElement
{
    private :
    protected :
    public :
                              YangType                                 ();
        virtual              ~YangType                                 ();

        static  string        getYangName                              ();


        static  YangElement  *createInstance                           ();

        static  void          initializeBuiltinTypes                   ();
                bool          isKnownBuiltinType                       (const string &typeName) const;

                void          populateEnumAttribute                    (string name, UI32 value);
                ResourceId    getValueFromEnumName                     (const string name, UI32 &value);
                ResourceId    getEnumNameFromValue                     (string &name, const UI32 &value);

                void          populateBitMapAttribute                  (string name, UI32 value);
                void          getBitPositionFromBitName                (string name, UI32 &value);
                void          getBitNameFromBitPosition                (string &name, UI32 value);
                void          getStringValueFrom32BitBitMap            (string &bitMapString, UI32 bitPattern);
                void          getStringValueFrom64BitBitMap            (string &bitMapString, UI64 bitPattern);
                void          getDisplayStringForYangTypeInsideUnion   (Attribute *pAttribute, string &displayString );

        virtual void          processChildElement                      (YangElement *pYangElement);

    // Now the data members
    private :

        static  set<string>    m_knownBuiltinTypes;

                Attribute     *m_pAttribute;

                UI32           m_nextEnumValue;

    protected :
    public :
};

}

#endif // YANGTYPE_H
