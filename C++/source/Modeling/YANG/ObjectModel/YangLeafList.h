/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGLEAFLIST_H
#define YANGLEAFLIST_H

#include "Modeling/YANG/ObjectModel/YangDataElement.h"

namespace WaveNs
{

class YangLeafList : public YangDataElement
{
    private :
    protected :
    public :
                            YangLeafList    ();
        virtual            ~YangLeafList    ();

        static  string      getYangName     ();

        static YangElement *createInstance  ();

                void        displayConfigurtionForLeaf (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, WaveManagedObject *pWaveManagedObject);

        virtual void        applyFormattingToConfigString       (string &configString) const;

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // YANGLEAFLIST_H
