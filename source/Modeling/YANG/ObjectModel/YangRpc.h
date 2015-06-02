/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGRPC_H
#define YANGRPC_H

#include "Modeling/YANG/ObjectModel/YangElement.h"

namespace WaveNs
{

class YangRpc : public YangElement
{
    private :
    protected :
    public :
                            YangRpc                                    ();
        virtual            ~YangRpc                                    ();

        static  string      getYangName                                ();

        static YangElement *createInstance                             ();

        virtual void        getAllCliTargetNodeNamesForData            (vector<string> &allCliTargetNodeNamesForData) const;
        virtual void        computeCliTargetNodeNameMapForData         (map<string, vector<YangElement *> > &cliTargetNodeNameMapForData) const;
        virtual void        computeWillBeShownInConfigurationTree      ();

        virtual bool        considerForComputingUsageCountForGroupingsForProgrammingLanguages () const;

        virtual bool        considerForHFileForCLanguage               () const;


    // Now the data members

    private :
    protected :
    public :
};

}

#endif // YANGRPC_H
